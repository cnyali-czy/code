#define REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <unordered_map>
#include <vector>
#include <cmath>

using namespace std;
const int maxn = 1e4 + 10, maxm = 1e5 + 10;
int bg[maxn], ne[maxm], to[maxm], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

template <typename T> T read()
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

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

int m, n, k;
vector <int> G[maxn];
int dfn[maxn], low[maxn], dfs_clock, stack[maxn], top, blg[maxn], cnt, v[maxn];
bool vis[maxn];

void dfs(int x)
{
	dfn[x] = low[x] = ++dfs_clock;
	vis[x] = 1;
	stack[++top] = x;
	for (int i = bg[x]; i; i = ne[i])
		if (!dfn[to[i]])
		{
			dfs(to[i]);
			chkmin(low[x], low[to[i]]);
		}
		else if (vis[to[i]]) chkmin(low[x], dfn[to[i]]);
	if (low[x] == dfn[x])
	{
		cnt++;
		while (1)
		{
			int u = stack[top--];
			blg[u] = cnt;
			vis[u] = 0;
			if (x == u) break;
		}
	}
}
int V[maxn];
unordered_map <int, bool> E[maxn];
int dp[maxn], q[maxn], head, tail, in[maxn];

int main()
{
#ifdef CraZYali
	file("3387-new");
#endif
	n = read<int>();m = read<int>();
	REP(i, 1, n) v[i] = read<int>();
	while (m--)
	{
		int x = read<int>(), y = read<int>();
		add(x, y);
	}
	REP(i, 1, n) if (!dfn[i]) dfs(i);
	REP(i, 1, n) V[blg[i]] += v[i];
	swap(v, V);
	REP(x, 1, n)
		for (int i = bg[x]; i; i = ne[i]) if (!E[blg[x]][blg[to[i]]] && blg[x] != blg[to[i]])
		{
			E[blg[x]][blg[to[i]]] = 1;
			G[blg[x]].push_back(blg[to[i]]);
			in[blg[to[i]]]++;
		}
	tail = -1;
	REP(i, 1, cnt)
	{
		dp[i] = v[i];
		if (!in[i]) q[++tail] = i;
	}
	while (head <= tail)
	{
		int x = q[head++];
		for (int y : G[x])
		{
			chkmax(dp[y], v[y] + dp[x]);
			if (!(--in[y])) q[++tail] = y;
		}
	}
	int ans = dp[1];
	REP(i, 2, cnt) chkmax(ans, dp[i]);
	cout << ans << endl;
	return 0;
}
