/*
	Problem:	checker.cpp
	Time:		2020-07-27 09:01
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cassert>
#include <cstring>
#include <iostream>
#include <cstdio>

using namespace std;

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

const int maxn = 3000 + 10;
int n, m, G[maxn][maxn];
char col[maxn][maxn];

bool vis[maxn][30];

int main()
{
	freopen("A.in", "r", stdin);
	n = read<int>();m = read<int>();
	REP(i, 2, n) REP(j, 1, i - 1)
	{
		int op;
		scanf("%1d", &op);
		G[i][j] = op;
		G[j][i] = !op;
	}
	freopen("A.out", "r", stdin);
	REP(i, 2, n)
	{
		scanf("%s", col[i] + 1);
		assert(strlen(col[i] + 1) == i - 1);
		REP(j, 1, i - 1) assert('a' <= col[i][j] && col[i][j] <= 'a' + m - 1);
	}
	REP(i, 1, n) REP(j, i + 1, n) col[i][j] = col[j][i];
	REP(i, 1, n) REP(j, 1, n) if (G[i][j])
		vis[j][col[i][j] - 'a'] = 1;
	REP(i, 1, n) REP(j, 1, n) if (G[i][j])
		if (vis[i][col[i][j] - 'a'])
		{
			printf("gg %d %d\n", i, j);
			return 0;
		}
	if (n<=800)
	{
		DEBUG;
		REP(i,1,n)REP(j,1,n)if(G[i][j])REP(k,1,n)if(G[j][k]&&col[i][j]==col[j][k]){printf("gg %d %d %d\n",i,j,k);return 0;}
	}
	puts("OK");	
	return 0;
}
