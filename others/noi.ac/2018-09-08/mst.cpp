#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 50, MOD = 1e9 + 7;

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
	else if (x / 10) write(x / 10);
	putchar(x % 10 + '0');
}

int m, n, k;

bool app[maxn * maxn / 2];

int dis[maxn], x[maxn], y[maxn];
int G[maxn][maxn];

int ans = 0;

bool in[maxn];

priority_queue <pair<int, int> >q;
bool Vis[maxn];

void calc()
{
	REP(i, 2, n) dis[i] = 1e9;
	REP(i, 1, n) Vis[i] = 0;
	while (!q.empty()) q.pop();
	q.push(make_pair(0, 1));
	while (!q.empty())
	{
		register int dist = -q.top().first;
		register int x = q.top().second;
		q.pop();
		if (dist > dis[x] || Vis[x]) continue;
		else
		{
			Vis[x] = 1;
			if (x ^ 1 && !app[dist]) return;
			REP(i, 1, n)
				if (!Vis[i] && G[x][i] && dis[i] > G[x][i]) q.push(make_pair(-(dis[i] = G[x][i]), i));
		}
	}
	ans++;
	if (ans >= MOD) ans %= MOD;
}

bool vis[maxn * maxn / 2];

int T;

void dfs(int u)
{
	if (u == T) calc();
	else
	{
		u++;
		REP(i, 1, T)
			if (!vis[i])
			{
				vis[i] = 1;
				G[x[u]][y[u]] = G[y[u]][x[u]] = i;
				dfs(u);
				vis[i] = 0;
			}
	}
}

int main()
{
#ifdef CraZYali
	freopen("mst.in", "r", stdin);
	freopen("mst.out", "w", stdout);
#endif
	cin >> n;
	T = n * (n - 1) / 2;
	REP(i, 2, n) app[read<int>()] = 1;

	register int now = 0;
	REP(i, 1, n)
		REP(j, i + 1, n)
		{
			now++;
			x[now] = i;
			y[now] = j;
		}

	dfs(0);
	cout << ans % MOD;

	return 0;
}
