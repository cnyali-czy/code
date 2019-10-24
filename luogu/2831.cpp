#define  REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <queue>

using namespace std;
const int maxn = 18;
const double eps = 1e-8;

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

double x[maxn], y[maxn];
int dp[1 << maxn], LG[1 << maxn];

int ok[1 << maxn];
inline bool judge(int x)
{
	if (ok[x] != -1) return ok[x];
	if (x == (x & -x)) return 1;
	ok[x] = 0;
	int ccc(2);
	bool flag = 1;
	double x1, y1, x2, y2, a, b;
	int tmp;
	for (tmp = x; ccc; tmp -= tmp & -tmp, ccc--)
		if (ccc == 2) x1 = ::x[LG[tmp & -tmp]], y1 = y[LG[tmp & -tmp]];
		else x2 = ::x[LG[tmp & -tmp]], y2 = y[LG[tmp & -tmp]];
	if (fabs(x1 - x2) < eps) return 0;
	b = (y1 * x2 * x2 - y2 * x1 * x1) / (x1 * x2 * x2 - x2 * x1 * x1);
	a = (y1 - b * x1) / x1 / x1;
	if (a > -eps) return 0;
	for (; tmp; tmp -= tmp & -tmp)
	{
		double curx = ::x[LG[tmp & -tmp]], cury = y[LG[tmp & -tmp]];
		if (fabs(a * curx * curx + b * curx - cury) > eps) return 0;
	}
#ifdef CraZYali
	fprintf(stderr, "a = %.5lf b = %.5lf\n", a, b);
	for (int tmp = x; tmp; tmp -= tmp & -tmp)
	{
		double curx = ::x[LG[tmp & -tmp]], cury = y[LG[tmp & -tmp]];
		fprintf(stderr,"%.3lf ", a * curx * curx + b * cury);
	}
	fputs("\n---------\n",stderr);
#endif
	return ok[x] = 1;
}
int line[maxn][maxn];

int main()
{
#ifdef CraZYali
	file("2831");
#endif
	register int T = read<int>();
	REP(i, 0, 17) LG[1 << i] = i;
	while (T--)
	{
		n = read<int>();read<int>();
		REP(i, 0, n-1) scanf("%lf%lf", x + i, y + i);
		memset(dp, 0x3f, sizeof dp);
		memset(ok, -1, sizeof ok);
		memset(line, 0, sizeof line);
		const int inf = dp[1], lim = (1 << n) - 1;
		REP(i, 0, n - 1)
			REP(j, i + 1, n - 1) if (fabs(x[i]-x[j]) > eps)
			{
				double x1(x[i]), y1(y[i]), x2(x[j]), y2(y[j]);
				double b = (y1 * x2 * x2 - y2 * x1 * x1) / (x1 * x2 * x2 - x2 * x1 * x1);
				double a = (y1 - b * x1) / x1 / x1;
				if (a > -eps) continue;
				REP(k, 0, n - 1)
				{
					double curx = x[k], cury = y[k];
					if (fabs(a * curx * curx + b * curx - cury) < eps)
					{
						line[i][j] |= (1 << k);
						line[j][i] |= (1 << k);
					}
				}
			}
		REP(i, 0, n - 1) line[i][i] = (1 << i);
		dp[0] = 0;
		REP(S, 0, lim - 1) 
		{
			int x = (lim ^ S);
			REP(k, 0, n - 1)
				chkmin(dp[S | line[k][LG[x & -x]]], dp[S] + 1);
		}
		printf("%d\n", dp[lim]);
	}
	return 0;
}
