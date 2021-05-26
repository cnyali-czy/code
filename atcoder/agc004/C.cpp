/*
	Problem:	2043.cpp
	Time:		2021-01-19 11:17
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
const int maxn = 500 + 10;

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
char c[maxn][maxn], a[maxn][maxn], b[maxn][maxn];

int main()
{
#ifdef CraZYali
	file("2043");
#endif
	n = read<int>();m = read<int>();
	REP(i, 1, n) scanf("%s", c[i] + 1);
	REP(i, 1, n) REP(j, 1, m) a[i][j] = b[i][j] = '.';
	REP(i, 1, n) a[i][1] = b[i][m] = '#';
	REP(j, 1, m) REP(i, 1, n) if (i & 1) a[i][j] = '#';else b[i][j] = '#';
	REP(i, 1, n) a[i][m] = b[i][1] = '.';
	REP(i, 1, n) REP(j, 1, m) if (c[i][j] == '#') a[i][j] = b[i][j] = '#';
	REP(i, 1, n) puts(a[i] + 1);puts("");
	REP(i, 1, n) puts(b[i] + 1);
	return 0;
}
