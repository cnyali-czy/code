/*
 * File Name:	1718.cpp
 * Author	:	CraZYali
 * Year		:	2019.11.15 11:27
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
const int maxn = 10000 + 10, maxm = 10000 + 10;

int bg[maxn], ne[maxm << 1], to[maxm << 1], e = 1;
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

int n, m;
int dfn[maxn], low[maxn], dfs_clock;
bool ban[maxm << 1];

void dfs(int x, int fa = -1)
{
	low[x] = dfn[x] = ++dfs_clock;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
		if (!dfn[to[i]])
		{
			dfs(to[i], x);
			chkmin(low[x], low[to[i]]);
			if (low[to[i]] > dfn[x]) ban[i] = ban[i ^ 1] = 1;
		}
		else chkmin(low[x], dfn[to[i]]);
}

int fa[maxn];
int find(int x) {return x == fa[x] ? fa[x] : fa[x] = find(fa[x]);}
inline void uni(int x, int y) {fa[find(x)] = find(y);}
int in[maxn];
#include <set>
#include <vector>
set <int> G[maxn];
vector <int> GG[maxn];

int main()
{
#ifdef CraZYali
	file("1718");
#endif
	cin >> n >> m;
	while (m--)
	{
		int x(read<int>()), y(read<int>());
		add(x, y);add(y, x);
	}
	REP(i, 1, n) if (!dfn[i]) dfs(i);
	REP(i, 1, n) fa[i] = i;
	REP(x, 1, n)
		for (int i = bg[x]; i; i = ne[i]) if (!ban[i]) uni(x, to[i]);
	REP(x, 1, n)
		for (int i = bg[x]; i; i = ne[i])
		{
			int _x(find(x)), _y(find(to[i]));
			if (_x == _y || G[_x].count(_y)) continue;
			G[_x].insert(_y);G[_y].insert(_x);
			GG[_x].push_back(_y);GG[_y].push_back(_x);
		}
	int leaf(0);
	REP(i, 1, n) leaf += (G[i].size() == 1);
	cout << (leaf + 1) / 2 << endl;
	return 0;
}
