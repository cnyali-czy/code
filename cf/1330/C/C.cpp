/*
	Problem:	C.cpp
	Time:		2020-04-03 22:56
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

int n, m, l[maxn], p[maxn];

int main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();m = read<int>();
	long long tot = 0;
	REP(i, 1, m) l[i] = read<int>(), tot += l[i], p[i] = i;
	if (tot < n)
	{
		puts("-1");
		return 0;
	}
	REP(i, 1, m) if (i + l[i] - 1 > n)
	{
		puts("-1");
		return 0;
	}
	REP(i, 1, m) if (i + l[i] - 1 == n)
	{
		REP(j, 1, m) printf("%d ", j);
		return 0;
	}
	DEP(i, m, 1)
	{
		if (p[i] + l[i] - 1 >= n)
		{
			n = 0;
			break;
		}
		else
		{
			n -= l[i];
			p[i] = n + 1;
		}
	}
	if (n > 0)
		puts("-1");
	else
		REP(i, 1, m) printf("%d ", p[i]);
	return 0;
}
