/*
	Problem:	5788.cpp
	Time:		2020-08-13 19:54
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
const int maxn = 3e6 + 10;

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

int n, a[maxn], stk[maxn], top, f[maxn];

int main()
{
#ifdef CraZYali
	file("5788");
#endif
	n = read<int>();
	REP(i, 1, n) a[i] = read<int>();
	DEP(i, n, 1)
	{
		while (top && a[i] >= a[stk[top]]) top--;
		f[i] = stk[top];
		stk[++top] = i;
	}
	REP(i, 1, n) printf("%d%c", f[i], i == end_i ? '\n' : ' ');
	return 0;
}
