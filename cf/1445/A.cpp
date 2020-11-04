/*
	Problem:	A.cpp
	Time:		2020-11-01 19:05
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <set>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 50 + 5;

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

int n, x, a[maxn], b[maxn];
multiset <int> s;

int main()
{
#ifdef CraZYali
	file("A");
#endif
	register int T = read<int>();
	while (T--)
	{
		n = read<int>();x = read<int>();
		REP(i, 1, n) a[i] = read<int>();
		REP(i, 1, n) b[i] = read<int>();
		sort(a + 1, a + 1 + n);
		sort(b + 1, b + 1 + n);reverse(b + 1, b + 1 + n);
		bool flag = 1;
		REP(i, 1, n) if (a[i] + b[i] > x) {flag = 0;break;}
		puts(flag ? "Yes" : "No");
	}
	return 0;
}
