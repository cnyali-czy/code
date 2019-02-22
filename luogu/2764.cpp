#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 150 + 5 << 1, maxm = 6000 + 10 + maxn + maxn, inf = 1e9;

int n, m;
struct Flow_Graph
{
	int bg[maxn], ne[maxm << 1], to[maxm << 1], w[maxm << 1], e;
	Flow_Graph() {e = 1;memset(bg, 0, sizeof(bg));}
	inline void add(int x, int y, int z)
	{
		e++;
		to[e] = y;
		ne[e] = bg[x];
		bg[x] = e;
		w[e] = z;
	}
	int N, S, T;
	void inputNST(int _N, int _S, int _T) {N = _N;S = _S;T = _T;}
	int q[maxn], head, tail, dis[maxn];
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
	int dfs(int x, int y)
	{
		if (x == T || !y) return y;
		int ret = 0;
		for (int i = bg[x]; i ; i = ne[i])
			if (w[i] > 0 && dis[to[i]] == dis[x] + 1)
			{
				int temp = dfs(to[i], min(y, w[i]));
				if (temp > 0)
				{
					y -= temp;
					ret += temp;
					w[i] -= temp;
					w[i ^ 1] += temp;
				}
			}
		return ret;
	}
	int max_flow;
	void calc()
	{
		max_flow = 0;
		while (bfs()) max_flow += dfs(S, inf);
	}
}FG;
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

struct Graph
{
	int bg[maxn], ne[maxm], to[maxm], deg[maxn], e;
	Graph() {e = 1;memset(bg, 0, sizeof(bg));memset(deg, 0, sizeof(deg));}
	inline void add(int x, int y)
	{
		e++;
		to[e] = y;
		ne[e] = bg[x];
		bg[x] = e;
		deg[y]++;
	}
	int q[maxn], head, tail;
	int belong[maxn], cnt;
	vector <int> path[maxn];
	void topsort()
	{
		head = 1;tail = 0;
		REP(i, 1, n)
			if (!deg[i])
			{
				path[belong[i] = ++cnt].push_back(i);
				q[++tail] = i;
			}
		while (head <= tail)
		{
			int x = q[head++];
			for (int i = bg[x]; i ; i = ne[i]) if (!(--deg[to[i]])) path[belong[q[++tail] = to[i]] = belong[x]].push_back(to[i]);
		}
	}
	void output_path()
	{
		REP(i, 1, cnt)
		{
			int siz = path[i].size() - 1;
			REP(j, 0, siz) printf("%d%c", path[i][j], j == siz ? '\n' : ' ');
		}
		printf("%d\n", cnt);
	}
}G;

int main()
{
#ifdef CraZYali
	freopen("2764.in", "r", stdin);
	freopen("2764.out", "w", stdout);
#endif
	cin >> n >> m;
	FG.inputNST(n + n + 2, n + n + 1, n + n + 2);
	REP(i, 1, n) FG.add(FG.S, i, 1), FG.add(i, FG.S, 0);
	REP(i, n + 1, n + n) FG.add(i, FG.T, 1), FG.add(FG.T, i, 0);
	while (m --> 0)
	{
		int x(read<int>()), y(read<int>());
		FG.add(x, y + n, 1), FG.add(y + n, x, 0);
	}
	FG.calc();
	REP(x, 1, n)
		for (int i = FG.bg[x]; i ; i = FG.ne[i])
			if (FG.to[i] ^ FG.S && !FG.w[i]) G.add(x, FG.to[i] - n);
	G.topsort();
	G.output_path();
	return 0;
}
