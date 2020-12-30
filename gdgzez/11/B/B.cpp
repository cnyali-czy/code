/*
	Problem:	B.cpp
	Time:		2020-12-28 19:49
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
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
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, q;
vector <int> B[maxn];

int stk[maxn], top, s, t;
void dfs(int x)
{
	stk[++top] = x;
	if (stk[top] == t) return;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ stk[top - 1])
	{
		dfs(to[i]);
		if (stk[top] == t) return;
	}
	top--;
}

int main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read<int>();
	REP(i, 2, n)
	{
		int x = read<int>(), y = read<int>();
		add(x, y);add(y, x);
	}
	REP(i, 2, n)
	{
		int x = read<int>(), y = read<int>();
		B[x].emplace_back(y);
		B[y].emplace_back(x);
	}
	q = read<int>();
	while (q--)
	{
		s = read<int>(), t = read<int>();
		top = 0;
		dfs(s);
		int ans = 0;
		static bool vis[maxn];
		REP(i, 1, top)
		{
			int cm = 0;
			REP(j, i, top)
			{
				vis[stk[j]] = 1;
				for (auto v : B[stk[j]]) if (vis[v]) cm++;
				if (cm == j - i) ans++;
			}
			REP(j, i, top) vis[stk[j]] = 0;
		}
		printf("%d\n", ans);
	}
	return 0;
}
