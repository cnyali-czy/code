#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 1000 + 10, maxm = 1000 + 10;

int m, n, k, q;

int a[maxn][maxn], b[maxn][maxn];

int A[maxn * maxn];

int ans[maxn][maxm];

int main()
{
#ifdef CraZYali
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	cin >> n >> m >> q;
	REP(i, 1, n)
		REP(j, 1, m)
		{
			scanf("%d", &k);
			a[i][j] = b[j][i] = k;
		}

	REP(i, 1, n) sort(a[i] + 1, a[i] + 1 + m, greater<int>());
	REP(i, 1, m) sort(b[i] + 1, b[i] + 1 + n, greater<int>());
	REP(i, 1, m)
		REP(j, 1, n)
			A[b[i][j]] = j;

	REP(i, 1, n)
		REP(j, 1, m)
			ans[j][A[a[i][j]]]++;

	while (q --> 0)
	{
		register int x, y;
		scanf("%d%d", &x, &y);
		printf("%d\n", ans[x][y]);
	}

	return 0;
}
