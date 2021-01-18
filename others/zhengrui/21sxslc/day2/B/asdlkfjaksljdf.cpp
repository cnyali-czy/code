/*
	Problem:	B.cpp
	Time:		2021-01-10 09:58
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cassert>
#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 1e6 + 10, MOD = 998244353;

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
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int ty, n, k, ans[maxn];

int fac[maxn], invs[maxn], Inv[maxn];

void init(int n)
{
	fac[0] = invs[0] = Inv[0] = 1;
	fac[1] = invs[1] = Inv[1] = 1;
	REP(i, 2, n)
	{
		fac[i] = 1ll * i * fac[i - 1] % MOD;
		invs[i] = 1ll * (MOD - MOD / i) * invs[MOD % i] % MOD;
		Inv[i] = 1ll * invs[i] * Inv[i - 1] % MOD;
	}
}
i64 C(int n, int m) {return n < m || m < 0 ? 0 : 1ll * fac[n] * Inv[m] % MOD * Inv[n - m] % MOD;}

i64 calc(int x1, int y1, int x2, int y2)
{
	int n = x2 - x1;
	if (abs(y2 - y1) > n) return 0;
	assert(y1 > 0);assert(y2 > 0);assert(abs(y2 - y1) <= n);assert((n + y2 - y1) % 2 == 0);
	cerr << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << ' ' << ( C(n, (n + y2 - y1) >> 1) - C(n, (n + y2 + y1) >> 1) + MOD ) % MOD << endl;
	return ( C(n, (n + y2 - y1) >> 1) - C(n, (n + y2 + y1) >> 1) + MOD ) % MOD;
}

i64 calc1(int n, int s, int mi)
{
	if (mi == 1) return calc1(n - 1, s - 1, 0);
	if (mi > s) return 0;
	assert((n + s) % 2 == 0);
	return (C(n, n + s >> 1) - C(n, (n + s + 2 * (mi - 1)) / 2) + MOD) % MOD;
	i64 res = 0;
	if ( 1 >= mi) res += calc(1,  1 - (mi - 1), n, s - (mi - 1));
	if (-1 >= mi) res += calc(1, -1 - (mi - 1), n, s - (mi - 1));
	return res % MOD;
}
i64 calc(int n, int s, int mi)
{
	return (calc1(n, s, mi) - calc1(n, s, mi + 1) + MOD) % MOD;
}

int main()
{
#ifdef CraZYali
	file("B");
#endif
	cin >> ty >> n;
	if (ty == 1) cin >> k;
	init(n);

	REP(i, 1, (1 << n) - 1)
	{
		int top = 0, res = 0;
		REP(j, 1, n)
			if (i >> (j - 1) & 1) top++;
			else if (top) {top--;res++;}
		ans[res]++;
		int s = 0, mi = 0;
		REP(j, 1, n)
		{
			if (i >> (j - 1) & 1) s++;
			else s--;
			mi = min(s, mi);
		}
		assert(n - s + 2 * mi == res * 2);
	}
	static int res[maxn];
	REP(mi, -n, 1)
		REP(s, mi, n)
		{
			int tot = n - s + 2 * max(0, mi);
			if (0 <= tot && tot <= n && tot % 2 == 0)
			{
				(res[tot >> 1] += calc(n, s, mi)) %= MOD;
	//			if(calc(n,s,mi))cerr << n << ' ' << s << ' ' << mi << ' ' <<calc(n, s, mi) << endl;
			}
		}
	REP(i, 0, n / 2) printf("%d%c", ans[i], i == end_i ? '\n' : ' ');
	REP(i, 0, n / 2) printf("%d%c", res[i], i == end_i ? '\n' : ' ');
	if (ty == 1) cout << ans[k] << endl;
	else
	{
		i64 bin = 1, Ans = 0;
		REP(i, 0, n / 2)
		{
			(Ans += bin * ans[i]) %= MOD;
			(bin *= 233) %= MOD;
		}
		cout << Ans << endl;
	}

	return 0;
}
