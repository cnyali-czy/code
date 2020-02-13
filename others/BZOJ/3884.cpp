/*
Problem:	3884.cpp
Time:		2020-02-13 12:15
Author:		CraZYali
E-Mail:		yms-chenziyang@outlook.com 
*/
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <cassert>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e7 + 10;
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

int prime[maxn], p_cnt, phi[maxn];
bool notp[maxn];

struct __init__
{
	__init__(const int N = 1e7)
	{
		phi[1] = 1;
		REP(i, 2, N)
		{
			if (!notp[i]) phi[prime[++p_cnt] = i] = i - 1;
			REP(j, 1, p_cnt)
			{
				int tmp = i * prime[j];if (tmp > N) break;
				notp[tmp] = 1;
				if (i % prime[j]) phi[tmp] = phi[i] * (prime[j] - 1);
				else
				{
					phi[tmp] = phi[i]* prime[j];
					break;
				}
			}
		}
	}
}__INIT__;
#define i64 long long
int power_pow(i64 base, int b, const int MOD)
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

int f(int p)
{
	if (p == 1) return 0;
	return power_pow(2, f(phi[p]) + phi[p], p);
}

int main()
{
#ifdef CraZYali
	file("3884");
#endif
	register int T = read<int>();
	while (T--) printf("%d\n", f(read<int>()));
	return 0;
}
