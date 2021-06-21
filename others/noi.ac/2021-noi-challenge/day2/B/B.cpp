/*
	Problem:	B.cpp
	Time:		2021-06-20 16:59
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdio>
#define int long long

using namespace std;
const int maxn = 5e5 * 2 + 10, maxm = maxn;

int bg[maxn], ne[maxn << 1], to[maxn << 1], w[maxn << 1], e;
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

int fa[maxn], ed[maxn], sz[maxn];
int find(int x) {return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);}
void uni(int x, int y)
{
	x = find(x);y = find(y);
	if (x == y) ed[x]++;
	else
	{
		fa[x] = y;
		ed[y]++;
		sz[y] += sz[x];
	}
}
bool vis[maxn];
vector <int> vec[maxn];

int stk[maxn], top, cir[maxm], c;
void findcircle(int x, int fa = 0)
{
}

signed main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read<int>();m = read<int>();
	REP(i, 1, n + n) fa[i] = i, sz[i] = 1;
	while (m--)
	{
		int x = read<int>(), y = read<int>(), a = read<int>(), b = read<int>();
		add(x, y + n, b);
		add(y + b, x, a);
		uni(x, y + n);
	}
	REP(i, 1, n + n) vec[find(i)].emplace_back(i);
	REP(i, 1, n + n) if (find(i) == i)
		if (ed[i] == sz[i] - 1) // tree
		{
		}
		else // tree on circle
		{
			c = 0;
			findcircle(i);
		}
	return 0;
}
