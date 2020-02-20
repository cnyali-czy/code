/*
	Problem:	B.cpp
	Time:		2020-02-20 21:50
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cstring>
#include <iostream>
#include <cstdio>
#define int long long
using namespace std;
const int maxn = 21;

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

int n, a[maxn], f[1 << maxn], S;

signed main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read<int>();
	REP(i, 0, n - 1) S += (a[i] = read<int>());
	REP(ans, n + 1 >> 1, n - 1)
	{
		memset(f, 0x3f, sizeof f);f[0] = 0;
		REP(i, 1, (1 << n) - 1)
		{
			REP(j, 0, n - 1) if (i & 1 << j) chkmin(f[i], f[i ^ 1 << j] + S - a[j] * ans);
			if (f[i] == S) f[i] = 0;
		}
		if (f[(1 << n) - 1] <= 0)
		{
			cout << ans << endl;
			return 0;
		}
	}
	return 0;
}
