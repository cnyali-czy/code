#define chkmin(a, b) a = min(a, b)
#define REP(i, s, e) for (int i = s; i <= e ;i++)

#include <bits/stdc++.h>
#define int long long

using namespace std;
const int maxn = 1000 + 10, maxm = 2000 + 5, inf = 1ll<<40;

int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

int fa[maxn];
void pre(int x)
{
	for (int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ fa[x])
		{
			fa[to[i]] = x;
			pre(to[i]);
		}
}

int down[maxn], up[maxn], cost[maxm];
int n, m;
bool ok[maxn][maxm];
int dp[maxn][maxm];
bool flag[maxn];

void dfs(int x)
{
	for (int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ fa[x])
		{
			flag[x] = 1;
			dfs(to[i]);
			int Min = inf;
			REP(j, 1, m) chkmin(Min, dp[to[i]][j]);
			int res = inf;
			REP(j, 1, m) if (ok[x][j]) chkmin(res, cost[j]);
			Min += res;
			REP(j, 1, m)
				if (ok[x][j])
				{
					if (ok[to[i]][j]) chkmin(dp[x][j], dp[to[i]][j]);
				}
				else chkmin(dp[x][j], Min);
		}
	if (!flag[x]) memset(dp[x], 0, sizeof(dp[x]));
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 2, n)
	{
		int x, y;
		scanf("%lld%lld", &x, &y);
		add(x, y);add(y, x);
	}
	n++;
	add(n,1);
	pre(1);
	REP(i, 1, m)
	{
		scanf("%lld%lld%lld", down + i, up + i, cost + i);
		int x = fa[down[i]];
		while (x != up[i])
		{
			ok[x][i] = 1;
			x = fa[x];
		}
	}
	REP(i, 1, n)
		REP(j, 1, m) dp[i][j] = inf;
	dfs(1);
	int ans = inf;
	REP(j, 1, m) ans = min(ans, dp[1][j]);
	REP(i, 1, n)
		REP(j, 1, m)
		printf("%lld %lld %lld\n", i, j, dp[i][j]);
	cout << (ans == inf ? -1 : ans) << endl;
	return 0;
}
