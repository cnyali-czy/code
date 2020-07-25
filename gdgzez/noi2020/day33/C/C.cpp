/*
	Problem:	C.cpp
	Time:		2020-07-24 11:46
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e6 + 10;

int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
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
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, v[maxn], c[maxn], m;
void dfs(int x, int fa = 0)
{
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
	{
		dfs(to[i], x);
		v[x] -= v[to[i]];
		if (x < to[i])	c[to[i]] -= v[to[i]], c[x] += v[to[i]];
		else			c[to[i]] += v[to[i]], c[x] -= v[to[i]];
	}
}
int orz[maxn], jjs[maxn];

int main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();
	REP(i, 1, n) v[i] = read<int>();
	REP(i, 2, n)
	{
		int x = read<int>(), y = read<int>();
		add(x, y);add(y, x);
	}
	dfs(1);
	int m1 = 0, m2 = 0;
	REP(i, 1, n)
		if (c[i] > 0)	REP(j, 1, c[i]) orz[++m1] = i;
		else			REP(j, 1,-c[i]) jjs[++m2] = i;
	printf("%d\n", m1);
	REP(i, 1, m1) printf("%d %d\n", orz[i], jjs[i]);
	return 0;
}
