/*
	Problem:	A.cpp
	Time:		2020-07-29 08:28
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
#include <cmath>

using namespace std;
const int maxn = 250 + 5, maxm = maxn * maxn, inf = 1e9;
const double eps = 1e-9;

int bg[maxn], ne[maxm], to[maxm], e;
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

int n, m, p[maxn], ans = inf;

int dfn, fir;
bool vis[maxn], in[maxn];
void dfs(int x)
{
	vis[x] = 1;
	for (int i = bg[x]; i; i = ne[i]) if (!vis[to[i]] && in[to[i]])
		dfs(to[i]);
}
bool check()
{
	if (!in[1] || !in[n]) return 0;
	dfn += n + n;
	REP(i, 1, n) vis[i] = 0;
	dfs(1);if (!vis[n]) return 0;
	dfn += n + n;
	REP(i, 1, n) vis[i] = 0;
	dfs(n);if (!vis[1]) return 0;
	return 1;
}
namespace bf
{
	void work()
	{
		REP(S, 1, (1 << n) - 1)
		{
			int res = 0;
			REP(i, 1, n)
			{
				in[i] = (S >> (i - 1) & 1);
				if (in[i]) res += p[i];
			}
			if (res >= ans) continue;
			else if (check()) ans = res;
		}
	}
}
inline int randint(int l, int r) {return rand() % (r - l + 1) + l;}
namespace cheat
{
	void SA()
	{
		int res = 0;
		REP(i, 1, n) in[i] = 1, res += p[i];
		dfn += n;
		double T = res;
		while (T > eps)
		{
			++dfn;
			int i = randint(2, n - 1);
			int tmp = res;
			if (in[i])	tmp -= p[i];
			else 		tmp += p[i];
			if (tmp < res || (!check() && exp((tmp - res) / T) < rand() * 1. / RAND_MAX))
			{
				in[i] = 1;
				res = tmp;
				if (res < ans && check()) ans = res;
			}
			T *= .98;
			REP(i, 1, n) printf("%d%c", in[i], i == end_i ? '\n' : ' ');
		}
	}
	void work()
	{
		SA();
		fir = dfn;
		while (fir + dfn <= 20000000) SA();
	}
}

int main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();m = read<int>();
	REP(i, 1, n) p[i] = read<int>();
	if (n == 2)
	{
		cout << p[1] + p[2] << endl;
		return 0;
	}
	while (m--)
	{
		int x = read<int>(), y = read<int>();
		add(x, y);
	}
	if (0&&n <= 20) bf :: work();
	else cheat :: work();
	printf("%d\n", ans < inf ? ans : -1);
	return 0;
}
