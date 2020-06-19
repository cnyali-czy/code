/*
	Problem:	5325-new-new.cpp
	Time:		2020-06-11 21:40
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cmath>
#include <iostream>
#include <cstdio>

using namespace std;
#define i64 long long
const int maxn = 1e5 + 10, MOD = 1e9 + 7, inv2 = (MOD + 1) / 2, inv3 = (MOD + 1) / 3;

inline int add(int x, int y) {return (x += y) >= MOD ? x - MOD : x;}
inline i64 S1(i64 n) {if (n >= MOD) n %= MOD;return n * (n + 1) / 2 % MOD;}
inline i64 S2(i64 n) {if (n >= MOD) n %= MOD;return n * (n + 1) / 2 % MOD * (n + n + 1) % MOD * inv3 % MOD;}

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

i64 n, w[maxn << 1];
int tot, sqr;

int prime[maxn], p_cnt, sp1[maxn], sp2[maxn], ind1[maxn], ind2[maxn];
bool notp[maxn];

void init(int N)
{
	REP(i, 2, N)
	{
		if (!notp[i])
		{
			prime[++p_cnt] = i;
			sp1[p_cnt] = add(i, sp1[p_cnt - 1]);
			sp2[p_cnt] = (1ll * i * i + sp2[p_cnt - 1]) % MOD;
		}
		REP(j, 1, p_cnt)
		{
			int tmp = i * prime[j]; if (tmp > N) break;
			notp[tmp] = 1;
			if (i % prime[j] == 0) break;
		}
	}
}
inline int& get(i64 x) {return n / x <= sqr ? ind1[n / x] : ind2[n / (n / x)];}
int g1[maxn << 1], g2[maxn << 1];

i64 S(i64 x, int j)
{
	if (prime[j] >= x) return 0;
	i64 k = get(x);
	i64 ans = 1ll * g2[k] - sp2[j] - (g1[k] - sp1[j]);
	for (int i = j + 1; i <= p_cnt && prime[i] <= x / prime[i]; i++)
	{
		i64 pe = prime[i];
		for (int e = 1; pe <= x; e++, pe *= prime[i])
		{
			i64 xx = pe % MOD;
			(ans += xx * (xx - 1) % MOD * ((e != 1) + S(x / pe, i))) %= MOD;
		}
	}
	return ans % MOD;
}

int main()
{
#ifdef CraZYali
	file("5325-new-new");
#endif
	cin >> n;sqr = sqrt(n);
	init(sqr);
	for (i64 i = 1, j; i <= n; i = j + 1)
	{
		j = n / (n / i);
		i64 x = n / i;
		w[++tot] = n / i;
		if (x >= MOD) x %= MOD;
		g1[tot] = S1(x) - 1;
		g2[tot] = S2(x) - 1;
		get(n / i) = tot;
	}
	REP(i, 1, p_cnt)
		for (int j = 1; j <= tot && prime[i] <= w[j] / prime[i]; j++)
		{
			i64 k = get(w[j] / prime[i]);
			i64 G1 = (g1[j] - 1ll * prime[i] * (g1[k] - sp1[i - 1])) % MOD;
			i64 G2 = (g2[j] - 1ll * prime[i] * prime[i] % MOD * (g2[k] - sp2[i - 1])) % MOD;
			if (G1 < 0) G1 += MOD;if (G2 < 0) G2 += MOD;
			g1[j] = G1;g2[j] = G2;
		}
	cout << (S(n, 0) + 1 + MOD) % MOD;
	return 0;
}
