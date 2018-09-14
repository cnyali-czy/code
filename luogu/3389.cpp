#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 100 + 5;

double M[maxn][maxn + 1];
int n;

const double eps = 1e-9;
inline bool same(double A, double B) {return abs(A - B) < eps;}

double x[maxn];

int main()
{
#ifdef CraZYali
	freopen("3389.in", "r", stdin);
	freopen("3389.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n)
		REP(j, 1, n + 1)
			scanf("%lf", &M[i][j]);
	
	REP(i, 1, n - 1)
	{
		bool flag = 1;
		REP(j, i + 1, n)
			if (!same(0, M[i][j])) {flag = 0;break;}
		if (same(M[i][i], 0) || (flag && !same(0, M[i][n + 1])))
		{
			cout << "No Solution";
			return 0;
		}
		flag = 0;
		REP(j, i + 1, n)
		{
			REP(k, i + 1, n + 1)
				M[j][k] -= M[j][i] / M[i][i] * M[i][k];
			M[j][i] = 0;
		}
	}

	if (same(0, M[n][n])) {cout << "No Solution";return 0;}

	DREP(i, n, 1)
	{
		REP(j, i + 1, n)
			M[i][n + 1] -= x[j] * M[i][j];
		x[i] = M[i][n + 1] / M[i][i];
	}

	REP(i, 1, n) printf("%.2lf\n", x[i]);
	
	return 0;
}
