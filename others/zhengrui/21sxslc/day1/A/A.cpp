/*
	Problem:	A.cpp
	Time:		2020-12-27 08:45
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cmath>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 2000 + 10;

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
int n;

int c1(int n) {return n == 0 ? 0 : (int)ceil(log2(n));}

int main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();
	REP(x, 1, n)
	{
		int ans = 1 + c1(n);
		REP(y, x, n)
		{
			int res = 0;
			ans = max(ans, 2 * c1(n - x + 1) + 1);
		}
		printf("%d%c", ans, x == end_x ? '\n' : ' ');
	}
	return 0;
}
