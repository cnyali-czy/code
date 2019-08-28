#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUmaxnCTIOmaxn__, __LImaxnE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 600000 + 10, inf = 1e9, MOD = 1e9 + 7;
int n, m, f[maxn], siz[maxn], x;

int bg[maxn], cur[maxn], ne[maxn], to[maxn], e = 1;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

bool vis[maxn];
void dfs(int x)
{
	for (int &i = cur[x]; i ; i = ne[i])
	{
		if (vis[i]) continue;
		vis[i] = vis[i ^ 1] = 1;
		if (to[i] == x + n) f[x] = -1;
		if (to[i] == x - n) f[to[i]] = 1;
		dfs(to[i]);
	}
}
signed main()
{
#ifdef CraZYali
	freopen("F.in", "r", stdin);
	freopen("F.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n + n)
	{
		int x;
		scanf("%d", &x);
		x = x == -1 ? 0 : x;
		if (x && i > n) x += n;
		add(i, x);add(x, i);
		siz[x]++;
	}
	REP(i, 1, n) if ((siz[i] + siz[i + n]) & 1)
	{
		puts("IMPOSSIBLE");
		return 0;
	}
	REP(i, 1, n) if (!(siz[i] & 1))
		add(i, i + n), add(i + n, i);
	f[0] = -1;
	copy(bg, bg + n + n + 1, cur);
	dfs(0);
	puts("POSSIBLE");
	REP(i, 1, n) printf("%d%c", f[i], i == n ? '\n' : ' ');
	return 0;
}
