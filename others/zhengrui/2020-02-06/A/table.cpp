/*
 * File Name:	A.cpp
 * Author	:	CraZYali
 * Time		:	2020.02.06 09:35
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
#define int long long
using namespace std;
const int maxn = 1e6 + 10;
const double eps = 1e-8;

template <typename T> inline T read()
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

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout);

int prime[maxn], p_cnt, mu[maxn], to[maxn], Max[maxn];
bool notp[maxn];

int s2[maxn], s1[maxn];

int MOD;	
inline void init(int n = maxn - 10)
{
	mu[1] = 1;
	s2[1] = 1;
	REP(i, 2, n)
	{
		if (!notp[i]) mu[to[prime[++p_cnt] = i] = i] = -1, Max[i] = i, s2[i] = 2;
		REP(j, 1, p_cnt)
		{
			int tmp = i * prime[j];
			if (tmp > n) break;
			notp[tmp] = 1;
			Max[tmp] = Max[i];
			if (prime[j] > Max[i]) Max[tmp] = prime[j];
			if (i % prime[j])
			{
				to[tmp] = to[i] * prime[j];
				mu[tmp] = -mu[i];
				s2[tmp] = s1[i] * 2;
			}
			else
			{
				s2[tmp] = s1[i];
				to[tmp] = to[i];
				break;
			}
		}
	}
	DEP(i, n, 1) s2[i] = s2[i-1];
	REP(i, 1, p_cnt)
		REP(j, 1, n / prime[i])
		s2[j * prime[i]] += s2[j];
	REP(i, 1, n)
	{
		s1[i] = (1ll * i * s2[i] % MOD + s1[i-1]) % MOD;
		(s2[i] += s2[i-1]) %= MOD;
	}
}

int n, stack[100], top, lg[(1 << 25) + 5], sig[maxn];
bool vis[maxn];
long long mem[maxn];
signed main()
{
#ifdef CraZYali
	file("A");
#endif
	REP(i, 1, 25) lg[1 << i] = i;
	register int T = read<int>();
	MOD = read<int>();
	init();
	while (T--)
	{
		int n = read<int>();
		long long ans = (s1[n] + n * (n * n - s2[n]) % MOD) % MOD;
		printf("%lld\n", (MOD + ans) % MOD);
	}
	return 0;
}

