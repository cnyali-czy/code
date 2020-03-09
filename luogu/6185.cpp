/*
	Problem:	6185.cpp
	Time:		2020-03-07 23:17
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cstring>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e5 + 10;

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

int fa[maxn];
int find(int x) {return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);}

int n, m, a[maxn], b[maxn];
int col[maxn], s[maxn], top, c[5];
pair <int, int> stack[maxn];

bool dfs(int x, int k)
{
	c[col[x] = k] += s[x];
	bool res = 1;
	for (int i = bg[x]; i; i = ne[i]) 
	{
		if (col[x] == col[to[i]]) res = 0;
		if (col[to[i]] < 0 && !dfs(to[i], !k)) res = 0;
	}
	return res;
}
int main()
{
#ifdef CraZYali
	file("6185");
#endif
	register int T = read<int>();
	while (T--)
	{
		n = read<int>();m = read<int>();
		REP(i, 1, n) col[i] = -1, bg[i] = s[i] = 0, fa[i] = i;
		REP(i, 1, n) a[i] = read<int>();
		REP(i, 1, n) b[i] = read<int>();
		e = top = 0;
		REP(i, 1, m)
		{
			int t(read<int>()), u(read<int>()), v(read<int>());
			if (t == 2) fa[find(u)] = find(v);
			else stack[++top] = make_pair(u, v);
		}
		REP(i, 1, top)
		{
			int x(find(stack[i].first)), y(find(stack[i].second));
			add(x, y);add(y, x);
		}
		REP(i, 1, n) s[find(i)] += b[i] - a[i];
		bool flag = 1;
		REP(i, 1, n) if (i == fa[i] && col[i] < 0)
		{
			c[0] = c[1] = 0;
			bool tmp = dfs(i, 0);
			if (tmp && c[0] ^ c[1]) {flag = 0;break;}
			if (!tmp && ((c[0] ^ c[1]) & 1)) {flag = 0;break;}
		}
		puts(flag ? "YES" : "NO");
	}
	return 0;
}
