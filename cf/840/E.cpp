/*
	Problem:	E.cpp
	Time:		2020-11-28 22:23
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
const int maxn = 5e4 + 10;

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

int n, q, a[maxn], ua[maxn], da[maxn], dep[maxn];
int anc[maxn][9];
void dfs(int x)
{
	dep[x] = dep[anc[x][0]] + 1;
	REP(i, 1, 8) anc[x][i] = anc[anc[x][i - 1]][i - 1];
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ anc[x][0])
	{
		anc[to[i]][0] = x;
		dfs(to[i]);
	}
}
int f[maxn][256];

int main()
{
#ifdef CraZYali
	file("E");
#endif
	n = read<int>();q = read<int>();
	REP(i, 1, n) a[i] = read<int>(), ua[i] = a[i] >> 8, da[i] = a[i] & 255;
	REP(i, 2, n)
	{
		int x = read<int>(), y = read<int>();
		add(x, y);add(y, x);
	}
	dfs(1);
	REP(x, 1, n)
	{
		static int s[300];
		for (int y = x, j = 0; j < 256; j++, y = anc[y][0])
			s[j] = y;
		static int bst[300];
		REP(i, 0, 255) bst[i] = 0;
		REP(j, 0, 255) if (s[j])
		{
			int y = s[j];
			bst[ua[y]] = max(bst[ua[y]], da[y] ^ j);
		}else break;
		REP(B, 0, 255)
		{
			int bstua = 0;
			REP(k, 0, 255) if (s[k])
			{
				int y = s[k];
				bstua = max(bstua, ua[y] ^ B);
			}else break;
			f[x][B] = (bstua << 8) + bst[bstua ^ B];
		}
	}
	while (q--)
	{
		int u = read<int>(), v = read<int>();
		int ans = 0;
		int x = v;
		REP(B, 0, 255)
			if (dep[anc[x][8]] >= dep[u]) ans = max(ans, f[x][B]), x = anc[x][8];
			else break;
		while (dep[x] >= dep[u])
		{
			ans = max(ans, a[x] ^ (dep[v] - dep[x]));
			x = anc[x][0];
		}
		printf("%d\n", ans);
	}
	return 0;
}
