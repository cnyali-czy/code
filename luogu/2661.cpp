#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>
#include <stack>

using namespace std;
const int maxn = 200000 + 10, maxm = maxn;

int bg[maxn], ne[maxm], to[maxm], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

int pre[maxn], low[maxn], dfs_clock;

stack <int> s;
bool vis[maxn];

int belong[maxn], scc_cnt;

void dfs(int u)
{
	pre[u] = low[u] = ++dfs_clock;
	s.push(u);
	vis[u] = 1;
	for (register int i = bg[u]; i ; i = ne[i])
		if (!pre[to[i]])
		{
			dfs(to[i]);
			chkmin(low[u], low[to[i]]);
		}
		else if (vis[to[i]]) chkmin(low[u], low[to[i]]);
	if (pre[u] == low[u])
	{
		belong[u] = ++scc_cnt;
		vis[u] = 0;
		while (s.top() ^ u)
		{
			register int x = s.top();
			s.pop();
			belong[x] = scc_cnt;
			vis[x] = 0;
		}
		s.pop();
	}
}

int m, n, k;

int size[maxn];

int main()
{
#ifdef CraZYali
	freopen("2661.in", "r", stdin);
	freopen("2661.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n)
	{
		scanf("%d", &k);
		add(i, k);
	}

	REP(i, 1, n)
		if (!pre[i]) dfs(i);

	REP(i, 1, n) size[belong[i]]++;
	int ans = 1e9;
	REP(i, 1, n) chkmin(ans, (size[belong[i]] ^ 1 ? size[belong[i]] : ans));
	cout << ans;
	return 0;
}
