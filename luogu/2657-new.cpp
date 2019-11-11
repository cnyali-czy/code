/*
 * File Name:	2657-new.cpp
 * Author	:	CraZYali
 * Year		:	2019.11.11 21:54
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define int long long
using namespace std;

template <typename T> inline T read()
{
	T ans(0), flag(1);
	char c(getchar());
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

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout);

int dp[100][10][2], qaq[100][10], stack[100], top;

int solve(int n)
{
	top = 0;
	int x = n;
	do
	{
		stack[++top] = x % 10;
		x /= 10;
	}while (x);
	reverse(stack + 1, stack + 1 + top);
	memset(dp, 0, sizeof dp);
	REP(i, 1, stack[1])
		dp[1][i][i != stack[1]] = 1;
	REP(i, 2, top)
		REP(x, 0, 9)
		{
			REP(j, 0, stack[i] - 1) if (abs(x - j) > 1)
		 		dp[i][j][1] += dp[i-1][x][0] + dp[i-1][x][1];
			REP(j, stack[i], 9) if (abs(x - j) > 1)
				dp[i][j][1] += dp[i-1][x][1];
			if (abs(x - stack[i]) > 1) dp[i][stack[i]][0] += dp[i-1][x][0];
		}
	int res(0);
	REP(j, 0, 9)
		REP(k, 0, 1) 
		res += dp[top][j][k];
	//正好长度的算完了
	memset(qaq, 0, sizeof qaq);
	REP(i, 1, 9) qaq[1][i] = 1;
	REP(i, 2, top - 1)
		REP(x, 0, 9)
		REP(j, 0, 9) if (abs(x - j) > 1)
		qaq[i][j] += qaq[i-1][x];
	REP(i, 1, top - 1)
		REP(j, 0, 9) res += qaq[i][j];
	return res;
}

signed main()
{
#ifdef CraZYali
	file("2657-new");
#endif
	int A, B;
	cin >> A >> B;
	cout << solve(B) - solve(A - 1) << endl;
	return 0;
}
