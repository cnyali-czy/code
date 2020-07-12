/*
	Problem:	C.cpp
	Time:		2020-07-11 22:38
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
const int maxn = 1000 + 10, M = 2e4, inf = 1e9;

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

int n, k, a[maxn], b[maxn], f[maxn][M + 5];

int main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>(), k = read<int>();
	REP(i, 1, n - 1) a[i] = read<int>(), b[i] = read<int>();
	REP(i, 0, n) REP(j, 0, M) f[i][j] = -inf;
	REP(i, 0, k - 1) f[1][i] = i;
	int ans = 0;
	REP(i, 1, n)
	{
		int Max = -inf;
		REP(j, 0, M)
		{
			if (j < a[i])
			{
				chkmax(Max, f[i][j]);
				chkmax(f[i + 1][j + b[i]], f[i][j] + b[i]);
			}
			else if (j < a[i] + b[i])
				chkmax(f[i + 1][j - a[i]], f[i][j]);
			else
				chkmax(f[i + 1][j], f[i][j]);
			chkmax(ans, f[i][j]);
		}
		REP(j, 0, b[i] - 1) chkmax(f[i + 1][j], Max + j);
	}
	cout << ans << endl;
	return 0;
}
