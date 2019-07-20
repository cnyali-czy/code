#define  REP(i, s, e) for (int i = s; i <= e ; i++)
#define DREP(i, s, e) for (int i = s; i >= e ; i--)

#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;
const int maxn = 10, maxm = 50 + 5, maxN = maxn * maxm;

int t, n, m;double p;

namespace Gauss
{
	double M[maxN][maxN];
	int N;

	double x[maxN];

	void solve()
	{
#ifndef ONLINE_JUDGE
		REP(i, 1, N)
			REP(j, 1, N+1) fprintf(stderr,"%.2lf%c", M[i][j], j == N + 1 ? '\n' : '\t');
		fputs("===========================\n",stderr);
#endif
		REP(i, 1, N - 1)
			REP(j, i + 1, N)
			{
				REP(k, i + 1, N + 1)
					M[j][k] -= M[j][i] / M[i][i] * M[i][k];
				M[j][i] = 0;
			}
#ifndef ONLINE_JUDGE
		REP(i, 1, N)
			REP(j, 1, N+1) fprintf(stderr,"%.2lf%c", M[i][j], j == N + 1 ? '\n' : '\t');
		fputs("===========================\n",stderr);
#endif

		DREP(i, N, 1)
		{
			REP(j, i + 1, N) M[i][N + 1] -= x[j] * M[i][j];
			x[i] = M[i][N + 1] / M[i][i];
		}
#ifndef ONLINE_JUDGE
		REP(i, 1, N) fprintf(stderr,"%.5lf%c", x[i], i == N?'\n':  ' ' );
		fputs("---------------------------\n",stderr);
#endif
	}
#define id(x, y) ((x-1) * m + y)
	int d[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
	void clear() {REP(i, 1, N) REP(j, 1, N+1) M[i][j] = 0;}
	void init()
	{
		N = n * m;
		clear();
		M[1][1] = M[1][N+1] = 1;
		REP(i, 1, n)
			REP(j, 1, m)
			if (!(i == 1 && j == 1))
			{
				int U(id(i, j)), cnt(0);
				REP(k, 0, 3)
				{
					int x = i + d[k][0], y = j + d[k][1];
					if (x < 1 || x > n || y < 1 || y > m || (1 && x == n && y == m)) continue;
					cnt++;
				}
				M[U][U] = cnt * 1. / (p-1);
				REP(k, 0, 3)
				{
					int x = i + d[k][0], y = j + d[k][1];
					if (x < 1 || x > n || y < 1 || y > m || (1 && x == n && y == m)) continue;
					M[U][id(x, y)] = 1;
				}
			}
	}
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
	freopen("B.err", "w", stderr);
#endif
	cin >> t;
	while (t--)
	{
		scanf("%d%d%lf", &n, &m, &p);
		Gauss::init();
		Gauss::solve();
		printf("%.6lf\n", Gauss::x[id(n,m)]);
	}
	return 0;
}
