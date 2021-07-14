/*
	Problem:	C.cpp
	Time:		2021-07-11 11:24
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <bits/extc++.h>
#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 60;

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

int n, q, go[maxn][2];
__gnu_pbds :: gp_hash_table <i64, int> dis[maxn];

int main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();
	REP(i, 0, n - 2) go[i][0] = read<int>() - 1, go[i][1] = read<int>() - 1;
	i64 u = 0, sta = 0;
	dis[u][sta] = 0;
	REP(d, 1, 1e9)
	{
		sta ^= (1ll << u);
		u = go[u][sta >> u & 1];
		if (dis[u].find(sta) != dis[u].end()) break;
		dis[u][sta] = d;
		if (u == n - 1) break;
	}
	q = read<int>();
	while (q--)
	{
		int x = read<int>() - 1;
		sta = 0;
		REP(i, 0, n - 2)
		{
			char c = getchar();
			while (!isalpha(c)) c = getchar();
			if (c == 'R') sta |= (1ll << i);
		}
		printf("%d\n", dis[x].find(sta) == dis[x].end() ? -1 : dis[x][sta]);
	}
	return 0;
}
