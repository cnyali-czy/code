/*
	Problem:	6091.cpp
	Time:		2020-08-13 19:32
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cstdio>
#define i64 long long
using namespace std;
const int maxn = 1e6 + 10;

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

int n, d;

int prime[maxn], phi[maxn], Min[maxn], p_cnt;
bool notp[maxn];
struct __init__
{
	__init__(const int N = maxn - 10)
	{
		REP(i, 2, N)
		{
			if (!notp[i]) phi[prime[++p_cnt] = i] = i - 1, Min[i] = i;
			REP(j, 1, p_cnt)
			{
				int tmp = i * prime[j];
				if (tmp > N) break;
				notp[tmp] = 1;
				Min[tmp] = prime[j];
				if (i % prime[j])
					phi[tmp] = phi[i] * (prime[j] - 1);
				else
				{
					phi[tmp] = phi[i] * prime[j];
					break;
				}
			}
		}
	}
}__INIT__;

int stk[maxn], top;
void split(int x)
{
	top = 0;
	while (x > 1)
	{
		if (Min[x] ^ stk[top]) stk[++top] = Min[x];
		x /= Min[x];
	}
}

i64 power_pow(i64 base, int b, const int MOD)
{
	i64 ans = 1;
	while (b)
	{
		if (b & 1) (ans *= base) %= MOD;
		(base *= base) %= MOD;
		b >>= 1;
	}
	return ans;
}
bool judge(int g)
{
	REP(i, 1, top)
		if (power_pow(g, phi[n] / stk[i], n) == 1) return 0;
	return power_pow(g, phi[n], n) == 1;
}
int g[maxn], m;

int main()
{
#ifdef CraZYali
	file("6091");
#endif
	register int T = read<int>();
	while (T--)
	{
		 n = read<int>();d = read<int>();
		 split(phi[n]);
		 m = 0;
		 REP(i, 1, n - 1) if (judge(i))
		 {
			 for (int k = 1, ki = i; k <= phi[n]; k++, ki = 1ll * ki * i % n) if (__gcd(k, phi[n]) == 1)
			 	g[++m] = ki;
			 break;
		 }
		 printf("%d\n", m);
		 sort(g + 1, g + 1 + m);
		 REP(i, 1, m / d) printf("%d ", g[i * d]);
		 puts("");
	}
	return 0;
}
