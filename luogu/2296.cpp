#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 10000 + 10, maxm = 200000 + 10;

int m, n, k, S, T, u[maxm], v[maxm];
int son_cnt[maxn], ok_cnt[maxn];

bool vis[maxn];

struct Graph
{
	int bg[maxn], ne[maxm], to[maxm], e;
	inline void add(int x, int y)
	{
		e++;
		to[e] = y;
		ne[e] = bg[x];
		bg[x] = e;
	}
	void dfs(int x)
	{
		vis[x] = 1;
		for (register int i = bg[x]; i ; i = ne[i])
			if (!vis[to[i]]) dfs(to[i]);
	}
	void output()
	{
		REP(x, 1, n)
			for (register int i = bg[x] ; i  ; i = ne[i]) printf("%d %d\n", x, to[i]);
	}
	int dis[maxn], q[maxn], head, tail;
	void bfs()
	{
		REP(i, 1, n) dis[i] = -1;dis[S] = 0 ;
		q[head = tail = 1] = S;
		while (head <= tail)
		{
			register int x = q[head++];
			for (register int i = bg[x]; i ; i = ne[i])
				if (dis[to[i]] == -1) dis[q[++tail] = to[i]] = dis[x] + 1;
		}
	}
}G, R;

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

int main()
{
#ifdef CraZYali
	freopen("2296.in", "r", stdin);
	freopen("2296.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, m)
	{
		u[i] = read<int>(), v[i] = read<int>();
		if (u[i] == v[i]) continue;
		son_cnt[u[i]]++;
		R.add(v[i], u[i]);
	}
	cin >> S >> T;
	R.dfs(T);

	REP(i, 1, m)
		if (u[i] ^ v[i]) ok_cnt[u[i]] += vis[v[i]];
	REP(i, 1, m)
		if (u[i] ^ v[i] && ok_cnt[u[i]] == son_cnt[u[i]] && ok_cnt[v[i]] == son_cnt[v[i]]) G.add(u[i], v[i]);

	G.bfs();

	cout << G.dis[T];
	return 0;
}
