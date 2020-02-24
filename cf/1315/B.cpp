/*
	Problem:	B.cpp
	Time:		2020-02-24 00:18
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
#define int long long
using namespace std;
const int maxn = 1e5 + 10;

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

int a, b, p, n;
char s[maxn];
int dp[maxn];
signed main()
{
#ifdef CraZYali
	file("B");
#endif
	register int T = read<int>();
	while (T--)
	{
		a = read<int>();
		b = read<int>();
		p = read<int>();
		scanf("%s", s + 1);
		n = strlen(s + 1);
		if (n == 1)
		{
			puts("1");
			continue;
		}
		dp[n] = 0;
		DEP(i, n - 1, 1)
		{
			if (s[i] == s[i + 1])
			{
				if (i == n - 1) dp[i] = dp[i + 1] + (s[i] == 'A' ? a : b);
				else dp[i] = dp[i + 1];
			}
			else dp[i] = dp[i + 1] + (s[i] == 'A' ? a : b);
		}
		dp[0] = 1e9 + 5;
		DEP(i, n, 1) if (p >= dp[i] && p < dp[i - 1])
		{
			cout << i << '\n';
			break;
		}
	}
	return 0;
}
