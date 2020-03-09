#include <bits/stdc++.h>

template <class T>
inline void read(T &res)
{
	res = 0; bool bo = 0; char c;
	while (((c = getchar()) < '0' || c > '9') && c != '-');
	if (c == '-') bo = 1; else res = c - 48;
	while ((c = getchar()) >= '0' && c <= '9')
		res = (res << 3) + (res << 1) + (c - 48);
	if (bo) res = ~res + 1;
}

template <class T>
inline T Max(const T &a, const T &b) {return a > b ? a : b;}

template <class T>
inline T Min(const T &a, const T &b) {return a < b ? a : b;}

const int N = 2e5 + 5, M = N << 1, L = N + M, INF = 0x3f3f3f3f;

int n, m, ecnt, nxt[M], adj[N], go[M], op[L], kt[L], ans[L], fl[L], fr[L], sze[N],
ms[N], to[L], tot, et[L], fi[N], qt, que[L], A[L], mark[N];
bool vis[N];

std::vector<int> pt[N], eg[M];

void change(int x, int v)
{
	for (; x <= m; x += x & -x)
		A[x] += v;
}

int ask(int x)
{
	int res = 0;
	for (; x; x -= x & -x)
		res += A[x];
	return res;
}

void clean(int x)
{
	for (; x <= m; x += x & -x)
		A[x] = 0;
}

void add_edge(int u, int v)
{
	nxt[++ecnt] = adj[u]; adj[u] = ecnt; go[ecnt] = v;
	nxt[++ecnt] = adj[v]; adj[v] = ecnt; go[ecnt] = u;
}

int siz[N], Mx[N], allnode, rt;
void findrt(int u, int fu)
{
	siz[u] = 1;Mx[u] = 0;
	for (int e = adj[u], v = go[e]; e; v = go[e = nxt[e]]) if (v ^ fu && !vis[v])
	{
		findrt(v, u);
		siz[u] += siz[v];
		Mx[u] = Max(Mx[u], siz[v]);
	}
	Mx[u] = Max(Mx[u], allnode - siz[u]);
	if (!rt || Mx[u] < Mx[rt]) rt = u;
}
void dfs1(int u, int fu)
{
	sze[u] = 1; ms[u] = 0;
	for (int e = adj[u], v; e; e = nxt[e])
		if ((v = go[e]) != fu && !vis[v]) dfs1(v, u),
			sze[u] += sze[v], ms[u] = Max(ms[u], sze[v]);
}

void dfs2(int u, int fu, int r, int &G)
{
	if (Max(ms[u], sze[r] - sze[u]) < Max(ms[G], sze[r] - sze[G]))
		G = u;
	for (int e = adj[u], v; e; e = nxt[e])
		if ((v = go[e]) != fu && !vis[v])
			dfs2(v, u, r, G);
}

int findG(int u) {int G = u; dfs1(u, 0); dfs2(u, 0, u, G); return G;}

void calc(int u, int fu, int fe)
{
	for (int i = 0; i < pt[u].size(); i++) que[++qt] = pt[u][i];
	mark[u] = -1; fi[u] = INF;
	for (int e = adj[u], v; e; e = nxt[e])
		if ((v = go[e]) != fu && !vis[v])
		{
			for (int i = 0; i < eg[e].size(); i++)
			{
				int x = eg[e][i], t;
				if (fu) fl[x] = (t = std::lower_bound(eg[fe].begin(), eg[fe].end(), x)
					- eg[fe].begin(), t == eg[fe].size() ? INF : fl[eg[fe][t]]),
					fr[x] = (t = std::lower_bound(eg[fe].begin(), eg[fe].end(), x)
					- eg[fe].begin() - 1, t == -1 ? -INF : fr[eg[fe][t]]);
				else fl[x] = fr[x] = x;
				to[x] = v; et[++tot] = x;
			}
			calc(v, u, e);
		}
}

void calc2(int u, int fu, int fe)
{
	for (int i = 0; i < pt[u].size(); i++) que[++qt] = pt[u][i];
	mark[u] = -1; fi[u] = INF;
	for (int i = 0; i < eg[fe].size(); i++) et[++tot] = eg[fe][i];
	for (int e = adj[u], v; e; e = nxt[e])
		if ((v = go[e]) != fu && !vis[v])
			calc2(v, u, e);
}

void djqtxdy(int u)
{
	if (!allnode) allnode = n;else allnode = siz[u];
	rt = 0;
	findrt(u, 0);
	u = rt;
	vis[u] = 1;
	tot = qt = 0; calc(u, 0, 0); fi[u] = 1;
	for (int i = 1; i <= tot; i++) fi[to[et[i]]] = Min(fi[to[et[i]]], fl[et[i]]);
	std::sort(que + 1, que + qt + 1);
	std::sort(et + 1, et + tot + 1);
	for (int i = 1, j = 1; i <= qt; i++)
	{
		while (j <= tot && et[j] <= que[i])
		{
			if (mark[to[et[j]]] != -1) change(m - mark[to[et[j]]] + 1, -1);
			if (fr[et[j]] > 0) change(m - fr[et[j]] + 1, 1),
				mark[to[et[j]]] = fr[et[j]];
			j++;
		}
		if (fi[kt[que[i]]] <= que[i]) ans[que[i]] += ask(m - fi[kt[que[i]]] + 1) + 1;
	}
	for (int i = 1; i <= tot; i++) if (fr[et[i]] > 0) clean(m - fr[et[i]] + 1);
	for (int e = adj[u], v = go[e]; e; e = nxt[e], v = go[e])
		if (!vis[v])
		{
			tot = qt = 0; calc2(v, u, e);
			for (int i = 1; i <= tot; i++)
				fi[to[et[i]]] = Min(fi[to[et[i]]], fl[et[i]]);
			std::sort(que + 1, que + qt + 1);
			std::sort(et + 1, et + tot + 1);
			for (int i = 1, j = 1; i <= qt; i++)
			{
				while (j <= tot && et[j] <= que[i])
				{
					if (mark[to[et[j]]] != -1) change(m - mark[to[et[j]]] + 1, -1);
					if (fr[et[j]] > 0) change(m - fr[et[j]] + 1, 1),
						mark[to[et[j]]] = fr[et[j]];
					j++;
				}
				if (fi[kt[que[i]]] <= que[i])
					ans[que[i]] -= ask(m - fi[kt[que[i]]] + 1);
			}
			for (int i = 1; i <= tot; i++) if (fr[et[i]] > 0)
				clean(m - fr[et[i]] + 1);
		}
	for (int e = adj[u], v = go[e]; e; e = nxt[e], v = go[e])
		if (!vis[v]) djqtxdy(v);
}

int main()
{
	int x, y;
	read(n); read(m);
	if (n > 30000) return 0;
	for (int i = 1; i < n; i++) read(x), read(y), add_edge(x, y);
	for (int i = 1; i <= m; i++)
		if (read(op[i]), read(x), kt[i] = x, op[i] == 1) pt[x].push_back(i);
		else eg[x << 1].push_back(i), eg[(x << 1) - 1].push_back(i);
	djqtxdy(1);
	for (int i = 1; i <= m; i++) if (op[i] == 1) printf("%d\n", ans[i]);
	return 0;
}
