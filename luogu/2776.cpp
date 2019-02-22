#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 1000 + 10, maxm = maxn * maxn, inf = 1e9;
int bg[maxn], ne[maxm << 1], to[maxm << 1], w[maxm << 1], cur[maxn << 1], e = 1;
inline void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	cur[e] = w[e] = z;
}

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
int n, a[maxn], dp[maxn], maxlen;

int S, T, N,q[maxn], head, tail, dis[maxn];

bool bfs()
{
	REP(i, 1, N) dis[i] = -1;
	dis[q[head = tail = 1] = S] = 0;
	while (head <= tail)
	{
		int x = q[head++];
		for (int i = bg[x]; i ; i = ne[i])
			if (w[i] > 0 && dis[to[i]] == -1) dis[q[++tail] = to[i]] = dis[x] + 1;
	}
	return dis[T] != -1;
}
int dfs(int x = S, int y = inf)
{
	if (x == T || !y) return y;
	int ret = 0;
	for (int i = bg[x]; i ; i = ne[i])
		if (w[i] > 0 && dis[to[i]] == dis[x] + 1)
		{
			int temp = dfs(to[i], min(y, w[i]));
			if (temp > 0)
			{
				ret += temp;
				y -= temp;
				w[i] -= temp;
				w[i ^ 1] += temp;
			}
		}
	return ret;
}

int main()
{
#ifdef CraZYali
	freopen("2776.in", "r", stdin);
	freopen("2776.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n)
	{
		a[i] = read<int>();
		REP(j, 0, i - 1) chkmax(dp[i], (a[j] <= a[i]) * (dp[j] + 1));
		chkmax(maxlen, dp[i]);
	}
	cout << maxlen << endl;
	S = n + n + 1;N = T = n + n + 2;
	REP(i, 1, n) if (dp[i] == 1) add(S, i, 1), add(i, S, 0);
	REP(i, 1, n) if (dp[i] == maxlen) add(i + n, T, 1), add(T, i + n, 0);
	REP(i, 1, n) add(i, i + n, 1), add(i + n, i, 0);
	REP(i, 1, n)
		REP(j, 1, i - 1)
		if (a[j] <= a[i] && dp[j] == dp[i] - 1) add(j + n, i, 1), add(i, j + n, 0);
	int ans = 0;
	while (bfs()) ans += dfs();
	cout << ans << endl;
	add(1, n + 1, inf);add(n + 1, 1, 0);
	add(S, 1, inf);add(1, S, 0);
	if (dp[n] == maxlen)
	{
		add(n + n, T, inf);add(T, n + n, 0);
		add(n, n + n, inf);add(n + n, n, 0);
	}
	while (bfs()) ans += dfs();
	cout << ans << endl;
	return 0;
}
