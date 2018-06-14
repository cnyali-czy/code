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
const int maxn = (100 + 5) << 1, maxm = maxn * maxn, inf = 1e9;

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

int min_cost;

queue <int> q;
int dis[maxn], pre[maxn], Max[maxn];
bool vis[maxn];

int m, n, k, S, T;
inline bool spfa()
{
	REP(i, 1, n) {vis[i] = 0;dis[i] = inf;}
	dis[S] = 0;
	while (!q.empty()) q.pop();
	q.push(S);
	
	while (!q.empty())
	{
		register int x = q.front();
		q.pop();
		vis[x] = 0;
		for (register int i = bg[x]; i ; i = ne[i])
			if (w[i] > 0 && dis[x] + cost[i] < dis[to[i]])
			{
				dis[to[i]] = dis[x] + cost[i];
				pre[to[i]] = i;
				Max[to[i]] = max(w[i], Max[x]);
				if (!vis[to[i]])
				{
					vis[to[i]] = 1;
					q.push(to[i]);
				}
			}
	}
	return dis[T] != inf;
}

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

char s[maxn][maxn];

pair <int, int> house[maxn], man[maxn];

int main()
{
#ifdef CraZYali
	freopen("GoingHome.in", "r", stdin);
	freopen("GoingHome.out", "w", stdout);
#endif
	while (scanf("%d%d", &n, &m) * n * m)
	{
		memset(bg, 0, sizeof(bg));
		e = 1;

		REP(i, 1, n) scanf("%s", s[i] + 1);
		int mcnt(0), hcnt(0);
		REP(i, 1, n)
			REP(j, 1, m)
				if (s[i][j] == 'm') man[++mcnt] = make_pair(i, j);
				else if (s[i][j] == 'H') house[++hcnt] = make_pair(i, j);
		n = mcnt * 2 + 2;
		REP(i, 1, mcnt)
			REP(j, 1, mcnt)
			{
				add(i, j + mcnt, 1,  abs(house[i].first - man[j].first) + abs(house[i].second - man[j].second));
				add(j + mcnt, i, 0, -abs(house[i].first - man[j].first) - abs(house[i].second - man[j].second));
			}
		S = n - 1, T = n;
		REP(i, 1, mcnt)
		{
			add(S, i, 1, 0);
			add(i, S, 0, 0);
			add(i + mcnt, T, 1, 0);
			add(T, i + mcnt, 0, 0);
		}
		min_cost = 0;
		while (spfa()) update();
		printf("%d\n", min_cost);
	}

	return 0;
}
