/*
 * File Name:	5325.cpp
 * Author	:	CraZYali
 * Time		:	2020.02.10 20:59
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <cmath>
#include <iostream>
#include <cstdio>
#define i64 long long
#define MOD 1000000007
#define inv2 500000004
#define inv3 333333336
#define inv6 166666668
using namespace std;
const int N = 1e6, maxn = N + 10;

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout);

int prime[maxn], p_cnt, h[maxn], s1[maxn], s2[maxn];
bool notp[maxn];

inline void inc(int &x, int y)
{
	x += y;
	if (x >= MOD) x -= MOD;
}
void init(int N)
{
	REP(i, 2, N)
	{
		if (!notp[i])
		{
			prime[++p_cnt] = i;
			s1[p_cnt] = s1[p_cnt - 1];inc(s1[p_cnt], i);
			s2[p_cnt] = s2[p_cnt - 1];inc(s2[p_cnt], 1ll * i * i % MOD);
		}
		REP(j, 1, p_cnt)
		{
			int tmp = i * prime[j];
			if (tmp > N) break;
			notp[tmp] = 1;
			if (i % prime[j] == 0) break;
		}
	}
}

i64 n, Sqr, tot, w[maxn];
int g1[maxn], g2[maxn], mem1[maxn], mem2[maxn];

i64 g(i64 x, int y)
{
	if (prime[y] >= x) return 0;
	i64 k = x <= Sqr ? mem1[x] : mem2[n / x], ans = g2[k] - g1[k] - (s2[y] - s1[y]);
	REP(i, y + 1, p_cnt)
	{
		i64 pe = prime[i]; if (pe * pe > x) break;
		for (int e = 1; pe <= x; e++, pe *= prime[i])
		{
			int xx = pe % MOD;
			ans += xx * (xx - 1ll) % MOD * ((e > 1) + g(x / pe, i)) % MOD;
		}
	}
	return ans % MOD;
}

signed main()
{
#ifdef CraZYali
	file("5325");
#endif
	cin >> n;
	init(Sqr = sqrt(n));
	for (i64 i = 1, j; i <= n; i = j + 1)
	{
		j = n / (n / i);
		w[++tot] = n / i;
		int x = w[tot] % MOD;
		g1[tot] = x * (x + 1ll) / 2 % MOD - 1;
		g2[tot] = x * (x + 1ll) % MOD * (x << 1 | 1) % MOD * inv6 % MOD - 1;
		if (n / i <= Sqr) mem1[n / i] = tot;
		else mem2[n / (n / i)] = tot;
	}
	REP(i, 1, p_cnt)
	{
		const i64 p = prime[i], pp = p * p % MOD;
		REP(j, 1, tot)
		{
			if (p * p > w[j]) break;
			i64 fff = w[j] / p;
			i64 k = fff <= Sqr ? mem1[fff] : mem2[n / fff];
			(g1[j] -= p  * (g1[k] - s1[i - 1]) % MOD) %= MOD;
			(g2[j] -= pp * (g2[k] - s2[i - 1]) % MOD) %= MOD;
		}
	}
	cout << (g(n, 0) % MOD + 1 + MOD) % MOD << endl;
	return 0;
}
