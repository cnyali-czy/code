/*
	Problem:	2657-new.cpp
	Time:		2020-09-15 09:37
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
const int maxn = 20;

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

int dp[maxn][12];
int lim[maxn], top;

int dfs(int x, int st, bool flag)//flag = (==) 
{
	if (!x) return 1;
	if (!flag && ~dp[x][st]) return dp[x][st];
	int res = 0;
	REP(i, 0, flag ? lim[x] : 9)
	{
		if (abs(i - st) < 2) continue;
		if (st == 11 && !i)
			res += dfs(x - 1, 11, flag & (i == end_i));
		else
			res += dfs(x - 1, i, flag & (i == end_i));
	}
	if (!flag) dp[x][st] = res;
	return res;
}

int work(int n)
{
	if (n < 1) return 1;
	top = 0;
	for (int x = n; x; x /= 10) lim[++top] = x % 10;
	memset(dp, -1, sizeof dp);
	return dfs(top, 11, 1);
}

int main()
{
#ifdef CraZYali
	file("2657-new");
#endif
	int l = read<int>(), r = read<int>();
	cout << work(r) - work(l - 1) << endl;
	return 0;
}
