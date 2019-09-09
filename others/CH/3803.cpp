/*
 * File Name:	3803.cpp
 * Author	:	CraZYali
 * Year		:	2019.09.08 22:34
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 14;
const double inf = 1e18;

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout);

double f[maxn][maxn][maxn][maxn][5][5];
int t1,t2,t3,t4;

double dp(int a,int b,int c,int d,int p,int q)
{
	if(f[a][b][c][d][p][q]) return f[a][b][c][d][p][q];
	double &ans = f[a][b][c][d][p][q];
	int x1(a + (p == 1) + (q == 1)), x2(b + (p == 2) + (q == 2)), x3(c + (p == 3) + (q == 3)), x4(d + (p == 4) + (q == 4));
	if (x1 >= t1 && x2 >= t2 && x3 >= t3 && x4 >= t4) return 0;
	int sum = 54 - x1 - x2 - x3 - x4;
	if (sum <= 0) return ans = inf;
	if (a < 13) ans += dp(a + 1, b, c, d, p, q) * (13 - a) / sum;
	if (b < 13) ans += dp(a, b + 1, c, d, p, q) * (13 - b) / sum;
	if (c < 13) ans += dp(a, b, c + 1, d, p, q) * (13 - c) / sum;
	if (d < 13) ans += dp(a, b, c, d + 1, p, q) * (13 - d) / sum;
	if (!p)
	{
		double t = dp(a, b, c, d, 1, q);
		chkmin(t, dp(a, b, c, d, 2, q));
		chkmin(t ,dp(a, b, c, d, 3, q));
		chkmin(t, dp(a, b, c, d, 4, q));
		ans += t / sum;
	}
	if (!q)
	{
		double t = dp(a, b, c, d, p, 1);
		chkmin(t, dp(a, b, c, d, p, 2));
		chkmin(t, dp(a, b, c, d, p, 3));
		chkmin(t, dp(a, b, c, d, p, 4));
		ans += t / sum;
	}
	return ++ans;
}
int main()
{
#ifdef CraZYali
	file("3803");
#endif
	cin >> t1 >> t2 >> t3 >> t4;
	double Ans = dp(0, 0, 0, 0, 0, 0);
	printf("%.3lf\n", Ans >= inf ? -1 : Ans);;
	return 0;
}
