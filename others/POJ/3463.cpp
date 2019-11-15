/*
 * File Name:	3463.cpp
 * Author	:	CraZYali
 * Year		:	2019.11.15 08:23
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;
const int maxn = 1000 + 10, maxm = 10000 + 10;

int bg[maxn], ne[maxm], to[maxm], w[maxm], e;
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
	T ans(0), flag(1);
	char c(getchar());
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout);

int dis[maxn][2], cnt[maxn][2];
bool vis[maxn][2];

struct node
{
	int x, dis, k;
	inline node(int x = 0, int dis = 0, int k = 0) : x(x), dis(dis), k(k) {}
	inline bool operator < (const node &B) const {return dis > B.dis;}
};
priority_queue <node> q;
const int inf = 1e9;
int n, m, S, T;
void dij()
{
	REP(i, 1, n)
	{
		dis[i][0] = dis[i][1] = inf;
		cnt[i][0] = cnt[i][1] = vis[i][0] = vis[i][1] = 0;
	}
	while (!q.empty()) q.pop();
	cnt[S][0] = 1;
	dis[S][0] = 0;
	q.push(node(S, 0, 0));
	while (!q.empty())
	{
		node cur(q.top());q.pop();
		int x(cur.x), dist(cur.dis), k(cur.k);
		if (vis[x][k]) continue;
		vis[x][k] = 1;
		for (int i = bg[x]; i; i = ne[i])
		{
			int l = dist + w[i];
			if (dis[to[i]][0] > l)
			{
				dis[to[i]][1] = dis[to[i]][0];
				cnt[to[i]][1] = cnt[to[i]][0];
				cnt[to[i]][0] = cnt[x][k];
				dis[to[i]][0] = l;
				q.push(node(to[i], dis[to[i]][0], 0));
				q.push(node(to[i], dis[to[i]][1], 1));
			}
			else if (dis[to[i]][0] == l)
				cnt[to[i]][0] += cnt[x][k];
			else if (dis[to[i]][1] > l)
			{
				dis[to[i]][1] = l;
				cnt[to[i]][1] = cnt[x][k];
				q.push(node(to[i], dis[to[i]][1], 1));
			}
			else if (dis[to[i]][1] == l) cnt[to[i]][1] += cnt[x][k];
		}
	}
}

int main()
{
#ifdef CraZYali
	file("3463");
#endif
	register int Case(read<int>());
	while (Case--)
	{
		n = read<int>();
		m = read<int>();
		e = 0;
		REP(i, 1, n) bg[i] = 0;
		while (m--)
		{
			int x(read<int>()), y(read<int>()), z(read<int>());
			add(x, y, z);
		}
		S = read<int>();T = read<int>();
		dij();
		int ans(cnt[T][0]);
		if (dis[T][0] == dis[T][1] - 1) ans += cnt[T][1];
		printf("%d\n", ans);
	}
	return 0;
}
