#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>
#include <queue>
#include <stack>
#include <set>

using namespace std;
const int maxn = 100010, maxm = 1000000 + 10;

int pre[maxn], low[maxn], dfs_clock;

bool vis[maxn];
stack <int> s;

int cnt, belong[maxn];

struct Graph
{
	int bg[maxn], e;
	vector <int> ne, to;
	Graph() {ne.push_back(0);to.push_back(0);}
	inline void add(int x, int y)
	{
		e++;
		to.push_back(y);
		ne.push_back(bg[x]);
		bg[x] = e;
	}
}G1, G2;

void dfs(int u)
{
	pre[u] = low[u] = ++dfs_clock;
	s.push(u);
	vis[u] = 1;
	for (register int i = G1.bg[u]; i ; i = G1.ne[i])
		if (!pre[G1.to[i]])
		{
			dfs(G1.to[i]);
			chkmin(low[u], low[G1.to[i]]);
		}
		else if (vis[G1.to[i]])
			chkmin(low[u], low[G1.to[i]]);
	if (low[u] == pre[u])
	{
		belong[u] = ++cnt;
		vis[u] = 0;
		while (s.top() ^ u)
		{
			register int x = s.top();
			s.pop();
			belong[x] = cnt;
			vis[x] = 0;
		}
		s.pop();
	}
}
int n, m, MOD;
int in[maxn], A[maxn], now;

queue <int> q;

int size[maxn], dp[maxn];

set <pair <int, int> > S;

int g[maxn];

int main()
{
#ifdef CraZYali
	freopen("2272.in", "r", stdin);
	freopen("2272.out", "w", stdout);
#endif
	cin >> n >> m >> MOD;
	while (m --> 0)
	{
		register int x, y;
		scanf("%d%d", &x, &y);
		G1.add(x, y);
	}
	REP(i, 1, n)
		if (!pre[i]) dfs(i);
	REP(i, 1, n) size[belong[i]]++;
	REP(x, 1, n)
		for (register int i = G1.bg[x]; i ; i = G1.ne[i])
			if (belong[x] ^ belong[G1.to[i]] && S.find(make_pair(belong[x], belong[G1.to[i]])) == S.end())
			{
				S.insert(make_pair(belong[x], belong[G1.to[i]]));
				in[belong[G1.to[i]]]++;
				G2.add(belong[x], belong[G1.to[i]]);
			}
	REP(i, 1, cnt)
		if (!in[i])
		{
			dp[i] = size[i];
			g[i] = 1;
			q.push(i);
		}
	while (!q.empty())
	{
		register int x = q.front();
		q.pop();
		A[++now] = x;
		for (register int i = G2.bg[x]; i ; i = G2.ne[i])
			if (in[G2.to[i]])
			{
				in[G2.to[i]]--;
				if (!in[G2.to[i]]) q.push(G2.to[i]);
			}	
	}

	REP(i, 1, n)
	{
		register int x = A[i];
		for (register int i = G2.bg[x]; i ; i = G2.ne[i])
			if (dp[G2.to[i]] < dp[x] + size[G2.to[i]])
			{
				dp[G2.to[i]] = dp[x] + size[G2.to[i]];
				g[G2.to[i]] = g[x];
			}
			else if (dp[G2.to[i]] == dp[x] + size[G2.to[i]]) 
				g[G2.to[i]] = (g[G2.to[i]] + g[x]) % MOD;
	}

	int Max = dp[1];
	REP(i, 2, cnt) chkmax(Max, dp[i]);
	printf("%d\n", Max);

	int ans = 0;
	REP(i, 1, cnt)
		if (dp[i] == Max) ans = (ans + g[i]) % MOD;
	cout << (ans + MOD) % MOD;

	return 0;
}
