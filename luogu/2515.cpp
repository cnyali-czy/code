#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 100 + 5, maxm = 500 + 5;

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

int n, m, w[maxn], v[maxn], d[maxn];
int bg[maxn], ne[maxm], to[maxm], e;
void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}
void clear()
{
	e = 0;
	REP(i, 1, n) bg[i] = 0;
}

int s[maxn], top, dfn[maxn], low[maxn], dfs_clock;
bool ins[maxn];

int belong[maxn], belong_cnt = 1, W[maxn], V[maxn];

void dfs(int u)
{
	dfn[u] = low[u] = ++dfs_clock;
	ins[s[++top] = u] = 1;
	for (int i = bg[u]; i ; i = ne[i])
		if (!dfn[to[i]])
		{
			dfs(to[i]);
			chkmin(low[u], low[to[i]]);
		}
		else if (ins[to[i]]) chkmin(low[u], low[to[i]]);
	if (dfn[u] == low[u])
	{
		belong[u] = ++belong_cnt;
		while (s[top + 1] ^ u)
		{
			belong[s[top]] = belong_cnt;
			W[belong_cnt] += w[s[top]];
			V[belong_cnt] += v[s[top]];
			ins[s[top--]] = 0;
		}
	}
}
int in[maxn], dp[maxm][maxm];

void solve(int x)
{
	REP(i, W[x], m) dp[x][i] = V[x];
	for (int i = bg[x]; i ; i = ne[i])
	{
		int v = to[i];
		solve(v);
		DREP(i, m - W[x], 0)
			REP(j, 0, i)
			chkmax(dp[x][i + W[x]], dp[v][j] + dp[x][i + W[x] - j]);
	}
}

int main()
{
#ifdef CraZYali
	freopen("2515.in", "r", stdin);
	freopen("2515.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, n) w[i] = read<int>();
	REP(i, 1, n) v[i] = read<int>();
	REP(i, 1, n) add(d[i] = read<int>(), i);
	REP(i, 1, n) if (!dfn[i]) dfs(i);
	clear();
	belong[0] = 1;
	REP(i, 1, n)
		if (belong[d[i]] ^ belong[i])
		{
			add(belong[d[i]], belong[i]);
			in[belong[i]]++;
		}
	REP(i, 2, belong_cnt)
		if (!in[i]) add(1, i);
	solve(1);
#ifdef CraZYali
	REP(i, 1, belong_cnt) printf("%d %d\n", W[i], V[i]);
	cout<<endl;
	REP(x, 1, belong_cnt)
		for (int i = bg[x]; i ; i = ne[i]) printf("%d %d\n", x-1,to[i]-1);
#endif
	cout << dp[1][m] << endl;
	return 0;
}
