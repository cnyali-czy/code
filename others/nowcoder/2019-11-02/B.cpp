/*
 * File Name:	B.cpp
 * Author	:	CraZYali
 * Year		:	2019.11.02 19:00
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;
const int maxn = 1e5 + 10;

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

int n, W, a[maxn];
long long dp[maxn], sum[maxn];

int Min[maxn][25], Max[maxn][25], LG[maxn];
#define _min(a, b) (a < b ? a : b)
#define _max(a, b) (a > b ? a : b)
inline int st_query_min(int l, int r)
{
	int k = LG[r - l + 1];
	return _min(Min[l][k], Min[r - (1 << k) + 1][k]);
}
inline int st_query_max(int l, int r)
{
	int k = LG[r - l + 1];
	return _max(Max[l][k], Max[r - (1 << k) + 1][k]);
}
const long long inf = 1e16;
#define tmp(j, i) (dp[j] + st_query_max(j + 1, i) - st_query_min(j + 1, i))
int main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read<int>();
	REP(i, 2, n) LG[i] = LG[i >> 1] + 1;
	W = read<int>();
	REP(i, 1, n)	Min[i][0] = Max[i][0] = a[i] = read<int>();
	DREP(i, n, 1)	sum[i] = sum[i+1] + a[i];
	DREP(i, n, 1)
		for (int j = 1; i + (1 << j) - 1 <= n; j++)
		{
			Min[i][j] = _min(Min[i][j-1], Min[i + (1 << j - 1)][j-1]);
			Max[i][j] = _max(Max[i][j-1], Max[i + (1 << j - 1)][j-1]);
		}
	/*
	   REP(i, 1, n) printf("%lld%c", sum[i], i == n ? '\n' :' ');
	   REP(i, 1, n)
	   REP(j, i, n) printf("%d %d %d %d\n", i, j, st_query_max(i, j), st_query_min(i, j));
	   */
	REP(i, 1, n) dp[i] = inf;
	dp[0] = sum[1];
	if (n <= 5000)
		REP(i, 1, n)
		{
			DREP(j, i - 1, 0)
				if (sum[j+1] - sum[i+1] <= W)
					chkmin(dp[i], dp[j] + st_query_max(j + 1, i) - st_query_min(j + 1, i) + sum[i+1]);
				else break;
		}
	else
	{
		int j(0);
		REP(i, 1, n)
			DREP(k, _min(i - 1, j + 800), _max(0, j - 800))
				if (sum[k + 1] - sum[i + 1] <= W)
				{
					long long ttt = tmp(k, i) + sum[i + 1];
					if (dp[i] >= ttt) dp[j = i] = ttt;
				}
				else break;
	}
	//	REP(i, 1, n) printf("%lld%c", dp[i], i == n ? '\n' : ' ');
	cout << dp[n] << endl;
	return 0;
}
