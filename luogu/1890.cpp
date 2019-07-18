#define REP(i, s, e) for (int i = s; i <= e ; i++)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 1000 + 10;

int n, m, g[maxn][maxn];

int main()
{
#ifndef ONLINE_JUDGE
	freopen("1890.in", "r", stdin);
	freopen("1890.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, n) scanf("%d", &g[i][i]);
	REP(i, 1, n)
		REP(j, i + 1, n)
		g[i][j] = __gcd(g[i][j-1], g[j][j]);
	while (m--)
	{
		int l, r;
		scanf("%d%d", &l, &r);
		printf("%d\n", g[l][r]);
	}
	return 0;
}
