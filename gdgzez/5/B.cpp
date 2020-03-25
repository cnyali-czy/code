/*
	Problem:	B.cpp
	Time:		2020-03-25 10:50
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

int bg[maxn], ne[maxm << 1], to[maxm << 1], deg[maxn], e;
inline void add(int x, int y)
{
	deg[y]++;
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

int n, m;

int r3[maxn], r4[maxn], vis[maxn], d2[maxn], d3[maxn];

inline bool cmp(int x, int y)
{
	return deg[x] > deg[y] || deg[x] == deg[y] && x > y;
}

void Solve2()
{
	REP(x, 1, n)
		for (int i = bg[x]; i; i = ne[i])
			d2[x] += deg[to[i]] - 1;
}

void Solve3()
{
	REP(x, 1, n)
	{
		for (int i = bg[x]; i; i = ne[i]) vis[to[i]] = cmp(x, to[i]);
		for (int i = bg[x]; i; i = ne[i]) if (cmp(x, to[i]))
			for (int j = bg[to[i]]; j; j = ne[j]) if (vis[to[j]] && cmp(to[i], to[j]))
			{
				r3[x]++;
				r3[to[i]]++;
				r3[to[j]]++;
			}
		for (int i = bg[x]; i; i = ne[i]) vis[to[i]] = 0;
	}
}
void Solve4()
{ // 找四元环 
	REP(x, 1, n)
	{
		for (int i = bg[x]; i; i = ne[i]) if (cmp(x, to[i]))
			for (int j = bg[to[i]]; j; j = ne[j]) if (cmp(x, to[j]))
			{
				r4[x] += vis[to[j]];
				r4[to[i]] += vis[to[j]];
				r4[to[j]] += vis[to[j]];
				vis[to[j]]++;
			}
		for (int i = bg[x]; i; i = ne[i]) if (cmp(x, to[i]))
			for (int j = bg[to[i]]; j; j = ne[j]) if (cmp(x, to[j]))
				r4[to[i]] += --vis[to[j]];
	}
}


int main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read<int>();m = read<int>();
	while (m--)
	{
		int x(read<int>()), y(read<int>());
		add(x, y);add(y, x);
	}
	Solve2();
	Solve3();
	Solve4();
	REP(x, 1, n)
	{
		for (int i = bg[x]; i; i = ne[i]) d3[x] += d2[to[i]];
		d3[x] -= r3[x] * 2 + deg[x] * (deg[x] - 1);
	}
#ifdef CraZYali
	REP(i, 1, n) printf("%d%c", deg[i], i == n ? '\n' : ' ');
	REP(i, 1, n) printf("%d%c", d2[i], i == n ? '\n' : ' ');
	REP(i, 1, n) printf("%d%c", d3[i], i == n ? '\n' : ' ');
	REP(i, 1, n) printf("%d%c", r3[i], i == n ? '\n' : ' ');
	REP(i, 1, n) printf("%d%c", r4[i], i == n ? '\n' : ' ');
#endif
	REP(x, 1, n)
	{
		long long ans = 0;
		for (int i = bg[x]; i; i = ne[i]) ans += d3[to[i]];
		ans -= r4[x] * 2 + r3[x] * (deg[x] - 2) * 2 + deg[x] * d2[x] - 2 * r3[x] - d2[x];
		cout << ans << '\n';
	}
	return 0;
}
