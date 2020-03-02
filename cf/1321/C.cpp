/*
	Problem:	C.cpp
	Time:		2020-03-01 21:40
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cmath>
#include <cstring>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 100 + 5, inf = 1e8;

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

int n;
char s[maxn];
int f[maxn][maxn][30][30];
int main()
{
#ifdef CraZYali
	file("C");
#endif
	scanf("%d\n%s", &n, s + 1);
	if (n == 1)
	{
		puts("0");
		return 0;
	}
	REP(i, 1, n) s[i] -= 'a';
	s[0] = s[n + 1] = '#';
	/*
	REP(i, 1, n) REP(j, 0, 26) dp[i][j] = -inf;
	dp[1][s[1]] = 0;
	if (s[2] == s[1] - 1) dp[1][26] = 1;
	s[n + 1] = '#';
	REP(i, 2, n)
	{
		REP(j, 0, 26) chkmax(dp[i][s[i]], dp[i-1][j]);
		REP(j, 0, 25) if ((s[i+1] == s[i] || j == s[i] - 1) && dp[i-1][j] > -inf)
			chkmax(dp[i][j], 1 + dp[i-1][j]);
		REP(j, 0, 25) if (j == s[i] + 1 && dp[i-1][j] > -inf)
			chkmax(dp[i][s[i]], 1 + dp[i-1][j]);
		if (dp[i-1][26] > -inf && s[i+1] == s[i] - 1) dp[i][26] = dp[i-1][26] + 1;
	}
	int ans = 0;
	if (dp[n][26] > -inf) chkmax(ans, dp[n][26] - (dp[n][26] == n));
	REP(i, 0, 25) chkmax(ans, dp[n][i]);
	REP(i, 1, n)
		REP(j, 0, 26) if (dp[i][j] > -inf) printf("dp[%d][%c] = %d\n", i, j == 26 ? '#' : j + 'a', dp[i][j]);
	*/
	REP(i, 0, n) REP(j, 0, n) REP(x, 0, 29) REP(y, 0, 29) f[i][j][x][y] = -inf;
	REP(i, 1, n)
	{
		f[i][i][s[i]][s[i]] = 0;
		if (s[i-1] == s[i] - 1 || s[i+1] == s[i] - 1) f[i][i][26][26] = 1;
	}
#define dp f
	REP(len, 2, n)
	{
		REP(i, 1, n)
		{
			int j = i + len - 1;if (j > n) break;
			REP(x, 0, 26) REP(y, 0, 26)
			{
				if (x != 26 && y != 26)
				{
					chkmax(dp[i][j][x][y], dp[i+1][j][x][y]);
					chkmax(dp[i][j][x][y], dp[i][j-1][x][y]);
				}
				if (x != 26 && s[i] == x + 1) chkmax(dp[i][j][x][y], 1 + dp[i+1][j][x][y]);
				if (y != 26 && s[j] == y + 1) chkmax(dp[i][j][x][y], 1 + dp[i][j-1][x][y]);
				if (x != 26 && s[i] == x - 1) chkmax(dp[i][j][s[i]][y], 1 + dp[i+1][j][x][y]);
				if (y != 26 && s[j] == y - 1) chkmax(dp[i][j][s[i]][y], 1 + dp[i][j-1][x][y]);
			}
		}
	}
	REP(i, 1, n) REP(j, i, n) REP(x, 0, 26) REP(y, 0, 26) if(dp[i][j][x][y]>=0)printf("dp[%d][%d][%c][%c] = %d\n", i,j,x==26?'#':x+'a',y==26?'#':y+'a',dp[i][j][x][y]);
	int ans = 0;
	REP(x, 0, 25) REP(y, 0, 25) chkmax(ans, dp[1][n][x][y]);
	if (dp[1][n][26][26] > -inf) chkmax(ans, dp[1][n][26][26] = (dp[1][n][26][26] == n));
	cout << ans << endl;
	return 0;
}
