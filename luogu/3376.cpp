#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>
#define int long long

using namespace std;
const int maxn = 10000 + 10, maxm = 100000 + 10, inf = 1ll << 60ll;

int bg[maxn], ne[maxm << 1], to[maxm << 1], w[maxm << 1], e = 1;
inline void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
}
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

int m, n, k, S, T;

int q[maxn], head, tail, dis[maxn];
bool bfs()
{
	q[head = tail = 1] = S;
	REP(i, 1, n) dis[i] = -1;
	dis[S] = 0;
	while (head <= tail)
	{
		register int x = q[head++];
		for (register int i = bg[x]; i ; i = ne[i])
			if (w[i] > 0 && dis[to[i]] == -1) dis[q[++tail] = to[i]] = dis[x] + 1;
	}
	return dis[T] != -1;
}

int dfs(int x = S, int y = inf)
{
	if (x == T || !y) return y;
	register int res = 0;
	for (register int i = bg[x], temp; i ; i = ne[i])
		if (w[i] > 0 && dis[to[i]] == dis[x] + 1 && (temp = dfs(to[i], min(y, w[i]))) > 0)
		{
			w[i] -= temp;
			w[i ^ 1] += temp;
			res += temp;
			y -= temp;
		}
	return res;
}

signed main()
{
#ifdef CraZYali
	freopen("3376.in", "r", stdin);
	freopen("3376.out", "w", stdout);
#endif
	cin >> n >> m >> S >> T;
	while (m --> 0)
	{
		register int x = read<int>(), y = read<int>(), z = read<int>();
		add(x, y, z);add(y, x, 0);
	}
	int ans = 0;
	while (bfs()) ans += dfs();

	cout << ans;
	return 0;
}
