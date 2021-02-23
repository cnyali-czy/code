/*
	Problem:	check.cpp
	Time:		2021-02-21 11:31
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
const int maxn = 1e6 + 10;

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

inline bool ok(int a, int b, int c)
{
	return a + b + c > 2 * max(max(a, b), c);
}

int a[maxn], b[maxn], c[maxn];

int main()
{
	FILE *fin = fopen("B.in", "r"), *fans = fopen("B.out", "r");
	freopen("check.out", "w", stdout);
	int n;fscanf(fin, "%d", &n);
	REP(i, 1, n) fscanf(fans, "%d%d%d", a + i, b + i, c + i);
	REP(i, 1, n) if (!ok(a[i], b[i], c[i])) printf("fuck %d (%d, %d, %d)\n", i, a[i], b[i], c[i]);
	sort(a + 1, a + 1 + n);
	sort(b + 1, b + 1 + n);
	sort(c + 1, c + 1 + n);
	int res = 0;
	REP(i, 1, n) if (ok(a[i], b[i], c[i])) res++;
	printf("n = %d, best = %d\n", n, res);
	return 0;
}
