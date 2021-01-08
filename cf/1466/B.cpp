/*
	Problem:	B.cpp
	Time:		2020-12-30 22:39
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <set>
#include <algorithm>
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

int n, a[maxn], cnt[maxn << 1];

int main()
{
#ifdef CraZYali
	file("B");
#endif
	register int T = read<int>();
	while (T--)
	{
		n = read<int>();
		set <int> ssr;
		REP(i, 1, n) cnt[a[i] = read<int>()]++;
		int m = unique(a + 1, a + 1 + n) - a - 1;
		DEP(i, m, 1)
			if (!cnt[a[i] + 1])
			{
				ssr.emplace(a[i] + 1);
				cnt[a[i]]--;
				if (cnt[a[i]]) ssr.emplace(a[i]);
			}
			else ssr.emplace(a[i]);
		printf("%d\n", ssr.size());
		REP(i, 1, n) cnt[a[i]] = 0;
	}
	return 0;
}
