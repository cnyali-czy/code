#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <queue>
#include <map>
#include <set>

using namespace std;

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
const int maxn = 100 + 5, maxm = maxn * maxn;

int bg[maxn << 1], ne[maxm << 1], to[maxm << 1], w[maxm << 1], e = 1;
double cost[maxm << 1];
inline void add(int x, int y, int z, double c)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
	cost[e] = c;
}

int m, n, k, S, T, N;


const double inf = 1e20;

double dis[maxn << 1]; 
int pre[maxn << 1], Max[maxn << 1];
bool vis[maxn << 1];
queue <int> q;

inline bool spfa()
{
	REP(i, 1, N) dis[i] = inf, vis[i] = 0;
	dis[S] = 0;
	Max[S] = inf;
	q.push(S);
	while (!q.empty())
	{
		register int x = q.front();
		vis[x] = 0;
		q.pop();
		for (register int i = bg[x]; i ; i = ne[i])
			if (w[i] > 0 && dis[to[i]] > dis[x] + cost[i])
			{
				dis[to[i]] = dis[x] + cost[i];
				pre[to[i]] = i;
				Max[to[i]] = min(Max[x], w[i]);
				if (!vis[to[i]])
				{
					vis[to[i]] = 1;
					q.push(to[i]);
				}
			}
	}
	return fabs(dis[T] - inf) > 1e-9;
}

double min_cost;

inline void update()
{
	register int now = T;
	while (now ^ S)
	{
		w[pre[now]] -= Max[T];
		w[pre[now] ^ 1] += Max[T];
		now = to[pre[now] ^ 1];
	}
	min_cost += Max[T] * dis[T];
}

int x[maxn << 1], y[maxn << 1];

#define dist(x1, y1, x2, y2) sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2))

int main()
{
#ifdef CraZYali
	freopen("1411.in", "r", stdin);
	freopen("1411.out", "w", stdout);
#endif
	bool first = 1;
	while (scanf("%d", &n) != EOF)
	{
		if (first) first = 0;
		else putchar(10);
		
		S = n * 2 + 1;
		T = n * 2 + 2;
		N = T;
		REP(i, 1, N) bg[i] = 0;
		e = 1;

		REP(i, 1, n << 1) x[i] = read<int>(), y[i] = read<int>();
		REP(i, 1, n)
		{
			add(S, i, 1, 0);
			add(i, S, 0, 0);
		}
		REP(i, 1, n)
		{
			add(i + n, T, 1, 0);
			add(T, i + n, 0, 0);
		}
		REP(i, 1, n)
			REP(j, 1, n)
			{
				register int u = i, v = j + n;
				add(u, v, 1, dist(x[u], y[u], x[v], y[v]));
				add(v, u, 0, -dist(x[u], y[u], x[v], y[v]));
			}
		min_cost = 0;
		while (spfa()) update();
		REP(x, 1, n)
			for (register int i = bg[x]; i ; i = ne[i])
				if (!w[i] && to[i] > n)
				{
					printf("%d\n", to[i] - n);
					break;
				}
	}

	return 0;
}

