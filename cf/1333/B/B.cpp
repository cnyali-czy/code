/*
	Problem:	B.cpp
	Time:		2020-04-08 22:42
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

int n, a[maxn], b[maxn];

bool flag[maxn][3];

int main()
{
#ifdef CraZYali
	file("B");
#endif
	register int T = read<int>();
	while (T--)
	{
		n = read<int>();
		REP(i, 1, n) a[i] = read<int>();
		REP(i, 1, n) b[i] = read<int>();
		REP(i, 1, n)
			REP(j, 0, 2)
			flag[i][j] = (flag[i-1][j] | (a[i] == j - 1));
		bool nice = 1;
		DEP(i, n, 1)
			if (b[i] == a[i]) continue;
			else if (b[i] < a[i]) nice &= flag[i-1][0];
			else nice &= flag[i-1][2];
		puts(nice ? "YES" : "NO");
	}
	return 0;
}
