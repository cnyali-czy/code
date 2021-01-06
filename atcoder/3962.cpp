/*
	Problem:	3962.cpp
	Time:		2020-12-29 21:23
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
const int maxn = 300 + 5, maxk = 300 + 5;

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
int f[maxn][maxk][maxn];

int main()
{
#ifdef CraZYali
	file("3962");
#endif
	n = read<int>();k = read<int>();
	const int MOD = read<int>();
	f[0][1][0] = 1;
	REP(i, 0, n) REP(j, 1, k) DEP(l, i, 0) if (f[i][j][l])
	{
		if (!l) (f[i][j + 1][i] += f[i][j][l]) %= MOD;
		else (f[i][j][l - 1] += f[i][j][l]) %= MOD;
		if (i < n)
			f[i + 1][j][l] = (f[i + 1][j][l] + (l + 1ll) * f[i][j][l]) % MOD;
	}
	cout << f[n][k][0] << endl;
	return 0;
}
