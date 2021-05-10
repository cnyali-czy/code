/*
	Problem:	2164.cpp
	Time:		2021-05-06 08:59
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
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
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, m, d[maxn], ans[maxn], x[maxn];
long long k;

int main()
{
#ifdef CraZYali
	file("2164");
#endif
	n = read<int>();
	REP(i, 1, n) x[i] = read<int>();
	REP(i, 1, n) d[i] = ans[i] = i;
	m = read<int>();k = read<long long>();
	REP(fk, 1, m)
	{
		int x = read<int>();
		swap(d[x], d[x + 1]);
	}
	while (k)
	{
		static int tmp[maxn];
		if (k & 1)
		{
			REP(i, 1, n) tmp[i] = ans[d[i]];
			REP(i, 1, n) ans[i] = tmp[i];
		}
		if (k >>= 1)
		{
			REP(i, 1, n) tmp[i] = d[d[i]];
			REP(i, 1, n) d[i] = tmp[i];
		}
	}
	static long long Ans[maxn];
	REP(i, 1, n) Ans[i] = x[ans[i]] - x[ans[i] - 1];
	REP(i, 1, n) printf("%lld.0\n", Ans[i] += Ans[i - 1]);
	return 0;
}
