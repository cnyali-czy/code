#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxk = 20 + 5, maxn = 1000 + 10, maxN = maxn + maxk + 10, maxE = maxk * maxn, inf = 1e9;

int bg[maxN], ne[maxE << 1], to[maxE << 1], w[maxE << 1], e = 1;
inline void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
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

int k, n, S, T, N, ans, need, total;

set <int> out[maxk];
set <int> :: iterator it;

int q[maxN], head, tail, dis[maxN];
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
	freopen("2763.in", "r", stdin);
	freopen("2763.out", "w", stdout);
#endif
	cin >> k >> n;
	S = k + n + 1;N = T = k + n + 2;
	REP(i, 1, k)
	{
		total += (need = read<int>());
		add(i + n, T, need);
		add(T, i + n, 0);
	}
	REP(i, 1, n) add(S, i, 1), add(i, S, 0);
	REP(i, 1, n)
	{
		int cnt = read<int>();
		REP(j, 1, cnt)
		{
			int type = read<int>();
			add(i, type + n, 1);
			add(type + n, i, 1);
		}
	}
	while (bfs()) ans += dfs();
	if (ans < total) cout << "No Solution!\n";
	else
	{
		REP(x, 1, n)
			for (int i = bg[x]; i ; i = ne[i])
				if (to[i] ^ S && !w[i]) {out[to[i] - n].insert(x);break;}
		REP(i, 1, k)
		{
			printf("%d:", i);
			for (it = out[i].begin(); it != out[i].end(); it++) printf(" %d", *it);
			putchar(10);
		}
	}
	return 0;
}
