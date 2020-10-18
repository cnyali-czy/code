/*
	Problem:	A.cpp
	Time:		2020-10-17 18:55
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
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, k, a[maxn][maxn];
int s(int x1, int y1, int x2, int y2) {return a[x2][y2] - a[x1 - 1][y2] - a[x2][y1 - 1] + a[x1 - 1][y1 - 1];}
int main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();k = read<int>();
	REP(i, 1, n) REP(j, 1, n)
	{
		scanf("%1d", a[i] + j);
		a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
	}
	int ans = 0;
	REP(i, 1, n - k + 1) REP(j, 1, n - k + 1) ans = max(ans, s(i, j, i + k - 1, j + k - 1));
	cout << ans << endl;
	return 0;
}
