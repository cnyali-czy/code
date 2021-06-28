/*
	Problem:	B.cpp
	Time:		2021-06-28 15:44
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
const int maxn = 2e5 + 10;

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

int n, m, a[maxn], b[maxn], pa[maxn], pb[maxn];

int main()
{
#ifdef CraZYali
	file("B");
#endif
	register int T = read<int>();
	while (T--)
	{
		n = read<int>();m = read<int>();
		REP(i, 0, n + 1) pb[i] = -1;
		REP(i, 1, n) pa[a[i] = read<int>()] = i;
		REP(i, 1, m) pb[pa[b[i] = read<int>()]] = i;
		int ans = 1;
		REP(i, 1, m)
		{
			int cnt = 0;
			if (pa[b[i]] > 1 && pb[pa[b[i]] - 1] < pb[pa[b[i]]]) cnt++;
			if (pa[b[i]] < n && pb[pa[b[i]] + 1] < pb[pa[b[i]]]) cnt++;
			(ans *= cnt) %= 998244353;
		}
		printf("%d\n", ans);
	}
	return 0;
}
