/*
	Problem:	C.cpp
	Time:		2020-10-22 19:20
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <bitset>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 5e4 + 10;

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

int n, m;

bitset <maxn> all, sg;

int main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();m = read<int>();
	REP(i, 1, n) all.set(i);
	DEP(i, n, 1)
	{
		sg = (~sg) & all;
		sg = (sg << i) | (sg >> i);
	}
	while (m--) putchar(sg.test(read<int>()) + '0');
	return 0;
}
