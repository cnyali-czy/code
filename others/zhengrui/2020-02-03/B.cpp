#define REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;
const int maxn = 11451400;
template <typename T> T read()
{
	T ans(0), flag(1);
	char c(getchar());
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

int m, n, k;
#define i64 long long
const i64 lim = 1ll << 62;
i64 A[maxn], top;
namespace rho
{
	inline i64 add(i64 x, i64 y, i64 MOD)
	{
		i64 res = x + y;
		if (res >= MOD) res -= MOD;
		return res;
	}

	inline i64 mul(__int128 a, __int128 b, i64 MOD) {return a * b % MOD;}
	i64 power_pow(i64 base, i64 b, const i64 MOD)
	{
		i64 ans(1);
		while (b)
		{
			if (b & 1) ans = mul(ans, base, MOD);
			base = mul(base, base, MOD);
			b >>= 1;
		}
		return ans;
	}

	int tst[] = {2, 3, 13, 17, 19, 23, 19260817}, times(3);
	inline bool fake(i64 a, i64 p)
	{
		i64 u(p - 1), l(0);
		while (!(u & 1))
		{
			l++;
			u >>= 1;
		}
		i64 x = power_pow(a, u, p);
		if (x == 1) return 0;
		REP(i, 1, l)
		{
			if (1 < x && x < p - 1 && mul(x, x, p) == 1) return 1;
			x = mul(x, x, p);
		}
		return x != 1;
	}
	inline bool check(i64 p)
	{
		if (p == 2) return 1;
		if (p < 2 || p % 2 == 0) return 0;
		REP(i, 0, times-1)
			if (p == tst[i]) return 1;
			else if (tst[i] < p && fake(tst[i], p)) return 0;
		return 1;
	}
	i64 c;
	i64 f(i64 x, i64 n)
	{
		return add(mul(x, x, n), c, n);
	}
	inline i64 rho(i64 x)
	{
		i64 s(0), t(0);
		c = rand() % (x - 1) + 1;
		i64 val = 1;
		for (i64 goal = 1; ; goal <<= 1, s = t, val = 1)
		{
			REP(step, 1, goal)
			{
				t = f(t, x);
				val = mul(val, abs(t - s), x);
				if (step % 127 == 0)
				{
					i64 d(__gcd(val, x));
					if (d > 1) return d;
				}
			}
			i64 d(__gcd(val, x));
			if (d > 1) return d;
		}
	}
	void solve(i64 n)
	{
		if (n == 1) return;
		if (check(n)) return void(A[top++] = n);
		i64 m = rho(n);
		solve(m);
		solve(n / m);
	}
}

int _a, _A;
pair <i64, i64> ans[maxn], Ans[maxn];
int lg[(1 << 25) + 1];
int main()
{
#ifdef CraZYali
	file("B");
#endif
	REP(i, 1, 25) lg[1 << i] = i;
	register int T = read<int>();
	while (T--)
	{
		i64 MOD = read<i64>();
		REP(k, 1, 32)
		{
			i64 tot = k * MOD + 1;
			top = 0;
			rho::solve(tot);
			REP(S, 1, (1 << top) - 1)
			{
				i64 res = 1, iv;
				for (int x = S; x; x &= (x - 1)) res *= A[lg[x & -x]];
				iv = tot / res;
				if (1 < res && res < MOD && 1 < iv && iv < MOD) ans[_a++] = make_pair(res, iv);
			}
		}
		sort(ans, ans + _a);
		i64 Min;
		REP(i, 0, _a - 1)
			if (i == 0 || ans[i].second < Min)
			{
				Ans[++_A] = make_pair(ans[i].first, ans[i].second);
				Min = ans[i].second;
			}
		cout << _A << endl;
		REP(i, 1, _A) printf("%lld %lld\n", Ans[i].first, Ans[i].second);
		_a = _A = 0;
	}
	return 0;
}
