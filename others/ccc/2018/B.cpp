/*
	Problem:	B.cpp
	Time:		2021-02-18 08:24
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
const int maxn = 100 + 5;

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

int n, a[maxn][maxn];
void rotate()
{
	static int b[maxn][maxn];
	DEP(i, n, 1)
		REP(j, 1, n)
		b[n - i + 1][j] = a[j][i];
	REP(i, 1, n) REP(j, 1, n) a[i][j] = b[i][j];
}
bool isinc(int a[], int n)
{
	REP(i, 2, n) if (a[i - 1] >= a[i]) return 0;
	return 1;
}
bool ok()
{
	REP(i, 1, n) if (!isinc(a[i], n)) return 0;
	static int c[maxn];
	REP(i, 1, n) c[i] = a[i][1];
	return isinc(c, n);
}

int main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read<int>();
	REP(i, 1, n) REP(j, 1, n) a[i][j] = read<int>();
	while (!ok()) rotate();
	REP(i, 1, n) REP(j, 1, n) printf("%d%c", a[i][j], j == end_j ? '\n' : ' ' );
	return 0;
}
