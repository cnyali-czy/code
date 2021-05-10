/*
	Problem:	2169.cpp
	Time:		2021-05-06 16:22
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
const int maxn = 20000 + 10;

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

int n, a[maxn], b[maxn];

int main()
{
#ifdef CraZYali
	file("2169");
#endif
	n = read<int>();
	REP(i, 1, n) a[read<int>()] = i;
	int t = 0;
	REP(i, 1, n) printf("%d%c", t += a[i], i == end_i ? '\n' : ' ' );
	DEP(i, n, 1)
	{
		t += a[i];
		b[i] = t;
	}
	REP(i, 1, n) printf("%d%c", b[i], i == end_i ? '\n' :  ' ' );
	return 0;
}
