/*
	Problem:	3228.cpp
	Time:		2021-03-05 14:42
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

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, k, m, p;

int power_pow(int base, int b, const int MOD)
{
	int ans = 1;
	while (b)
	{
		if (b & 1) (ans *= base) %= MOD;
		(base *= base) %= MOD;
		b >>= 1;
	}
	return ans;
}

signed main()
{
#ifdef CraZYali
	file("3228");
#endif
	cin >> n >> k >> m >> p; p *= 2;
	int ans = (1 + m - k * (1 + m) + 2 * n) % p * power_pow(m, k - 1, p) % p;
	ans = (ans + p) % p;
	cout << ans / 2 << endl;
	return 0;
}
