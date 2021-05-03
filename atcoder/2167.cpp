/*
	Problem:	2167.cpp
	Time:		2021-04-29 07:59
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
const int maxn = 1e5 + 10, maxm = 1e5 + 10;

int bg[maxn], ne[maxm << 1], to[maxm << 1], w[maxm << 1], e;
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

int n, m;

int c[maxn], k, app[3], ed, flg;
void dfs(int x)
{
	k++;
	app[c[x]]++;
	for (int i = bg[x]; i; i = ne[i])
	{
		if (w[i] == 1) ed++;
		if (c[to[i]] == -1)
		{
			c[to[i]] = (c[x] + w[i]) % 3;
			dfs(to[i]);
		}
		else if (c[to[i]] != (c[x] + w[i]) % 3) flg = 0;
	}
}
int main()
{
#ifdef CraZYali
	file("2167");
#endif
	n = read<int>();m = read<int>();
	while (m--)
	{
		int x = read<int>(), y = read<int>();
		add(x, y, 1);add(y, x, 2);
	}
	REP(i, 1, n) c[i] = -1;
	long long ans = 0;
	REP(i, 1, n) if (c[i] == -1)
	{
		app[0] = app[1] = app[2] = 0;
		flg = 1;
		ed = k = c[i] = 0;dfs(i);
		if (!flg) ans += 1ll * k * k;
		else if (!app[0] || !app[1] || !app[2]) ans += ed;
		else ans += 1ll * app[0] * (app[1] + app[2]) + 1ll * app[1] * app[2];
	}
	cout << ans << endl;
	return 0;
}
