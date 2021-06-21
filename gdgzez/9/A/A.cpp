/*
    Problem:    A.cpp
    Time:       2021-06-17 16:43
    Author:     CraZYali
    E-Mail:     yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cmath>
#include <iostream>
#include <cstdio>
#define int __int128

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

int n, q, a[maxn];

int f[maxn][2];
int pick[maxn][2];

signed main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();
	REP(i, 1, n) a[i] = read<int>();
	q = read<int>();
	while (q--)
	{
		int x = read<int>(), ans = 0;
		int l = -1e16, r = 1e16;
		while (l <= r)
		{
			int mid = (l + r >> 1);
			REP(i, 1, n)
			{
				f[i][1] = f[i - 1][0] + a[i] * x - mid;
				pick[i][1] = pick[i - 1][0] + 1;

				int flg = (f[i - 1][1] > f[i - 1][0] || f[i - 1][1] == f[i - 1][0] && pick[i - 1][1] < pick[i - 1][0]);
				f[i][0] = f[i - 1][flg];
				pick[i][0] = pick[i - 1][flg];
			}
			int flg = (f[n][1] > f[n][0] || f[n][1] == f[n][0] && pick[n][1] < pick[n][0]);
			ans = f[n][flg] / x + mid;
			if (pick[n][flg] >= x) l = mid + 1;
			else r = mid - 1;
		}
		printf("%lld\n", (long long)ans);
	}
	return 0;
}
