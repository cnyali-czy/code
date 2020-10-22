/*
	Problem:	3321.cpp
	Time:		2020-10-21 09:06
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

int n, k;

int a[505][505];
void add(int x, int y)
{
	a[x][x]++;a[y][y]++;
	a[x][y]--;a[y][x]--;
}

int main()
{
#ifdef CraZYali
	file("3321");
#endif
	n = read<int>();k = read<int>();
	static int id[505];
	REP(i, 1, k) REP(j, 1, n)
		REP(l, i + 1, k) REP(m, 1, n)
		add((i - 1) * n + j, (l - 1) * n + m);
	REP(i, 1, n * k) REP(j, 1, n * k) printf("%2d%c", a[i][j], j == end_j ? '\n' : ' ');
	return 0;
}
