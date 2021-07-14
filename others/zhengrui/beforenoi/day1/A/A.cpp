/*
	Problem:	A.cpp
	Time:		2021-07-13 09:11
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <ctime>
#include <set>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 5e5 + 10, inf = 1.5e9;

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
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, a[maxn];

int f[maxn];
void dfs(int x, int fa = 0)
{
	int mx = -inf, se = -inf;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
	{
		dfs(to[i], x);
		if (f[to[i]] > mx) se = mx, mx = f[to[i]];
		else se = max(se, f[to[i]]);
	}
	f[x] = max(a[x], se);
}

multiset <int> s[maxn];
void dfs0(int x, int fa = 0)
{
	int mx = -inf, se = -inf;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
	{
		dfs0(to[i], x);
		s[x].emplace(f[to[i]]);
		if (f[to[i]] > mx) se = mx, mx = f[to[i]];
		else se = max(se, f[to[i]]);
	}
	f[x] = max(a[x], se);
}
int ans[maxn];
inline int se(multiset <int> &s)
{
	if (s.size() < 2) return -inf;
	return *(--(--s.end()));
}

void dfs1(int x, int fa = 0)
{
	int res = a[x];
	for (int i = bg[x]; i; i = ne[i]) res = max(res, f[to[i]]);
	ans[x] = res;

	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
	{
		int y = to[i];
		int t1 = f[x], t2 = f[y];
		s[x].erase(s[x].find(f[y]));f[x] = max(a[x], se(s[x]));
		s[y].emplace(f[x]);f[y] = max(a[y], se(s[y]));
		dfs1(y, x);
		f[y] = t2;s[y].erase(s[y].find(f[x]));
		f[x] = t1;s[x].emplace(f[y]);		
	}
}

int main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();
	REP(i, 1, n) a[i] = read<int>();
	REP(i, 2, n)
	{
		int x = read<int>(), y = read<int>();
		add(x, y);add(y, x);
	}
	/*
	   REP(x, 1, n)
	   {
	   dfs(x, 0);
	   int ans = a[x];
	   for (int i = bg[x]; i; i = ne[i]) ans = max(ans, f[to[i]]);
	   printf("%d%c", ans, x == end_x ? '\n' : ' ');
	   }
	   */
	dfs0(1);
	dfs1(1);
	REP(i, 1, n) printf("%d%c", ans[i], i == end_i ? '\n' : ' ' );
	return 0;
}
