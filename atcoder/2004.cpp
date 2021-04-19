/*
	Problem:	2004.cpp
	Time:		2021-04-18 09:06
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <map>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>
#define i64 long long
#define u64 unsigned i64

using namespace std;

	template <typename T>
inline T read()
{
	T ans = 0, flag = 1;
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)
namespace Pollard
{
	u64 mul(u64 a, u64 b, const u64 p)
	{
		return (__int128)a * b % p;
		if (a < b) swap(a, b);
		u64 ans = 0;
		while (b)
		{
			(ans += (b & 15) * a) %= p;
			(a <<= 4) %= p;b >>= 4;
		}
		return ans;
	}
	u64 power_pow(u64 base, u64 b, const u64 p)
	{
		u64 ans = 1;
		while (b)
		{
			if (b & 1) ans = mul(ans, base, p);
			if (b >>= 1) base = mul(base, base, p);
		}
		return ans;
	}
	int tst[] = {2, 3, 13, 17, 19, 23};
	inline bool rabin(u64 n)
	{
		if (n <= 2) return (n == 2);
		u64 a = 0, b = n - 1;
		while (!(b & 1))
		{
			a++;
			b >>= 1;
		}
		for (int x : tst)
		{
			if (x == n) return 1;
			u64 fk = power_pow(x, b, n);
			if (fk == 1) continue;
			REP(i, 0, a - 1)
			{
				u64 nxt = mul(fk, fk, n);
				if (nxt == 1)
				{
					if (fk != n - 1) return 0;
					goto ok;
				}
				fk = nxt;
			}
			if (fk != 1) return 0;
ok:;
		}
		return 1;
	}
	i64 rho(const i64 n)
	{
		if (!(n & 1)) return 2;
		i64 c = (((u64)rand() << 32) | rand()) % n;
		for (i64 g = 1, s = 0, t = 0; ; g <<= 1, s = t)
		{
			i64 v = 1;
			REP(i, 1, g)
			{
				t = (mul(t, t, n) + c) % n;
				v = mul(v, abs(s - t), n);
				if (!(i & 127))
				{
					i64 d = __gcd(v, n);
					if (d > 1) return d;
				}
			}
			i64 d = __gcd(v, n);
			if (d > 1) return d;
		}
		return 233;
	}
	vector <i64> solve(i64 x)
	{
		if (x == 1) return vector <i64> (0);
		if (rabin(x)) return vector <i64> {x};
		i64 d = rho(x);
		auto lhs = solve(d), rhs = solve(x / d);
		for (auto i : rhs) lhs.emplace_back(i);
		return lhs;
	}
}
const int N = 1e5;
int n;
map <__int128, int> cnt;
map <__int128, __int128> fk;

int main()
{
#ifdef CraZYali
	file("2004");
#endif
	n = read<int>();
	int ard = 0;
	REP(i, 1, n)
	{
		i64 x = read<i64>();
		if (x == 1)
		{
			cnt[1]++;
			continue;
		}
		auto fac = Pollard :: solve(x);
		sort(fac.begin(), fac.end());
		if (fac.back() > N)
		{
			ard++;
			continue;
		}
		map <int, int> tmp;
		for (auto j : fac) tmp[j]++;
		__int128 real = 1, anti = 1;
		for (auto j : tmp)
		{
			REP(k, 1, j.second % 3) real *= j.first;
			REP(k, 1, (3 - j.second % 3) % 3) anti *= j.first;
		}
		cnt[real]++;
		cnt[anti] += 0;
		fk[real] = anti;fk[anti] = real;
	}

	int ans = 0;
	for (auto i : cnt) if (i.first > 1) ans += max(i.second, cnt[fk[i.first]]);
	ans /= 2;
	ans += ard + (cnt[1] >= 1);
	cout << ans << endl;
	return 0;
}
