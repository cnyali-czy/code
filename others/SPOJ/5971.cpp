/*
	Problem:	5971.cpp
	Time:		2020-04-05 21:37
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

int prime[maxn], p_cnt, v[maxn];
long long ans[maxn];
bool notp[maxn];
struct __init__
{
	__init__(const int n = maxn - 10)
	{
		v[1] = 1;
		REP(i, 2, n)
		{
			if (!notp[i])
			{
				prime[++p_cnt] = i;
				v[i] = 1 - i;
			}
			REP(j, 1, p_cnt)
			{
				int tmp = i * prime[j];if (tmp > n) break;
				notp[tmp] = 1;
				if (i % prime[j])
					v[tmp] = v[i] * (1 - prime[j]);
				else
				{
					v[tmp] = v[i];
					break;
				}
			}
		}
		REP(i, 1, n)
		{
			const long long ccc = i * (i + 1ll) / 2;
			for (register int ij = i, j = 1; ij <= n; ij += i, j++) ans[ij] += ccc * v[j]; 
			ans[i] *= i;
		}
	}
}__INIT__;
int main()
{
#ifdef CraZYali
	file("5971");
#endif
	register int T = read<int>();
	while (T--) cout << ans[read<int>()] << '\n';
	return 0;
}
