/*
	Problem:	D.cpp
	Time:		2020-04-03 23:12
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
const int maxn = 500 + 10;

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

int n, d;
signed main()
{
#ifdef CraZYali
	file("D");
#endif
	register int T = read<int>();
	while (T--)
	{
		d = read<int>();const int MOD = read<int>();
		int cur = 0, ans = 0, y = 1, yy = 2;
		int ccc = 0;
		while (cur < d)
		{
			int l = min(1ll << ccc, d - cur);
			cur += l;
			(ans += l * y % MOD) %= MOD;
			(y *= yy) %= MOD;
			(yy += (1 << ccc)) %= MOD;
			ccc++;
//			cout << l << ' ' << d << endl;
		}
		printf("%lld\n", ans);
//		puts("");
	}
	return 0;
}
