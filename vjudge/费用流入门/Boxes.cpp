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
const int maxn = 10000 + 10, maxm = maxn << 1, inf = 1e9;

int bg[maxn], ne[maxm << 1], to[maxm << 1], w[maxm << 1], cost[maxm << 1], e = 1;
inline void add(int x, int y, int z, int c)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
	cost[e] = c;
}

template <typename T> T read()
{
	T ans(0), p(1);
	char c = getchar();
	while (!isdigit(c)) {
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c)) {
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}
int m, n, k;

queue <int> q;
int dis[maxn], pre[maxn], Max[maxn], S, T;
bool vis[maxn];

inline bool spfa()
{
	REP(i, 1, n) {vis[i] = 0;dis[i] = inf;}
	Max[S] = inf;
	dis[S] = 0;
	q.push(S);
	while (!q.empty())
	{
		register int x = q.front();
		vis[x] = 0;
		q.pop();
		for (register int i = bg[x]; i ;i = ne[i])
			if (w[i] > 0 && dis[x] + cost[i] < dis[to[i]])
			{
				dis[to[i]] = dis[x] + cost[i];
				pre[to[i]] = i;
				Max[to[i]] = min(w[i], Max[x]);
				if (!vis[to[i]])
				{
					vis[to[i]] = 1;
					q.push(to[i]);
				}
			}
	}
	return dis[T] != inf;
}
int min_cost;
inline void update()
{
	int now = T;
	while (now ^ S)
	{
		w[pre[now]] -= Max[T];
		w[pre[now] ^ 1] += Max[T];
		now = to[pre[now] ^ 1];
	}
	min_cost += dis[T] * Max[T];
}

int main()
{
#ifdef CraZYali
	freopen("Boxes.in", "r", stdin);
	freopen("Boxes.out", "w", stdout);
#endif
	register int tT = read<int>();
	while (tT --> 0)
	{
		memset(bg, 0, sizeof(bg));
		e = 1;

		n = read<int>();
		S = n + 1;
		T = n + 2;

		REP(i, 1, n)
		{
			add(S, i, read<int>(), 0);
			add(i, S, 0, 0);
			add(i, T, 1, 0);
			add(T, i, 0, 0);
		}
		REP(i, 1, n - 1)
		{
			add(i, i + 1, inf, 1);
			add(i + 1, i, 0, -1);
			add(i + 1, i, inf, 1);
			add(i, i + 1, 0, -1);
		}
		add(n, 1, inf, 1);
		add(1, n, 0, -1);
		add(1, n, inf, 1);
		add(n, 1, 0, -1);
		n = T;
		min_cost = 0;
		while (spfa()) update();
		printf("%d\n", min_cost);
	}

	return 0;
}
