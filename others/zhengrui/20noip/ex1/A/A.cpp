/*
	Problem:	A.cpp
	Time:		2020-12-18 09:57
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
#define int long long

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

int n, a[maxn], ans[maxn], res[maxn];

signed main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();
	REP(i, 1, n) a[i] = read<int>();
	int s = 0, pos = 1;
	REP(i, 1, n)
	{
		if (s < 0)
		{
			pos = i;
			s = 0;
		}
		s += a[i];
		res[i] = s;
		ans[i] = pos;
	}
	s = 0;pos = n;
	DEP(i, n, 1)
	{
		if (s <= 0)
		{
			pos = i;
			s = 0;
		}
		s += a[i];
		if (s > res[i])
		{
			res[i] = s;
			ans[i] = pos;
		}
		else if (s == res[i])
		{
			ans[i] = min(ans[i], pos);
		}
	}
	REP(i, 1, n) printf("%lld%c", ans[i], i == end_i ? '\n' : ' ');
	return 0;
}
