/*
	Problem:	5960.cpp
	Time:		2020-11-12 09:05
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
const int maxn = 5e3 + 10, maxm = 5e3 + 10;

int bg[maxn], ne[maxm], to[maxm], w[maxm], e;
void add(int x, int y, int z)
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

int n, m;
bool vis[maxn];
int cnt[maxn], dis[maxn];
queue <int> q;

int main()
{
#ifdef CraZYali
	file("5960");
#endif
	n = read<int>();m = read<int>();
	while (m--)
	{
		int x = read<int>(), y = read<int>(), z = read<int>();
		add(y, x, z);
	}
	REP(times, 1, n)
		REP(x, 1, n)
		for (int i = bg[x]; i; i = ne[i]) dis[to[i]] = min(dis[to[i]], dis[x] + w[i]);
	REP(x, 1, n) for (int i = bg[x]; i; i = ne[i]) if (dis[to[i]] > dis[x] + w[i])
	{
		puts("NO");
		return 0;
	}
	REP(i, 1, n) printf("%d%c", dis[i], i == end_i ? '\n' : ' ');
	return 0;
}
