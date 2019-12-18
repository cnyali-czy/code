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
const long long lim = 1ll << 62;
namespace rho
{
	inline long long add(long long x, long long y, long long MOD)
	{
		long long res = x + y;
		if (res >= MOD) res -= MOD;
		return res;
	}
	inline long long mul(__int128 a, __int128 b, long long MOD) {return a * b % MOD;}
	long long power_pow(long long base, long long b, const long long MOD)
	{
		long long ans(1);
		while (b)
		{
			if (b & 1) ans = mul(ans, base, MOD);
			base = mul(base, base, MOD);
			b >>= 1;
		}
		return ans;
	}

	int tst[] = {2, 3, 13, 17, 19, 23, 19260817}, times(3);//sizeof (tst) / sizeof (int));
	inline bool fake(long long a, long long p)
	{
		long long u(p - 1), l(0);
		while (!(u & 1))
		{
			l++;
			u >>= 1;
		}
		long long x = power_pow(a, u, p);
		if (x == 1) return 0;
		REP(i, 1, l)
		{
			if (1 < x && x < p - 1 && mul(x, x, p) == 1) return 1;
			x = mul(x, x, p);
		}
		return x != 1;
	}
	inline bool check(long long p)
	{
		if (p == 2) return 1;
		if (p < 2 || p % 2 == 0) return 0;
		REP(i, 0, times-1)
			if (p == tst[i]) return 1;
			else if (tst[i] < p && fake(tst[i], p)) return 0;
		return 1;
	}
	long long c;
	long long f(long long x, long long n)
	{
		return add(mul(x, x, n), c, n);
	}
	inline long long rho(long long x)
	{
		long long s(0), t(0);
		c = rand() % (x - 1) + 1;
		long long val = 1;
		for (long long goal = 1; ; goal <<= 1, s = t, val = 1)
		{
			REP(step, 1, goal)
			{
				t = f(t, x);
				val = mul(val, abs(t - s), x);
				if (step % 127 == 0)
				{
					long long d(__gcd(val, x));
					if (d > 1) return d;
				}
			}
			long long d(__gcd(val, x));
			if (d > 1) return d;
		}
	}
	long long solve(long long n)
	{
		if (n == 1 || check(n)) return n;
		long long m = rho(n), res1(solve(m)), res2(solve(n / m));
		if (res1 > res2) return res1;
		return res2;
	}
}

int main()
{
#ifdef CraZYali
	file("4718");
#endif
	register int T(read<int>());
	while (T--)
	{
		long long n(read<long long>());
		if (rho::check(n)) puts("Prime");
		else printf("%lld\n", rho::solve(n));
	}
	return 0;
}
