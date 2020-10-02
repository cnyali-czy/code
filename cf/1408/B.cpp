/*
	Problem:	B.cpp
	Time:		2020-10-02 19:50
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 100 + 5;

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

int n, k, a[maxn], b[maxn];

int main()
{
#ifdef CraZYali
	file("B");
#endif
	register int T = read<int>();
	while (T--)
	{
		n = read<int>();k = read<int>();
		REP(i, 1, n) b[i] = a[i] = read<int>();
		int m = unique(b + 1, b + 1 + n) - b - 1;
		if (m <= k) puts("1");
		else if (k == 1) puts("-1");
		else printf("%d\n", (m - k + k - 2) / (k - 1) + 1);
	}
	return 0;
}
