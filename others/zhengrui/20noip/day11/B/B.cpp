/*
	Problem:	B.cpp
	Time:		2020-11-16 08:53
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <queue>
#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 1e5 + 10, maxm = maxn * 6;

int bg[maxn], ne[maxm], to[maxm], e = 1;
i64 w[maxm];
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

	template <typename T>
inline T read()
{
	T ans = 0, flag = 1;
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, m, N;
i64 k, a[maxn];
inline int id(int i, int j) {return (i - 1) * m + j;}
int d[][2] = {{0, -1}, {0, 1}, {-1, 0}, {-1, 1}, {1, -1}, {1, 0}};

bool vis[maxn];
i64 dis[maxn], cnt[maxn];

bool judge(i64 mid)
{
	REP(u, 1, N) for (int i = bg[u]; i; i = ne[i])
	{
		int v = to[i];
		w[i] = -mid + (a[u] - a[v]);
	}
	queue <int> q;
	REP(i, 1, N)
	{
		cnt[i] = dis[i] = 0;
		vis[i] = 1;
		q.emplace(i);
	}
	while (!q.empty())
	{
		int x = q.front();q.pop();
		vis[x] = 0;
		for (int i = bg[x]; i; i = ne[i])
			if (dis[to[i]] < dis[x] + w[i])
			{
				dis[to[i]] = dis[x] + w[i];
				cnt[to[i]] = cnt[x] + 1;
				if (cnt[to[i]] >= N) return 0;
				if (!vis[to[i]])
				{
					vis[to[i]] = 1;
					q.emplace(to[i]);
				}
			}
	}
//	printf("%lld: ", mid);
//	REP(i, 1, n) REP(j, 1, m) printf("%lld%c", dis[id(i, j)], j == end_j ? '\n' : ' ' );
	i64 tot = 0;
	REP(i, 1, N) tot += dis[i];
	return tot <= k;
}

int main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read<int>();m = read<int>();k = read<i64>();
	N = n * m;
	REP(i, 1, N) a[i] = read<i64>();
	i64 Mx = 0;
	REP(i, 1, n) REP(j, 1, m)
		REP(l, 0, 5)
		{
			int ti = i + d[l][0], tj = j + d[l][1];
			if (ti < 1 || ti > n || tj < 1 || tj > m) continue;
			int u = id(i, j), v = id(ti, tj);
			if (u > v) continue;
			add(u, v);add(v, u);
			Mx = max(Mx, a[u] - a[v]);Mx = max(Mx, a[v] - a[u]);			
		}
	i64 l = 0, r = Mx, ans = 114514;
	while (l <= r)
	{
		i64 mid = l + r >> 1;
		if (judge(mid))
		{
			ans = mid;
			r = mid - 1;
		}
		else l = mid + 1;
	}
	cout << ans << endl;
	return 0;
}
