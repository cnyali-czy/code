/*
	Problem:	B.cpp
	Time:		2020-04-10 22:47
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <queue>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
const int maxn = 1e5 + 10;
const double eps = 1e-8;
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

int n, x, a[maxn];

int main()
{
#ifdef CraZYali
	file("B");
#endif
	register int T = read<int>();
	while (T--)
	{
		n = read<int>();x = read<int>();
		REP(i, 1, n) a[i] = read<int>();
		sort(a + 1, a + 1 + n, greater <int> ());
		long long s = 0;
		int ans = 0;
		REP(i, 1, n)
		{
			s += a[i];
			if (s < 1ll * i * x)
			{
				ans = i - 1;
				break;
			}
			if (i == n) ans = n;
		}
		cout << ans << '\n';
	}
	return 0;
}
