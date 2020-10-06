/*
	Problem:	aba.cpp
	Time:		2020-06-12 07:55
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cstring>
#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 3000 + 10, maxk = 5000 + 10;

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

int n, k, L[maxn];
string dp[maxn][maxk], s[maxn];
char tmp[maxk];

int main()
{
#ifdef CraZYali
	file("aba");
#endif
	n = read<int>();k = read<int>();
	REP(i, 1, n)
	{
		scanf("%s", tmp);
		s[i] = tmp;
		L[i] = s[i].size();
	}
	REP(i, 1, n)
	{
		/*
		if (i) REP(j, 0, k)
		{
			if (!dp[i][j].size()) dp[i][j] = dp[i - 1][j];
			else if (dp[i - 1][j].size()) chkmin(dp[i][j], dp[i - 1][j]);
		}
	//	REP(j, 0, k) printf("dp[%d][%d] = %s\n", i, j, dp[i][j].c_str());
		REP(j, 0, k) if (!(i + j) || dp[i][j].size())
			REP(l, i + 1, n) if (j + s[l].size() <= k)
			{
				string tmp = dp[i][j] + s[l];
	//			cerr << i << ' ' << j << ' ' << l << ' ' << tmp << endl;
				if (!dp[l][j + s[l].size()].size()) dp[l][j + s[l].size()] = tmp;
				else chkmin(dp[l][j + s[l].size()], tmp);
			}
			*/
		REP(j, 0, i - 1) REP(len, 0, k - L[i]) if (!(j + len) || dp[j][len].size())
		{
			string tmp = dp[j][len] + s[i];
			if (!dp[i][len + L[i]].size()) dp[i][len + L[i]] = tmp;
			else chkmin(dp[i][len + L[i]], tmp);
		}
	}
	REP(i, 1, n)
	{
		REP(j, 0, k)
		{
			if (dp[i-1][j].size())
				if (!dp[i][j].size()) dp[i][j] = dp[i-1][j];
				else chkmin(dp[i][j],dp[i-1][j]);
			if(dp[i][j].size())printf("dp[%d][%d] = %s\n", i, j, dp[i][j].c_str());
		}
	}
	string ans = "";
	REP(i, 1, n) if (dp[i][k].size())
		if (!ans.size()) ans = dp[i][k];
		else chkmin(ans, dp[i][k]);
	cout << ans << endl;
	return 0;
}
