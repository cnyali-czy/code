//test
/*
Problem:	C.cpp
Time:		2020-02-15 15:37
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
const int maxn = 100 + 5 << 1;

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

int n, g, t;
double c[maxn][maxn], f1[maxn], f2[maxn], f3[maxn];
inline double C(int n, int m) {return c[n][m];}

namespace run
{
	int n, t, m, v[maxn];
	double dp[maxn][maxn], dp2[maxn][maxn], su2[maxn][maxn], su[maxn][maxn];
	int main()
	{
		cin >> n >> t >> m;
		REP(i, 1, n) v[i] = read<int>();
		sort(v + 1, v + 1 + n);
		REP(i, 1, n) chkmin(v[i], t);
		REP(i, n + 1, n + m) v[i] = t;
		REP(i, 1, n + m) dp[i][i - 1] = 1;
		REP(l, 0, n + m)
			REP(i, 1, n + m - l)
			{
				int j = i + l;
				REP(k, i, j)
				{
					double f1 = C(j - i, k - i) * (v[k] - v[i-1]) / t;
					double f2 = k <= n ? (v[k] + v[i - 1] + 1.) / 2 : 0;
					dp[i][j] += dp[i][k - 1] * dp[k + 1][j] * f1;
					su[i][j] += f1 * (f2 * dp[i][k - 1] * dp[k + 1][j] + su[i][k - 1] * dp[k + 1][j] + su[k + 1][j] * dp[i][k - 1]);
				}
			}
		dp2[0][0] = 1;
		REP(i, 0, n + m)
			REP(j, 0, m)
			{
				dp2[i + 1][j] += dp2[i][j];
				su2[i + 1][j] += su2[i][j];
				REP(k, i + 1, n + m)
					if (j + k - i <= m)
					{
						dp2[k + 1][j + k - i] += C(j + k - i, j) * dp2[i][j] * dp[i + 1][k];
						su2[k + 1][j + k - i] += C(j + k - i, j) * su2[i][j] * dp[i + 1][k];
						su2[k + 1][j + k - i] += C(j + k - i, j) * su[i + 1][k] * dp2[i][j];
					}
			}
		printf("%.10lf\n",su2[n+m+1][m]);
		return 0;
	}
}

struct __init__
{
	__init__(const int N = 100)
	{
		c[0][0] = 1;
		REP(i, 1, N) REP(j, 0, i) c[i][j] = c[i-1][j] + (j > 0 ? c[i-1][j-1] : 0);
	}
}__INIT__;

int main()
{
#ifdef CraZYali
	file("C");
#endif
	return run::main();
}
