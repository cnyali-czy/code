#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 1000 + 10, maxm = 1000 + 10, maxN = maxn * maxm, maxE = 6 * maxN;
int bg[maxN], ne[maxE << 1], to[maxE << 1], w[maxE << 1], e = 1;
void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
}
void insert(int x, int y, int z) {add(x, y, z);add(y, x, z);}

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

int n, m, N, ans;

int dis[maxN], q[maxN], head, tail;
bool bfs()
{
	REP(i, 2, N) dis[i] = -1;
	q[head = tail = 1] = 1;
	while (head <= tail)
	{
		int x = q[head++];
		for (int i = bg[x]; i ; i = ne[i])
			if (w[i] > 0 && dis[to[i]] == -1) dis[q[++tail] = to[i]] = dis[x] + 1;
	}
	return dis[N] != -1;
}
int dfs(int x = 1, int y = (int)1e9)
{
	if (x == N || !y) return y;
	int ret = 0;
	for (int i = bg[x]; i ; i = ne[i])
		if (w[i] > 0 && dis[to[i]] == dis[x] + 1)
		{
			int temp = dfs(to[i], min(w[i], y));
			if (temp > 0)
			{
				ret += temp;
				y -= temp;
				w[i] -= temp;
				w[i ^ 1] += temp;
				if (!y) break;
			}
		}
	if (!ret) dis[x] = -1;
	return ret;
}

int main()
{
#ifdef CraZYali
	freopen("1001.in", "r", stdin);
	freopen("1001.out", "w", stdout);
#endif
	cin >> n >> m;
	N = n * m;
	REP(i, 1, n)REP(j, 1, m - 1)
		insert(m * (i - 1) + j, m * (i - 1) + j + 1, read<int>());
	REP(i, 1, n - 1)REP(j, 1, m)
		insert(m * (i - 1) + j, m * i + j, read<int>());
	REP(i, 1, n - 1)REP(j, 1, m - 1)
		insert(m * (i - 1) + j, m * i + j + 1, read<int>());
	while (bfs()) ans += dfs();
	cout << ans << endl;
	return 0;
}
