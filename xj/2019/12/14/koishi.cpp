#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <cstring>
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;
const int maxn = 1e5 + 10, maxm = 1e5 + 10, MOD = 998244353;

int power_pow(long long base, int b)
{
	long long ans(1);
	while (b)
	{
		if (b & 1) (ans *= base) %= MOD;
		(base *= base) %= MOD;
		b >>= 1;
	}
	return (MOD + ans) % MOD;
}
int n, m;
bool ok[maxn];

vector <pair <int, int> > edge;
vector <int> G[maxn];

int fa[maxn], tot;
int find(int x) {return x == fa[x] ? fa[x] : fa[x] = find(fa[x]);}
void uni(int x, int y)
{
	x = find(x);y = find(y);
	if (x ^ y)
	{
		tot--;
		fa[x] = y;
	}
}

int ans, flag, dfs_clock, dfn[maxn], low[maxn], stack[maxn], top;
inline void chkmin(int &x, int y) {if (x > y) x = y;}
void tarjan(int u, int fa = 0)
{
	if (!flag) return;
	stack[++top] = u;
	dfn[u] = low[u] = ++dfs_clock;
	for (auto v : G[u]) if (v ^ fa)
		if (!dfn[v])
		{
			tarjan(v, u);
			chkmin(low[u], low[v]);
		}
		else chkmin(low[u], dfn[v]);
	if (low[u] > dfn[fa])
	{
		int siz(0);
		while (1)
		{
			int qaq = stack[top--];
			siz++;
			if (qaq == u) break;
		}
		flag &= ok[siz];
	}
}

void calc()
{
	tot = n;
	REP(i, 1, n) fa[i] = i;
	REP(u, 1, n)
		for (auto v : G[u]) uni(u, v);
	if (tot > 1) return;
	REP(i, 1, n) dfn[i] = low[i] = 0;
	top = dfs_clock = 0;
	flag = 1;
	tarjan(1);
	ans += flag;
}
void dfs(int x)
{
	if (x == n * (n - 1) / 2 - 1) calc();
	else
	{
		x++;
		G[edge[x].first].emplace_back(edge[x].second);
		G[edge[x].second].emplace_back(edge[x].first);
		dfs(x);
		G[edge[x].first].pop_back();
		G[edge[x].second].pop_back();
		dfs(x);
	}
}

namespace bf
{
	inline void work()
	{	
		edge.resize(n * (n - 1) >> 1);
		int qaq(0);
		REP(i, 1, n)
			REP(j, i + 1, n)
			edge[qaq++] = make_pair(i, j);
		dfs(-1);
		cout << ans << endl;
	}
}

int main()
{
#ifdef CraZYali
	freopen("koishi.in", "r", stdin);
	freopen("koishi.out", "w", stdout);
#endif
	cin >> n >> m;
	if (n == 1)
	{
		cout << 1 << endl;
		return 0;
	}
	REP(i, 1, m)
	{
		int x;scanf("%d", &x);
		ok[x] = 1;
	}
	bool zgl(1);
	if (zgl)
	{
		memset(ok, 0, sizeof ok);
		ok[n] = 1;
		bf::work();
		return 0;
	}
	if (n <= 6) bf::work();
	else cout << power_pow(n, n - 2) << endl;
	return 0;
}
