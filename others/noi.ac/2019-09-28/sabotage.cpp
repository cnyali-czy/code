/*
 * File Name:	sabotage.cpp
 * Author	:	CraZYali
 * Year		:	2019.09.28 19:55
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;
const int maxn = 1e5 + 10, maxm = 1.5e5 + 10, maxq = 1e5 + 10;

vector <int> G[maxn], rG[maxn];
int deg[maxn];
inline void add(int x, int y)
{
	G[x].push_back(y);
}
inline void add_r(int x, int y)
{
	rG[x].push_back(y);
	deg[y]++;
}

template <typename T> inline T read()
{
	T ans(0), flag(1);
	char c(getchar());
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout);

int n, m, q;

int Q[maxn], head, tail;
inline void topsort()
{
	head = 1;
	REP(i, 1, n)
		if (!deg[i]) Q[++tail] = i;
	while (head <= tail)
	{
		int u(Q[head++]);
		for (int v : rG[u])
			if (!--deg[v]) Q[++tail] = v;
	}
}

int LOG, fa[maxn][17], depth[maxn];
inline int lca(int x, int y)
{
	if (!x || !y) return x + y;
	if (depth[x] < depth[y]) swap(x, y);
	DREP(i, LOG, 0)
		if (depth[fa[x][i]] >= depth[y]) x = fa[x][i];
	if (x == y) return x;
	DREP(i, LOG, 0)
		if (fa[x][i] ^ fa[y][i]) x = fa[x][i], y = fa[y][i];
	return fa[x][0];
}
inline void insert(int u)
{
	int &l = fa[u][0];l = 0;
	for (int v : G[u])
		l = lca(v, l);
	REP(i, 1, LOG) fa[u][i] = fa[fa[u][i-1]][i-1];
	depth[u] = depth[l] + 1;
}

int main()
{
#ifdef CraZYali
	file("sabotage");
#endif
	cin >> n >> m;
	while (m--)
	{
		int x(read<int>()), y(read<int>());
		add(x, y);
		add_r(y, x);
	}
	topsort();
	LOG = log2(n);
	REP(i, 1, n) insert(Q[i]);
	q = read<int>();
	while (q--)
		printf("%d\n", depth[lca(read<int>(), read<int>())]);
	return 0;
}
