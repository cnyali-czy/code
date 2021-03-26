#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <queue>
#include <iostream>
#include <cstdio>
#define int long long

using namespace std;
const int maxd = 2000 + 10, inf = 1e16;
const int maxN = maxd << 1, maxM = maxN * 10;

int bg[maxN], ne[maxM << 1], to[maxM << 1], w[maxM << 1], cost[maxM << 1], e = 1, S, T, N;
void add(int x, int y, int z, int c)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
	cost[e] = c;
}
inline void Add(int x, int y, int z, int c)
{
	add(x, y, z,  c);
	add(y, x, 0, -c);
}

int d, a[maxd], p, m, f, n, s;

bool vis[maxN];
int dis[maxN], frm[maxN], Max[maxN];
bool spfa()
{
	REP(i, 1, N) dis[i] = inf, vis[i] = 0;
	dis[S] = 0;Max[S] = inf;
	queue <int> q;q.emplace(S);
	while (q.size())
	{
		int x = q.front();q.pop();
		for (int i = bg[x]; i; i = ne[i]) if (w[i] > 0 && dis[to[i]] > dis[x] + cost[i])
		{
			dis[to[i]] = dis[x] + cost[i];
			frm[to[i]] = i;
			Max[to[i]] = min(w[i], Max[x]);
			if (!vis[to[i]])
			{
				vis[to[i]] = 1;
				q.emplace(to[i]);
			}
		}
		vis[x] = 0;
	}
	return dis[T] < inf;
}

int ans, flow;
void update()
{
	flow += Max[T];
	ans += dis[T] * Max[T];
	for (int x = T; x ^ S; x = to[frm[x] ^ 1])
	{
		w[frm[x]] -= Max[T];
		w[frm[x] ^ 1] += Max[T];
	}
}

signed main()
{
#ifdef CraZYali
	freopen("1251.in", "r", stdin);
	freopen("1251.out", "w", stdout);
#endif
	cin >> d;
	REP(i, 1, d) scanf("%lld", a + i);
	cin >> p >> m >> f >> n >> s;

	N = S = d + d + 1;
	T = d + d;

	REP(i, 1, d)
	{
		Add(S, i, inf, p);
		Add(i, i + d, a[i], 0);

		if (i + m <= d) Add(i + d, i + m, inf, f);
		if (i + n <= d) Add(i + d, i + n, inf, s);
		if (i < d) Add(i + d, i + 1 + d, inf, 0);
	}
	while (spfa()) update();
	cout << ans << endl;
	cerr << flow << endl;
	return 0;
}
