/*
	Problem:	B.cpp
	Time:		2021-05-09 20:36
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
#define int long long

using namespace std;
const int maxn = 500 + 5, inf = 1e18;

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

int n, a[maxn], f[maxn][2];

signed main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read<int>();
	REP(i, 1, n) a[i] = read<int>();
	f[0][1] = -inf;
	REP(i, 1, n)
	{
		f[i][0] = max(f[i - 1][0], f[i - 1][1]);
		f[i][1] = -inf;
		if (i >= 3) f[i][1] = max(f[i][1], f[i - 2][0] + a[i - 2] + a[i - 1] + a[i]);
		if (i >= 4) f[i][1] = max(f[i][1], f[i - 3][1] - a[i - 3] + a[i]);
		if (i >= 5) f[i][1] = max(f[i][1], f[i - 5][0] + a[i - 5] + a[i - 1] + a[i]);
	}
	cout << max(f[n][0], f[n][1]) << endl;
	return 0;
}
