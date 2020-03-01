/*
	Problem:	5292.cpp
	Time:		2020-03-01 14:18
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <ctime>
#include <cstring>
#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 5000 + 10, maxm = 500000 + 10;

int bg[maxn], ne[maxm << 1], to[maxm << 1], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

vector <int> G[maxn];
inline void Add(int x, int y)
{
	G[x].emplace_back(y);
	G[y].emplace_back(x);
}
template <typename T>
inline T read()
{
	T ans = 0, flag = 1;
	char c = getchar();
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

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, m, q, vis[maxn];
char s[maxn];
bool flag, good[maxn][maxn];
void dfs(int x)
{
	for (int i = bg[x]; i; i = ne[i]) if (s[to[i]] == s[x])
		if (vis[to[i]] < 0)
		{
			Add(x, to[i]);
			vis[to[i]] = !vis[x];
			dfs(to[i]);
		}
		else if (vis[to[i]] == vis[x]) flag = 0;
}

int fa[maxn];
int find(int x) {return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);}
inline void uni(int x, int y) {fa[find(x)] = find(y);}
pair <int, int> Q[maxn * maxn];int head, tail;
int main()
{
#ifdef CraZYali
	file("5292");
#endif
	n = read<int>();m = read<int>();q = read<int>();
	REP(i, 1, n) fa[i] = i;
	scanf("%s", s + 1);
	while (m--)
	{
		int x(read<int>()), y(read<int>());
		add(x, y);add(y, x);
		if (s[x] != s[y] && find(x) != find(y))
		{
			Add(x, y);
			uni(x, y);
		}
	}
	memset(vis, -1, sizeof vis);
	REP(i, 1, n) if (vis[i] == -1)
	{
		flag = 1;
		vis[i] = 0;
		dfs(i);
		if (!flag) G[i].emplace_back(i);
	}
	tail = -1;
	REP(i, 1, n) Q[++tail] = {i, i}, good[i][i] = 1;
	REP(v, 1, n) for (int u : G[v]) if (s[u] == s[v]) Q[++tail] = {u, v}, good[u][v] = good[v][u] = 1;
	cerr << clock() *1. / CLOCKS_PER_SEC << endl;
	while (head <= tail)
	{
		int u = Q[head].first, v = Q[head].second;
		head++;
		/*
		   for (int i = bg[u]; i; i = ne[i])
		   for (int j = bg[v]; j; j = ne[j])
		   {
		   int U = to[i], V = to[j];
		   if (s[U] == s[V] && !good[U][V]) Q.emplace(U, V);
		   }
		   */
		for (int U : G[u]) for (int V : G[v]) if (s[U] == s[V] && !good[U][V])
		{
			Q[++tail] = {U, V};
			good[U][V] = good[V][U] = 1;
		}
	}
	cerr << clock() *1. / CLOCKS_PER_SEC << endl;
	while (q--)
	{
		int x(read<int>()), y(read<int>());
		puts(good[x][y] ? "YES" : "NO");
	}
	cerr << clock() *1. / CLOCKS_PER_SEC << endl;
	return 0;
}
