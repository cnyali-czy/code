/*
	Problem:	2266.cpp
	Time:		2021-05-08 10:14
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
const int maxn = 505;

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

int n, x[maxn], a[maxn * maxn];

int main()
{
#ifdef CraZYali
	file("2266");
#endif
	n = read<int>();
	REP(i, 1, n) x[i] = read<int>();
	static int id[maxn];
	REP(i, 1, n) id[i] = i;
	sort(id + 1, id + 1 + n, [&](int i, int j) {return x[i] < x[j];});
	int j = 1;
	REP(I, 1, n)
	{
		int i = id[I];
		if (a[x[i]]) return 0 * puts("No");
		a[x[i]] = i;
		REP(k, 1, i - 1)
		{
			while (a[j]) j++;
			if (j > x[i]) return 0 * puts("No");
			a[j] = i;
		}
	}
	j = n * n;
	DEP(I, n, 1)
	{
		int i = id[I];
		REP(k, 1, n - i)
		{
			while (a[j]) j--;
			if (j < x[i]) return 0 * puts("No");
			a[j] = i;
		}
	}
	puts("Yes");
	REP(i, 1, n * n) printf("%d%c", a[i], i == end_i ? '\n' : ' ' );
	return 0;
}
