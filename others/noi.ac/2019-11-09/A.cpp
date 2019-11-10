/*
 * File Name:	A.cpp
 * Author	:	CraZYali
 * Year		:	2019.11.09 20:16
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <iostream>
#include <cstdio>

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

int main()
{
#ifdef CraZYali
	file("A");
#endif
	register int T(read<int>());
	while (T--)
	{
		long long n(read<long long>());
		bool flag(1);
		for (long long i(1); i <= n; i++)
		{
			if (n % (i + 1) == 0)
			{
				flag = 0;
				break;
			}
			n -= n / (i + 1);
		}
		printf("%lld\n", flag ? n : -1);
	}
	return 0;
}
