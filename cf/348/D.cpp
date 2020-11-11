/*
	Problem:	D.cpp
	Time:		2020-11-06 19:47
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cstring>
#include <iostream>
#include <cstdio>
#define i64 long long
using namespace std;
const int maxn = 3000 + 10, maxm = 3000 + 10, MOD = 1e9 + 7;

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

int n, m;
char s[maxn][maxm];
int f[maxn][maxm];

void dp(int sx, int sy)
{
	if (s[sx][sy] == '#') return;
	f[sx][sy] = 1;
	s[sx][sy] = '#';
	REP(i, sx, n) REP(j, sy, m) if (s[i][j] != '#')
		f[i][j] = (f[i - 1][j] + f[i][j - 1]) % MOD;
	s[sx][sy] = '.';
}

int main()
{
#ifdef CraZYali
	file("D");
#endif
	n = read<int>();m = read<int>();
	REP(i, 1, n) scanf("%s", s[i] + 1);
	i64 ans1, ans2, ans3, ans4;
	dp(1, 2);ans1 = f[n - 1][m];ans2 = f[n][m - 1];
	memset(f, 0, sizeof f);
	dp(2, 1);ans3 = f[n - 1][m];ans4 = f[n][m - 1];
	i64 ans = ans1 * ans4 - ans2 * ans3;
	cout << (ans % MOD + MOD) % MOD << endl;
	return 0;
}
