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
#include <queue>
#include <vector>
#include <cmath>
#define i64 long long
using namespace std;
const int maxn = 2e5 + 10;

int bg[maxn], ne[maxn], to[maxn], e;
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
int M[maxn], fa[maxn];

int dfn[maxn], siz[maxn], dfs_clock;
bool ins(int x, int y)
{
	if (dfn[x] > dfn[y]) swap(x, y);
	return dfn[y] <= dfn[x] + siz[x] - 1;
}
i64 ans, dp[1 << 20];
int LG[1 << 20];

priority_queue <int> q[maxn];
void merge(int x, int y)
{
	if (q[x].size() < q[y].size()) swap(q[x], q[y]);
	priority_queue <int> tmp;
	while (!q[y].empty())
	{
		tmp.push(max(q[x].top(), q[y].top()));
		q[x].pop();q[y].pop();
	}
	while (!tmp.empty()) q[x].push(tmp.top()), tmp.pop();
}
void dfs(int x)
{
	for (int i = bg[x]; i; i = ne[i]) dfs(to[i]), merge(x, to[i]);
	q[x].push(M[x]);
}
int main()
{
#ifdef CraZYali
	file("5290");
#endif
	n = read<int>();
	REP(i, 1, n) M[i] = read<int>();
	REP(i, 2, n) add(fa[i] = read<int>(), i);
	dfs(1);
	while (!q[1].empty()) ans += q[1].top(), q[1].pop();
	cout << ans << endl;
	return 0;
}
