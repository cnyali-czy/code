#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 3000 + 10, maxE = maxn * maxn, maxm = maxn * maxn;

int m, n, k;

int f[maxn];
int find(int x) {return f[x] == x ? f[x] : f[x] = find(f[x]);}

struct Graph
{
	int bg[maxn], ne[maxE << 1], to[maxE << 1], w[maxE << 1], e = 1;
	
	inline void add(int x, int y, int z = 0)
	{
		e++;
		to[e] = y;
		ne[e] = bg[x];
		bg[x] = e;
		w[e] = z;
	}
}Tree, Que;

int lca[maxn];
bool vis[maxn];

void dfs(int x)
{
	vis[f[x] = x] = 1;
	for (register int i = Tree.bg[x]; i ; i = Tree.ne[i])
		if (!vis[Tree.to[i]])
		{
			dfs(Tree.to[i]);
			f[Tree.to[i]] = x;
		}
	for (register int i = Que.bg[x]; i ; i = Que.ne[i])
		if (vis[Que.to[i]]) lca[Que.w[i]] = find(Que.to[i]);
}

bool is[maxn];

long long ans[maxn];

template <typename T> T read()
{
	T lca(0), p(1);
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		lca = lca * 10 + c - 48;
		c = getchar();
	}
	return lca * p;
}

int main()
{
	freopen("b.in", "r", stdin);
	freopen("b.out", "w", stdout);
	cin >> n >> m;
	REP(i, 1, n) is[i] = read<int>();
	REP(i, 2, n)
	{
		register int x, y;
		scanf("%d%d", &x, &y);
		Tree.add(x, y);Tree.add(y, x);
	}
	while (m --> 0)
	{
		register int x, y;
		scanf("%d%d", &x, &y);
		if (x == 2) is[y] ^= 1;
		else
		{
			memset(Que.bg, 0, sizeof(Que.bg));
			REP(i, 1, n) vis[f[i] = i] = 0;
			Que.e = 1;
			int CNT(0);
			REP(i, 1, n)
				if (is[i])
				{
					++CNT;
					Que.add(i, y, CNT);
					Que.add(y, i, CNT);
				}
			dfs(1);
			CNT = 0;
			REP(i, 1, n) if (is[i]) ans[lca[++CNT]] += i;
		}
	}
	REP(i, 1, n) printf("%lld\n", ans[i]);
	return 0;
}
