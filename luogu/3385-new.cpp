/*
	Problem:	3385-new.cpp
	Time:		2020-11-06 18:53
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

using namespace std;
const int maxn = 2e3 + 10, maxm = 4e6 + 10, inf = 1e8;

int bg[maxn], ne[maxm], to[maxm], w[maxm], e;
inline void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
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
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, m;

int main()
{
#ifdef CraZYali
	file("3385-new");
#endif
	register int T = read<int>();
	while (T--)
	{
		n = read<int>();m = read<int>();
		REP(i, 1, n) bg[i] = 0;e = 0;
		while (m--)
		{
			int x = read<int>(), y = read<int>(), z = read<int>();
			add(x, y, z);
			if (z >= 0) add(y, x, z);
		}
		static bool vis[maxn];
		static int dis[maxn], cnt[maxn];
		REP(i, 1, n) vis[i] = 0;
		REP(i, 1, n) dis[i] = inf, cnt[i] = 0;
		dis[1] = 0;
		queue <int> q;
		q.push(1);
		while (!q.empty())
		{
			int x = q.front();q.pop();
			vis[x] = 0;
			for (int i = bg[x]; i; i = ne[i]) if (dis[to[i]] > dis[x] + w[i])
			{
				dis[to[i]] = dis[x] + w[i];
				cnt[to[i]] = cnt[x] + 1;
				if (cnt[to[i]] >= n)
				{
					puts("YES");
					goto gg;
				}
				if (!vis[to[i]])
				{
					vis[to[i]] = 1;
					q.push(to[i]);
				}
			}
		}
		puts("NO");
gg:;
	}
	return 0;
}
