#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %lld\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>
#include <bits/extc++.h>
#define int long long

using namespace std;
const int maxn = 100000 + 10, maxm = 200000 + 10, inf = 1ll << 50ll;

template <typename T> inline T read()
{
	T ans(0), p(1);
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}

template <typename T> void write(T x)
{
	if (x < 0) putchar('-'), write(-x);
	else
	{
		if (x / 10) write(x / 10);
		putchar(x % 10 + '0');
	}
}

int m, n, k, MOD;

struct node
{
	int x, y;
	node(){}
	node(int _x, int _y = 0) : x(_x), y(_y) {}
	bool operator < (node B) const {return y > B.y;}
};
__gnu_pbds::priority_queue <node> q;
int dis[maxn];
struct Graph
{
	int bg[maxn], ne[maxm], to[maxm], w[maxm], e;
	void init() {e = 0;REP(i, 1, n) bg[i] = 0;}
	inline void add(int x, int y, int z)
	{
		e++;
		to[e] = y;
		ne[e] = bg[x];
		bg[x] = e;
		w[e] = z;
	}
	bool v[maxn];
	void dij(int root)
	{
		REP(i, 1, n) dis[i] = inf, v[i] = 0;
		dis[root] = 0;while (!q.empty()) q.pop();
		q.push(node(root,0));
		while (!q.empty())
		{
			register int x = q.top().x, y = q.top().y;
			q.pop();
			if (v[x]) continue;v[x] = 1;
			for (register int i = bg[x]; i ; i = ne[i])
				if (dis[to[i]] > dis[x] + w[i]) q.push(node(to[i], dis[to[i]] = dis[x] + w[i]));
		}
	}
}G, S;

int dp[maxn][51];
bool flag, vis[maxn][51];

int dfs(int now, int k)
{
	if (~dp[now][k]) return dp[now][k];
	if (now == 1 && !k) dp[now][k] = 1;
	else dp[now][k] = 0;
	vis[now][k] = 1;
	for (register int i = S.bg[now]; i ; i = S.ne[i])
	{
		int temp = dis[now] + k - S.w[i] - dis[S.to[i]];
		if (temp >= 0)
		{
			if (vis[S.to[i]][temp]) flag = 1;
			dp[now][k] = (dp[now][k] + dfs(S.to[i], temp)) % MOD;
		}
	}
	vis[now][k] = 0;
	return dp[now][k];
}

signed main()
{
#ifdef CraZYali
	freopen("3953.in", "r", stdin);
	freopen("3953.out", "w", stdout);
#endif
	register int T = read<int>();
	while (T --> 0)
	{
		n = read<int>();m = read<int>();k = read<int>();MOD = read<int>();
		G.init();S.init();
		while (m --> 0)
		{
			register int x = read<int>(), y = read<int>(), z = read<int>();
			G.add(x, y, z);S.add(y, x, z);
		}
		G.dij(1);
		memset(dp, -1, sizeof(dp));
		flag = 0;int ans = 0;
		REP(i, 0, k) ans = (ans + dfs(n, i)) % MOD;
		printf("%lld\n", flag ? -1 : ans);
	}
	return 0;
}
