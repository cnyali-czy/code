#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <queue>
#include <map>
#include <set>

using namespace std;
const int maxn = 100000 + 10, maxm = 100000 + 10;

int bg[maxn], ne[maxm << 1], to[maxm << 1], e = 1;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

int m, n, k;

int root;

int dfn[maxn], pre[maxn];
int dfs_clock;

bool iscut[maxn];

int dfs(int u, int fa)
{
	int lowu = pre[u] = ++dfs_clock;
	int child_cnt(0);
	for (register int i = bg[u]; i ; i = ne[i])
		if (!pre[to[i]])
		{
			child_cnt++;
			int lowv = dfs(to[i], u);
			chkmin(lowu, lowv);
			if (lowv >= pre[u]) iscut[u] = 1;
		}
		else if (pre[to[i]] < pre[u] && to[i] ^ fa) chkmin(lowu, pre[to[i]]);
	if (u == root && child_cnt == 1) iscut[u] = 0;
	return lowu;
}

int main()
{
#ifdef CraZYali
	freopen("3388.in", "r", stdin);
	freopen("3388.out", "w", stdout);
#endif
	cin >> n >> m;
	while (m --> 0)
	{
		register int x, y;
		scanf("%d%d", &x, &y);
		add(x, y);
		add(y, x);
	}
	REP(i, 1, n)
		if (!dfn[i]) dfs(root = i, -1);
	int cnt(0);
	REP(i, 1, n) if (iscut[i]) cnt++;
	printf("%d\n", cnt);
	REP(i, 1, n) if (iscut[i]) printf("%d ", i);
	return 0;
}
