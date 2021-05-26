/*
	Problem:	2699.cpp
	Time:		2021-01-26 09:08
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
const int maxn = 2000 + 10;

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
char str[maxn][maxn];
int a[maxn][maxn], le[maxn][maxn], ri[maxn][maxn], up[maxn][maxn];

int main()
{
#ifdef CraZYali
	file("2699");
#endif
	n = read<int>();m = read<int>();
	REP(i, 1, n) scanf("%s", str[i] + 1);
	REP(i, 1, n) REP(j, 1, m) str[i][j] = (str[i][j] == '#');
	REP(i, 1, n - 1)
		REP(j, 1, m - 1)
			a[i][j] = ((str[i][j] + str[i][j + 1] + str[i + 1][j] + str[i + 1][j + 1]) % 2 == 0);

	REP(i, 1, n - 1) REP(j, 1, m - 1) if (a[i][j] == 1)
	{
		le[i][j] = ri[i][j] = j;
		up[i][j] = 1;
	}else le[i][j] = m, ri[i][j] = 0, up[i][j] = 0;
	REP(i, 1, n - 1) REP(j, 2, m - 1)
		if (a[i][j] && a[i][j - 1]) le[i][j] = le[i][j - 1];
	REP(i, 1, n - 1) DEP(j, m - 2, 1)
		if (a[i][j] && a[i][j + 1]) ri[i][j] = ri[i][j + 1];

	int ans = max(n, m);
	REP(i, 1, n - 1) REP(j, 1, m - 1)
	{
		if (i > 1 && a[i][j] && a[i - 1][j])
		{
			le[i][j] = max(le[i][j], le[i - 1][j]);
			ri[i][j] = min(ri[i][j], ri[i - 1][j]);
			up[i][j] = up[i - 1][j] + 1;
		}
		if (a[i][j]) ans = max(ans, (ri[i][j] - le[i][j] + 2) * (up[i][j] + 1));
	}
	cout << ans << endl;

	return 0;
}
