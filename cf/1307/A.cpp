/*
	Problem:	A.cpp
	Time:		2020-02-21 11:01
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <iostream>
#include <cstdio>
#define int long long
using namespace std;

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

signed main()
{
#ifdef CraZYali
	file("A");
#endif
	register int T = read<int>();
	while (T--)
	{
		int n = read<int>(), m = read<int>(), ans = read<int>();
		REP(i, 2, n)
		{
			int x = read<int>();
			if (x * (i - 1) <= m)
			{
				ans += x;
				m -= x * (i - 1);
			}
			else
			{
				ans += m / (i - 1);
				m = -1;
			}
		}
		cout << ans << '\n';
	}
	return 0;
}
