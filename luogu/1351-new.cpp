/*
 * File Name:	1351-new.cpp
 * Author	:	CraZYali
 * Year		:	2019.10.24 20:55
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 200000 + 10, MOD = 10007;

int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

template <typename T> inline T read()
{
	T ans(0), flag(1);
	char c(getchar());
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

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout);

int n;
int w[maxn], fa[maxn], Max[maxn], Sec[maxn], Sum[maxn], Sum2[maxn];

void dfs(int x)
{
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa[x])
	{
		fa[to[i]] = x;
		dfs(to[i]);
		(Sum[x] += w[to[i]]) %= MOD;
		(Sum2[x] += w[to[i]] * w[to[i]]) %= MOD;
		if (w[to[i]] > Max[x])
		{
			Sec[x] = Max[x];
			Max[x] = w[to[i]];
		}
		else if (w[to[i]] > Sec[x]) Sec[x] = w[to[i]];
	}
}
int Maxans, tot;

int main()
{
#ifdef CraZYali
	file("1351-new");
#endif
	cin >> n;
	REP(i, 2, n)
	{
		register int x(read<int>()), y(read<int>());
		add(x, y);add(y, x);
	}
	REP(i, 1, n) w[i] = read<int>();
	dfs(1);
	REP(i, 1, n) if (fa[fa[i]])
	{
		chkmax(Maxans, w[fa[fa[i]]] * w[i]);
		(tot += 2 * w[fa[fa[i]]] * w[i]) %= MOD;
	}
	REP(i, 1, n)
	{
		chkmax(Maxans, Max[i] * Sec[i]);
		(tot += Sum[i] * Sum[i] - Sum2[i]) %= MOD;
	}
	cout << Maxans << ' ' << tot << endl;
	return 0;
}
