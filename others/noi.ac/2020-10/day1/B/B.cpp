/*
	Problem:	B.cpp
	Time:		2020-07-11 21:10
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
const int maxn = 1e5 + 10, inf = 1e9;

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

int x[maxn], n, m, f[400][400];

int main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read<int>(), m = read<int>();
	if (n < m) REP(i, 1, n * m) x[i] = read<int>();
	else
	{
		swap(n, m);
		REP(i, 1, n) REP(j, 1, m)
			x[(j - 1) * n + i] = read<int>();
	}
	REP(i, 1, n) REP(j, 1, n) f[i][j] = inf;
	REP(i, 1, m) REP(j, 1, n) if (x[(i - 1) * n + j])
		REP(k, 1, n) if (x[(i - 1) * n + k] > x[(i - 1) * n + j])
		chkmin(f[j][k], x[(i - 1) * n + k] - x[(i - 1) * n + j]);
	REP(k, 1, n) REP(i, 1, n) REP(j, 1, n)
		chkmin(f[i][j], f[i][k] + f[k][j]);
	int ans = inf;
	REP(i, 1, n) chkmin(ans, f[i][i]);
	printf("%d\n", ans == inf ? -1 : ans);
	return 0;
}
