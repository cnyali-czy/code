#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1505;

int n, ans;
int G[1505][1505];
bool vis[1505];

void dfs(int x)
{
	if (x == n) ans++;
	x++;
	REP(i, 1, n) if (G[x][i] && !vis[i])
	{
		vis[i] = 1;
		dfs(x);
		vis[i] = 0;
	}
}

int main()
{
#ifdef CraZYali
	freopen("C.in", "r", stdin);
	freopen("C.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n) REP(j, 1, n) scanf("%1d", G[i] + j);
	dfs(0);
	puts(ans % 4 == 0 ? "YES" : "NO");
	return 0;
}
