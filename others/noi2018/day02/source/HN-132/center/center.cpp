#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <map>

using namespace std;
const int maxn = 5e4 + 10, maxE = maxn, maxm = 1e5 + 10, inf = 1e9;

struct Graph
{
	int bg[maxn << 1], ne[maxE << 1], to[maxE << 1], w[maxE << 1], e;
	inline void add(int x, int y, int z)
	{
		e++;
		to[e] = y;
		ne[e] = bg[x];
		bg[x] = e;
		w[e] = z;
	}
}Tree, Que;

int m, n, k;

int x[maxm], y[maxm], v[maxm];

int f[maxn];
inline int find(int x) {return x == f[x] ? x : f[x] = find(f[x]);}

bool vis[maxn];
int lca[maxm];

inline void dfs(int x)
{
	vis[f[x] = x] = 1;
	for (register int i = Tree.bg[x]; i ; i = Tree.ne[i])
		if (!vis[Tree.to[i]])
		{
			dfs(Tree.to[i]);
			f[Tree.to[i]] = x;
		}
	for (register int i = Que.bg[x]; i ;i = Que.ne[i])
		if (vis[Que.to[i]]) lca[Que.w[i]] = find(Que.to[i]);
}

int deep[maxn];
queue <int> q;
inline void BFS(int root)
{
	while (!q.empty()) q.pop();
	q.push(root);
	while (!q.empty())
	{
		register int x = q.front();
		q.pop();
		for (register int i = Tree.bg[x]; i ; i = Tree.ne[i])
			if (deep[Tree.to[i]] == -1)
			{
				deep[Tree.to[i]] = deep[x] + 1;
				q.push(Tree.to[i]);
			}
	}
}

bool mark1[maxn], mark2[maxn];

int father[maxn];

map <pair<int, int>, int> Get;

inline int markA(int id)
{
	register int getN = 0;

	register int top = lca[id];
	
	register int now;

	now = x[id];
	while (now ^ top)
	{
		getN += Get[make_pair(now, father[now])];
		mark1[now] = 1;
		now = father[now];
	}
	now = y[id];
	while (now ^ top)
	{
		getN += Get[make_pair(now, father[now])];
		mark1[now] = 1;
		now = father[now];
	}

	mark1[top] = 1;
	return getN;
}

inline int markB(int id)
{
	register int getN = 0;
	
	register int top = lca[id];
	
	register int now;

	now = x[id];
	while (now ^ top)
	{
		if (!mark1[now] || !mark1[father[now]]) getN += Get[make_pair(now, father[now])];
		mark2[now] = 1;
		now = father[now];
	}
	now = y[id];
	while (now ^ top)
	{
		if (!mark1[now] || !mark1[father[now]]) getN += Get[make_pair(now, father[now])];
		mark2[now] = 1;
		now = father[now];
	}

	mark2[top] = 1;
	return getN;
}

int main()
{
	freopen("center.in", "r", stdin);
	freopen("center.out", "w", stdout);
	register int T;
	cin >> T;
	while (T--)
	{
		scanf("%d", &n);
		REP(i, 1, n) Tree.bg[i] = Que.bg[i] = 0;
		Tree.e = Que.e = 0;
		Get.clear();
		REP(i, 2, n)
		{
			register int A, B, C;
			scanf("%d%d%d", &A, &B, &C);
			Tree.add(A, B, C);
			Tree.add(B, A, C);
			Get[make_pair(A, B)] = Get[make_pair(B, A)] = C;
		}
		scanf("%d", &m);
		REP(i, 1, m)
		{
			scanf("%d%d%d", x + i, y + i, v + i);
			Que.add(x[i], y[i], i);
			Que.add(y[i], x[i], i);
		}
		REP(i, 1, n) vis[i] = 0;
		dfs(1);

		REP(i, 2, n) deep[i] = -1;
		deep[1] = 0;
		BFS(1);
		
		father[1] = -1;
		REP(x, 2, n)
			for (register int i = Tree.bg[x]; i ; i = Tree.ne[i])
				if (deep[Tree.to[i]] < deep[x])
				{
					father[x] = Tree.to[i];
					break;
				}
		int ans = -inf;
		bool flag = 0;
		REP(i, 1, m - 1)
		{
			REP(FU, 1, n) mark1[FU] = 0;
			int AAA = markA(i);
			REP(j, i + 1, m)
			{
				REP(FU, 1, n) mark2[FU] = 0;
				int BBB = markB(j);
				REP(x, 2, n) if (mark1[x] && mark1[father[x]] && mark2[x] && mark2[father[x]])
				{
					flag = 1;
					chkmax(ans, AAA + BBB - v[i] - v[j]);
				}
			}
		}
		if (flag) printf("%d\n", ans);
		else printf("F\n");
	}

	return 0;
}
