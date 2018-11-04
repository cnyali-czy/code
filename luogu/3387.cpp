#define  REP(i, s, e) for (register int i = s; i <= e; i++)
#define DREP(i, s, e) for (register int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 1e4 + 10, maxm = 1e5 + 10;

template <typename T> T read()
{
	T ans = 0, p = 1;
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

int n, m, k;

struct Graph
{
	int bg[maxn], ne[maxm], to[maxm], e;
	inline void add(int x, int y)
	{
		e++;
		to[e] = y;
		ne[e] = bg[x];
		bg[x] = e;
	}
	int pre[maxn], low[maxn], dfs_clock;
	bool vis[maxn];stack <int> s;
	int belong[maxn], cnt;
	void dfs(int u)
	{
		pre[u] = low[u] = ++dfs_clock;
		vis[u] = 1;s.push(u);
		for (register int i = bg[u]; i ; i = ne[i])
			if (!pre[to[i]])
			{
				dfs(to[i]);
				chkmin(low[u], low[to[i]]);
			}
			else if (vis[to[i]]) chkmin(low[u], low[to[i]]);
		if (low[u] == pre[u])
		{
			cnt++;
			while (1)
			{
				belong[s.top()] = cnt;
				vis[s.top()] = 0;
				if (s.top() == u) break;
				s.pop();
			}
			s.pop();
		}			
	}
	void tarjan() {REP(i, 1, n) if (!pre[i]) dfs(i);}
	int w[maxn];
}Gt, G;

map <int, bool> M[maxn];
int in[maxn];

int q[maxn], head = 1, tail;
int dp[maxn];

int main()
{
#ifdef CraZYali
	freopen("3387.in", "r", stdin);
	freopen("3387.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, n) Gt.w[i] = read<int>();
	while (m --> 0)
	{
		register int x = read<int>(), y = read<int>();
		Gt.add(x, y);
	}
	Gt.tarjan();
	REP(i, 1, n) G.w[Gt.belong[i]] += Gt.w[i];
	REP(x, 1, n)
		for (register int i = Gt.bg[x]; i ; i = Gt.ne[i])
		{
			register int X = Gt.belong[x], Y = Gt.belong[Gt.to[i]];
			if (X != Y && !M[X][Y])
			{
				M[X][Y] = 1;
				G.add(X, Y);
				in[Y]++;
			}
		}
	int N = Gt.cnt;
	REP(i, 1, N)
		if (!in[i]) q[++tail] = i;
	REP(i, 1, N) dp[i] = G.w[i];
	while (head <= tail)
	{
		register int x = q[head++];
		for (register int i = G.bg[x]; i ; i = G.ne[i])
		{
			in[G.to[i]]--;
			chkmax(dp[G.to[i]], dp[x] + G.w[G.to[i]]);
			if (!in[G.to[i]]) q[++tail] = G.to[i];
		}
	}
	int ans = dp[1];
	REP(i, 2, N) chkmax(ans, dp[i]);
	cout << ans;
	return 0;
}
