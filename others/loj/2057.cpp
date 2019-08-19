#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 50 + 5, maxm = 50 + 5, maxN = maxn * maxm << 1, maxE = maxn * maxm, inf = 1e9;

int bg[maxN], to[maxE << 1], ne[maxE << 1], w[maxE << 1], e = 1;
inline void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
}
inline void link(int x, int y) {add(x, y, 1);add(y, x, 0);}

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

char s[maxn][maxm];
int belongx[maxn][maxm], belongy[maxn][maxm];
int n, m, N, S, T, curx, cury, ans;

int cur[maxN], dis[maxN], q[maxN], head, tail;
inline bool bfs()
{
	REP(i, 1, N) dis[i] = -1;
	dis[q[head = tail = 1] = T] = 0;
	while (head <= tail)
	{
		int x = q[head++];
		for (int i = bg[x]; i ; i = ne[i])
			if (w[i ^ 1] > 0 && dis[to[i]] == -1) dis[q[++tail] = to[i]] = dis[x] + 1;
	}
	return dis[S] != -1;
}
int dfs(int x = S, int y = inf)
{
	if (x == T || !y) return y;
	int res(0);
	for (int &i = cur[x]; i ; i = ne[i])
		if (w[i] > 0 && dis[to[i]] == dis[x] - 1)
		{
			int temp = dfs(to[i], min(y, w[i]));
			if (temp > 0)
			{
				res += temp;
				w[i] -= temp;
				w[i ^ 1] += temp;
				y -= temp;
				if (!y) goto End;
			}
		}
End:	return res;
}

inline void dinic()
{
	while (bfs())
	{
		copy(bg + 1, bg + 1 + N, cur + 1);
		ans += dfs();
	}
}

int main()
{
#ifdef CraZYali
	freopen("2057.in", "r", stdin);
	freopen("2057.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, n) scanf("%s", s[i] + 1);
	REP(i, 1, n)
		REP(j, 1, m) if (s[i][j] != '#') belongx[i][j] = belongx[i][j-1] ? belongx[i][j-1] : ++curx;
	REP(j, 1, m)
		REP(i, 1, n) if (s[i][j] != '#') belongy[i][j] = belongy[i-1][j] ? belongy[i-1][j] : ++cury;
	REP(i, 1, n)
		REP(j, 1, m) if (s[i][j] == '*') link(belongx[i][j], curx + belongy[i][j]);
	S = curx + cury + 1;
	N = T = curx + cury + 2;
	REP(i, 1, curx) link(S, i);
	REP(i, 1, cury) link(i + curx, T);
	dinic();
	cout << ans << endl;
	return 0;
}
