#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e5 + 10;

int n, k, fa[maxn], ans;
vector <int> G[maxn];
int dfs(int x, int d)
{
	int mxd = d;
	for (int y : G[x])
		mxd = max(mxd, dfs(y, d + 1));
	if (fa[x] != 1 && mxd - d + 1 >= k)
	{
		ans++;
		return 0;
	}
	return mxd;
}
int main()
{
#ifdef CraZYali
	freopen("2044.in", "r", stdin);
	freopen("2044.out", "w", stdout);
#endif
	cin >> n >> k;
	REP(i, 1, n)
	{
		scanf("%d", fa + i);
		if (i == 1)
		{
			if (fa[1] ^ 1) ans = fa[1] = 1;
		}
		else G[fa[i]].emplace_back(i);
	}
	dfs(1, 0);
	cout << ans << endl;
	return 0;
}
