#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 205, maxm = maxn * maxn * 2, inf = (((1 << 30) - 1) << 1) + 1;

int bg[maxn], ne[maxm], to[maxm], w[maxm], e = 1;
inline void add(int x, int y, int z)
{
	e++;
	w[e] = z;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

inline void ADD(int x, int y)
{
	add(x, y, 1);
	add(y, x, 0);
}
template <typename T> T read()
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

int m, n, k;
int x1[maxn], _y1[maxn], x2[maxn], y2[maxn];

int ans;

int d[maxn];
inline bool BFS()
{
	bool flag = 0;
	REP(i, 1, n + 2) d[i] = inf;
	d[n + 1] = 0;
	queue <int> q;
	q.push(n + 1);
	while (!q.empty())
	{
		register int x = q.front();
		q.pop();
		for (register int i = bg[x]; i; i = ne[i])
			if (w[i] > 0 && d[to[i]] == inf)
			{
				d[to[i]] = d[x] + 1;
				q.push(to[i]);
				if (to[i] == n + 2) flag = 1;
			}
	}
	return flag;
}
#define dfs DFS
#define bfs BFS
inline int DFS(int now = n + 1, int flow = inf)
{
	if (!flow || now == n + 2) return flow;
	for (register int i = bg[now]; i ; i = ne[i])
		if (d[to[i]] == d[now] + 1 && w[i] > 0)
		{
			register int temp = dfs(to[i], min(flow, w[i]));
			if (temp > 0)
			{
				w[i] -= temp;
				w[i ^ 1] += temp;
				return temp;
			}
		}
	return 0;
}

int main()
{
#ifdef CraZYali
	freopen("c.in", "r", stdin);
	freopen("c.out", "w", stdout);
#endif
	n = read<int>();
	REP(i, 1, n) x1[i] = read<int>(), _y1[i] = read<int>();
	REP(i, 1, n) x2[i] = read<int>(), y2[i] = read<int>();
//	dfs(0);
	REP(i, 1, n)
		REP(j, 1, n)
			if (x1[i] < x2[j] && _y1[i] < y2[j])
				ADD(i, j + n);
	n <<= 1;
	REP(i, 1, n / 2)
		ADD(n + 1, i);
	REP(i, n / 2 + 1, n)
		ADD(i, n + 2);
	while (BFS())
		ans += DFS();
	
	cout << ans;
	return 0;
}
