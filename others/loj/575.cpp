/*
	Problem:	575.cpp
	Time:		2021-03-29 20:54
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
const int maxn = 1e5 + 10, MOD = 998244353;

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

int n;
char str[maxn];

int f[2005][2005];
//前 i 个数，比最后一个小的有 j 个
int main()
{
#ifdef CraZYali
	file("575");
#endif
	scanf("%s", str + 1);
	n = strlen(str + 1) + 1;
	f[1][0] = 1;
	REP(i, 1, n - 1)
	{
		static int sum[maxn];
		sum[0] = f[i][0];REP(j, 1, i) sum[j] = (sum[j - 1] + f[i][j]) % MOD;
		if (str[i] == '<')
		{
			REP(k, 1, i) f[i + 1][k] = sum[k - 1];
		}
		else
		{
			REP(k, 0, i) f[i + 1][k] = (sum[i] - (k ? sum[k - 1] : 0) + MOD) % MOD;
		}
		/*
		REP(k, 0, i) REP(j, 0, i - 1)
		{
			if (str[i] == '<' && k >= j + 1) (f[i + 1][k] += f[i][j]) %= MOD;
			if (str[i] == '>' && k <= j    ) (f[i + 1][k] += f[i][j]) %= MOD;
		}
		*/
	}
	i64 ans = 0;
	REP(i, 0, n - 1) ans += f[n][i];
	cout << ans % MOD << endl;
	return 0;
}
