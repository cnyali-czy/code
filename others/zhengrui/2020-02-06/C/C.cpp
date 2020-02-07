/*
 * File Name:	C.cpp
 * Author	:	CraZYali
 * Time		:	2020.02.06 12:01
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <unordered_map>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 500 + 10, MOD = 998244353;
const long long llim = 100ll * MOD;

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

int n, m, a[maxn];
unordered_map <int, long long> dp[maxn];
//[1 << 9];

int main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();
	m = read<int>();
	int tot = 0;
	dp[0][0] = 1;
	REP(i, 1, n) tot ^= (a[i] = read<int>());
	REP(Case, 1, m)
	{
		int x = read<int>();
		tot ^= a[x];
		tot ^= (a[x] = read<int>());
		REP(i, Case == 1 ? 1 : x, n)
		{
			dp[i].clear();
			for (auto I : dp[i-1])
			{
				int k = I.first, lst = I.second;
				REP(j, 0, a[i])
				{
					dp[i][j ^ k] += lst;
					if (dp[i][j ^ k] >= llim) dp[i][j ^ k] -= llim;
				}
			}
		}
		printf("%lld\n", dp[n][tot] % MOD);
	}
	return 0;
}
