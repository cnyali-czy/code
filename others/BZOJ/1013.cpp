#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 10 + 5;

int n;
long double a[maxn][maxn], x[maxn];

int main()
{
#ifdef CraZYali
	freopen("1013.in", "r", stdin);
	freopen("1013.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 0, n)
	{
		REP(j, 1, n) scanf("%LF", &a[i][j]);
		if (!i) continue;
		REP(j, 1, n) a[i][n+1] += (a[i][j] + a[0][j]) * (a[i][j] - a[0][j]);
		REP(j, 1, n) a[i][j] = 2 * (a[i][j] - a[0][j]);
	}
	REP(i, 1, n)
		REP(j, i + 1, n)
		{
			long double t = a[j][i] / a[i][i];
			REP(k, 1, n + 1)
				a[j][k] -= t * a[i][k];
		}
	DREP(i, n, 1)
	{
		x[i] = a[i][n + 1] / a[i][i];
		REP(j, i, n) a[i-1][n+1] -= a[i-1][j] * x[j];
	}
	REP(i, 1, n) printf("%.3LF ", x[i]);
	return 0;
}
