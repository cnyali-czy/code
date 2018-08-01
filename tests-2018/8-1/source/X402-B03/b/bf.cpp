#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 300000 + 10, maxE = maxn, maxm = maxn;

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

int ans[maxn];

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

map <pair<int, int> , int> LCA;

int AAA[maxn], BBB[maxn];

pair <int, int> opts[maxm];

bool need[maxn];

int ABC[maxn], DEF[maxn];
int ABCcnt, DEFcnt;

int main()
{
	freopen("b.in", "r", stdin);
	freopen("b.out", "w", stdout);
	cin >> n >> m;
	REP(i, 1, n) need[i] = is[i] = read<int>();
	REP(i, 2, n)
	{
		register int x, y;
		scanf("%d%d", &x, &y);
		Tree.add(x, y);Tree.add(y, x);
	}
	REP(i, 1, m) scanf("%d%d", &opts[i].first, &opts[i].second);
	int lca_cnt(0);
	REP(i, 1, m) if (opts[i].first == 2) need[opts[i].second] = 1;
	REP(i, 1, n) if (need[i]) ABC[++ABCcnt] = i;
	REP(i, 1, m) if (opts[i].first == 1) DEF[++DEFcnt] = opts[i].second;
	REP(i, 1, ABCcnt)
		REP(j, 1, DEFcnt)
		{
			++lca_cnt;
			Que.add(ABC[i], DEF[j], lca_cnt);
			Que.add(DEF[j], ABC[i], lca_cnt);
			AAA[lca_cnt] = ABC[i];
			BBB[lca_cnt] = DEF[j];
		}
	dfs(1);
	REP(i, 1, lca_cnt) LCA[make_pair(AAA[i], BBB[i])] = LCA[make_pair(BBB[i], AAA[i])] = lca[i];
	REP(i, 1, m)
		if (opts[i].first == 2) is[opts[i].second] ^= 1;
		else REP(j, 1, n) if (is[j]) ans[LCA[make_pair(j, opts[i].second)]] += j;
	REP(i, 1, n) printf("%d\n", ans[i]);
	return 0;
}
