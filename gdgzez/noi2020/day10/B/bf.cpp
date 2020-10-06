/*
	Problem:	B.cpp
	Time:		2020-06-09 08:27
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cassert>
#include <iostream>
#include <cstdio>
#include <set>

using namespace std;
const int maxn = 5e5 + 10;

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

int n, a[maxn];
multiset <int> S;

int main()
{
	freopen("B.in", "r", stdin);
	freopen("bf.out", "w", stdout);
	n = read<int>();
	REP(i, 1, n)
	{
		a[i] = read<int>();
	}
	REP(i, 1, n)
	{
		S.emplace(a[i]);
		int res = 0;
		for (auto j : S)
			if (res < j) res++;
			else if (res > j) res--;
		printf("%d\n", res);
	}
	return 0;
}
