#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 10000 + 10, maxm = 50000 + 10;

int bg[maxn], ne[maxn << 1], to[maxn << 1], w[maxn << 1], e = 1;
inline void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
}

struct Edge
{
	int x, y, limit;
}E[maxm];
bool cmp(Edge A, Edge B) {return A.limit > B.limit;}

int fa[maxn];
int find(int x) {return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);}

int n, m, k;

int grand[maxn][20], Min[maxn][20], depth[maxn];

bool vis[maxn];

void pre(int x)
{
	vis[x] = 1;
	for (register int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ grand[x][0])
		{
			depth[to[i]] = depth[grand[to[i]][0] = x] + 1;
			Min[to[i]][0] = w[i];
			pre(to[i]);
		}
}

int main()
{
#ifdef CraZYali
	freopen("1967.in", "r", stdin);
	freopen("1967.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, n) fa[i] = i;
	REP(i, 1, m) scanf("%d%d%d", &E[i].x, &E[i].y, &E[i].limit);
	sort(E + 1, E + 1 + m, cmp);
	
	int al(0);
	REP(i, 1, m)
		if (find(E[i].x) ^ find(E[i].y))
		{
			fa[find(E[i].x)] = find(E[i].y);
			add(E[i].x, E[i].y, E[i].limit);
			add(E[i].y, E[i].x, E[i].limit);
			al++;
			if (al == n - 1) break;
		}

	memset(Min, 127, sizeof (Min));

	int Max = log(n) / log(2);

	REP(i, 1, n)
		if (!vis[i])
		{
			depth[i] = 1;
			pre(i);
			Min[i][0] = 1e9;
		}

	REP(j, 1, Max)
		REP(i, 1, n)
		{
			grand[i][j] = grand[grand[i][j-1]][j-1];
			Min[i][j] = min(Min[i][j-1], Min[grand[i][j-1]][j-1]);
		}

	register int q;
	cin >> q;

	while (q --> 0)
	{
		register int x, y, ans(1e9);
		scanf("%d%d", &x, &y);
		if (find(x) ^ find(y)) {printf("-1\n");continue;}
		if (depth[x] < depth[y]) swap(x, y);
		DREP(i, Max, 0)
			if (depth[grand[x][i]] >= depth[y])
			{
				chkmin(ans, Min[x][i]);
				x = grand[x][i];
			}
		if (x ^ y)
		{
			DREP(i, Max, 0)
				if (grand[x][i] ^ grand[y][i])
				{
					chkmin(ans, min(Min[x][i], Min[y][i]));
					x = grand[x][i];
					y = grand[y][i];
				}
			chkmin(ans, min(Min[x][0], Min[y][0]));
		}
		printf("%d\n", ans == 1000000000 ? -1 : ans);
	}
	return 0;
}
