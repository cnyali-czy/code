/*
	Problem:	C.cpp
	Time:		2021-06-24 16:23
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
const int maxn = 3e5 + 10;

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

int n;
vector <int> A[maxn], B[maxn];
int dfn[maxn], siz[maxn], fa[maxn], fb[maxn], top[maxn], hvy[maxn], dfs_clock;

void dfs1(int x)
{
	siz[x] = 1;hvy[x] = 0;
	for (int y : B[x])
	{
		dfs1(y);
		siz[x] += siz[y];
		if (siz[y] > siz[hvy[x]]) hvy[x] = y;
	}
}
void dfs2(int x, int z)
{
	dfn[x] = ++dfs_clock;
	top[x] = z;
	if (!hvy[x]) return;
	dfs2(hvy[x], z);
	for (int y : B[x]) if (y ^ hvy[x]) dfs2(y, y);
}
int ans;
int s[maxn];
int fen[maxn];
inline void add(int x, int y)
{
	while (x <= n)
	{
		fen[x] += y;
		x += x & -x;
	}
}
inline int sum(int x)
{
	int y = 0;
	while (x > 0)
	{
		y += fen[x];
		x &= (x - 1);
	}
	return y;
}
inline int sum(int l, int r) {return sum(r) - sum(l - 1);}
inline bool in(int x, int y) {return dfn[y] <= dfn[x] && dfn[x] <= dfn[y] + siz[y] - 1;}
void dfs(int x)
{
	vector <int> vec;
	if (!sum(dfn[x], dfn[x] + siz[x] - 1))
	{
		for (int z = x; z; z = fb[top[z]])
			if (s[top[z]] && in(x, s[top[z]]))
			{
				vec.emplace_back(-s[top[z]]);
				add(dfn[s[top[z]]], -1);
				s[top[z]] = 0;
			}
		s[top[x]] = x;
		add(dfn[x], 1);
		vec.emplace_back(x);
		ans = max(ans, sum(n));
	}
	for (int y : A[x]) dfs(y);
	s[top[x]] = 0;
	for (auto i : vec)
		if (i < 0)
		{
			s[top[-i]] = -i;
			add(dfn[-i], 1);
		}
		else add(dfn[x], -1);
}

int main()
{
#ifdef CraZYali
	file("C");
#endif
	register int T = read<int>();
	while (T--)
	{
		n = read<int>();
		REP(i, 1, n) A[i].clear(), B[i].clear();
		REP(i, 2, n) A[fa[i] = read<int>()].emplace_back(i);
		REP(i, 2, n) B[fb[i] = read<int>()].emplace_back(i);
		dfs_clock = 0;dfs1(1);dfs2(1, 1);
		ans = 0;
		REP(i, 1, n) s[i] = fen[i] = 0;
		dfs(1);
		printf("%d\n", ans);
	}
	return 0;
}
