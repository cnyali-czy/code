#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)

#include <algorithm>
#include <iostream>
#include <cstdio>
using namespace std;
const int maxn = 3000 + 10, maxm = 300 + 5, inf = 1e8;

int n, m;
int x[maxn], s[maxn], dis[maxn][maxn], f[maxn][maxm], dp[maxn][maxm];

int main()
{
#ifndef ONLINE_JUDGE
	freopen("4767.in", "r", stdin);
	freopen("4767.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, n) scanf("%d", x + i);
	sort(x + 1, x + 1 + n);
	REP(i, 1, n) s[i] = x[i] + s[i-1];
	REP(l, 1, n)
		REP(r, l, n)
		{
			int mid = l + r >> 1;
			dis[l][r] = (mid * 2 - r - l) * x[mid] - (s[mid-1] - s[l-1]) + (s[r] - s[mid]);
		}
	REP(i, 1, n)
		REP(j, 1, m) dp[i][j] = inf;
	REP(i, 1, n) dp[i][1] = dis[1][i];
	REP(j, 2, m)
	{
		f[n+1][j] = n;
		DREP(i, n, 1)
			REP(k, f[i][j-1], f[i+1][j])
			if (dp[i][j] > dp[k][j-1] + dis[k+1][i]) dp[i][j] = dp[f[i][j] = k][j-1] + dis[k+1][i];
	}
	cout << dp[n][m] << endl;
	return 0;
}
