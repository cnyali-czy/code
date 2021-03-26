#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 100 + 5, maxm = 100 + 5, inf = 1e9 + 233;
const int maxN = maxn * maxm, maxM = maxN * 5;

int bg[maxN], ne[maxM << 1], to[maxM << 1], w[maxM << 1], e = 1;
inline void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
}
inline void Add(int x, int y, int z) {add(x, y, z);add(y, x, 0);}

int n, m;
int a[maxn][maxm];

int N, S, T;
inline int id(int x, int y) {return (x - 1) * m + y;}
int d[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

int dis[maxN];
bool bfs()
{
	static int que[maxN], head, tail;
	REP(i, 1, N) dis[i] = -1;
	dis[que[head = tail = 0] = T] = 0;
	while (head <= tail)
	{
		int x = que[head++];
		for (int i = bg[x]; i; i = ne[i])
			if (w[i ^ 1] > 0 && dis[to[i]] == -1)
			{
				dis[to[i]] = dis[x] + 1;
				que[++tail] = to[i];
			}
	}
	return dis[S] != -1;
}
int cur[maxN];
int dfs(int x = S, int y = inf)
{
	if (x == T || !y) return y;
	int res = 0;
	for (int &i = cur[x]; i; i = ne[i]) if (w[i] > 0 && dis[to[i]] == dis[x] - 1)
	{
		int tmp = dfs(to[i], min(y, w[i]));
		if (tmp > 0)
		{
			res += tmp;
			y -= tmp;
			w[i] -= tmp;
			w[i ^ 1] += tmp;
			if (!y) break;
		}
	}
	return res;
}

int main()
{
#ifdef CraZYali
	freopen("2774.in", "r", stdin);
	freopen("2774.out", "w", stdout);
#endif
	cin >> n >> m;int ans = 0;
	REP(i, 1, n) REP(j, 1, m)
	{
		scanf("%d", a[i] + j);
		ans += a[i][j];
	}
	S = id(n, m) + 1;N = T = S + 1;
	REP(x, 1, n) REP(y, 1, m) if (x + y & 1)
	{
		int u = id(x, y);
		REP(k, 0, 3)
		{
			int tx = x + d[k][0], ty = y + d[k][1], v = id(tx, ty);
			if (tx < 1 || tx > n || ty < 1 || ty > m) continue;
			Add(u, v, inf);
		}
	}
	REP(x, 1, n) REP(y, 1, m) if (x + y & 1) Add(S, id(x, y), a[x][y]);else Add(id(x, y), T, a[x][y]);
	while (bfs()) copy(bg, bg + 1 + N, cur), ans -= dfs();
	cout << ans << endl;
	return 0;
}
