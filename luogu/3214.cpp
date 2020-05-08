/*
	Problem:	3214.cpp
	Time:		2020-04-30 22:57
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
const int MOD = 1e8 + 7;

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
#define int long long
int power_pow(int base, int b)
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
#define inv(x) power_pow(x, MOD - 2)
int n, m;
const int maxn = 1e6 + 10;

int f[maxn], a[maxn];

signed main()
{
#ifdef CraZYali
	file("3214");
#endif
	cin >> n >> m;
	int Inv = 1;
	REP(i, 2, m) (Inv *= i) %= MOD;
	Inv = inv(Inv);
	a[0] = 1;
	const int base = power_pow(2, n);
	REP(i, 1, n) a[i] = a[i - 1] * (base - i + MOD) % MOD;
	f[0] = 1;
	REP(i, 2, m)
	{
		f[i] = (a[i - 1] - f[i - 1] + MOD) % MOD;
		(f[i] -= f[i - 2] * (i - 1) % MOD * (base - i + 1) % MOD) %= MOD;
	}
	cout << Inv * (f[m] + MOD) % MOD << endl;
	return 0;
}
