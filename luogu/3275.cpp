/*
	Problem:	3275.cpp
	Time:		2021-05-03 19:55
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
const int maxn = 100000 + 10, maxm = maxn << 1;

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
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, k;

int dis[maxn], cnt[maxn];
bool vis[maxn];
queue <int> que;

int main()
{
#ifdef CraZYali
	file("3275");
#endif
	n = read<int>();k = read<int>();
	while (k--)
	{
		int x = read<int>(), a = read<int>(), b = read<int>();
		if (x == 1)
		{
			add(a, b, 0);
			add(b, a, 0);
		}
		else if (x == 2)
			add(a, b, 1);
		else if (x == 3)
			add(b, a, 0);
		else if (x == 4)
			add(b, a, 1);
		else if (x == 5)
			add(a, b, 0);
	}
	REP(i, 1, n) dis[i] = 1, que.push(i);
	const int LIM = 50;
	while (que.size())
	{
		int x = que.front();que.pop();
		cnt[x]++;if (cnt[x] > LIM)
		{
			puts("-1");
			return 0;
		}
		for (int i = bg[x]; i; i = ne[i]) if (dis[to[i]] < dis[x] + w[i])
		{
			dis[to[i]] = dis[x] + w[i];
			if (!vis[to[i]]) que.push(to[i]);
		}
		vis[x] = 0;
	}
	long long ans = 0;
	REP(i, 1, n) ans += dis[i];
	cout << ans << endl;
	
	return 0;
}
