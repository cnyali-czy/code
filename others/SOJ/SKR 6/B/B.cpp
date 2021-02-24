/*
	Problem:	B.cpp
	Time:		2021-02-23 13:19
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
#define i64 long long

using namespace std;
const int maxn = 1e6 + 10, maxm = 2e6 + 10, MOD = 10007;

int bg[maxn], ne[maxm << 1], to[maxm << 1], e;
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

int n, m, q;

int k;
bool vis[maxn];
void dfs(int x)
{
	vis[x] = 1;
	k++;
	for (int i = bg[x]; i; i = ne[i]) if (!vis[to[i]]) dfs(to[i]);
}
int query(int ban)
{
	REP(i, 1, n) vis[i] = 0;vis[ban] = 1;
	i64 ans = 0;
	REP(i, 1, n) if (!vis[i])
	{
		k = 0;
		dfs(i);
		ans += 1ll * k * k;
	}
	return ans % MOD;
}
int main()
{
#ifdef CraZYali
	file("B");
#endif
	cin >> n >> m >> q;
	while (m--)
	{
		int x = read<int>(), y = read<int>();
		add(x, y);add(y, x);
	}
	while (q--)
	{
		int opt = read<int>(), x = read<int>();
		if (opt == 1) printf("%d\n", query(x));
		else
		{
			int y = read<int>();
			add(x, y);add(y, x);
		}
	}
	return 0;
}
