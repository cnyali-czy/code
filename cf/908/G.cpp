/*
	Problem:	G.cpp
	Time:		2020-03-09 18:21
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
const int maxn = 700 + 5, MOD = 1e9 + 7;

inline int mul(i64 x, int y) {x *= y;return x >= MOD ? x % MOD : x;}
inline void inc(int &x, int y) {x += y;if (x >= MOD) x -= MOD;}

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
int bin[maxn], dp[maxn][maxn][10][2];

struct __init__
{
	__init__(const int n = maxn - 1)
	{
		bin[0] = 1;
		REP(i, 1, n) bin[i] = mul(bin[i - 1], 10);
	}
}__INIT__;

int main()
{
#ifdef CraZYali
	file("G");
#endif
	scanf("%s", s + 1);
	n = strlen(s + 1);
	REP(i, 1, n) s[i] -= 48;
	REP(i, 0, 9) dp[0][0][i][0] = 1;
	REP(i, 0, n - 1) REP(j, 0, i) REP(k, 1, 9) REP(l, 0, 1) if (dp[i][j][k][l])
		REP(p, 0, l ? 9 : s[i + 1])
		inc(dp[i + 1][j + (p >= k)][k][l | (p < s[i + 1])], dp[i][j][k][l]);
	int ans = 0;
	REP(k, 1, 9)
	{
		int tmp = 1;
		REP(i, 1, n)
		{
			inc(ans, mul(tmp, dp[n][i][k][0] + dp[n][i][k][1]));
			inc(tmp, bin[i]);
		}
	}
	cout << ans << '\n';
	return 0;
}
