/*
	Problem:	C.cpp
	Time:		2020-03-08 10:29
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cstdio>
#define int long long
using namespace std;
const int MOD = 1e9 + 7;
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

int n, k;

signed main()
{
#ifdef CraZYali
	file("C");
#endif
	REP(k, 2, 10)
	{
		int ans = 0;
		REP(n, 1, 100)
		{
			int x = n;
			__int128 l = x;
			REP(i, 1, k)
				l = l * (x + i) / __gcd(l, (__int128)x + i);
			(ans += l % MOD) %= MOD;
			cout << n << ' ' << k << ' ' << ans << '\n';
		}
	}
	return 0;
}
