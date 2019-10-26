/*
 * File Name:	A.cpp
 * Author	:	CraZYali
 * Year		:	2019.10.19 14:15
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1000 + 10, maxm = 1000 + 10;

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

char s[maxn][maxm];

int c1, c2;
char qaq[10];

int main()
{
#ifdef CraZYali
	file("A");
#endif
	register int T = read<int>();
	while (T--)
	{
		register int n = read<int>(), m = read<int>();
		REP(i, 1, n)
			scanf("%s", s[i] + 1);
		bool flag = 0;
		REP(i, 2, n)
			REP(j, 2, m)
			if (s[i-1][j] == s[i][j-1])
			{
				flag = 1;
				goto keng;
			}
keng:;
	 printf("%s\n", flag ? "Yes" : "No");
	}
	return 0;
}
