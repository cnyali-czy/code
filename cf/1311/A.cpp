/*
	Problem:	A.cpp
	Time:		2020-02-24 22:36
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

int main()
{
#ifdef CraZYali
	file("A");
#endif
	register int T = read<int>();
	while (T--)
	{
		int a = read<int>(), b = read<int>(), ans;
		swap(a, b);
		if (a == b)
		{
			puts("0");
			continue;
		}
		if (b > a)
		{
			if ((b - a) & 1) ans = 2;
			else ans = 1;
		}
		else
		{
			if ((a - b) & 1) ans = 1;
			else ans = 2;
		}
		cout << ans << '\n';
	}
	return 0;
}
