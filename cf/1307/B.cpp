/*
	Problem:	B.cpp
	Time:		2020-02-21 11:09
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
#include <cmath>

using namespace std;
#define int long long
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

int n, m, a[maxn];

signed main()
{
#ifdef CraZYali
	file("B");
#endif
	register int T = read<int>();
	while (T--)
	{
		n = read<int>();m = read<int>();
		int ans = 1e9;
		REP(i, 1, n)
		{
			int x = read<int>();
			if (x == m) ans = 1;
			else if (x > m) chkmin(ans, 2);
			else chkmin(ans, m / x + (m % x == 0 ? 0 : 1));
		}
		cout << ans << endl;
	}
	return 0;
}
