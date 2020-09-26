/*
	Problem:	F.cpp
	Time:		2020-09-26 22:01
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
#define i64 long long
using namespace std;
const int maxk = 5000 + 10, MOD = 998244353;

i64 power_pow(i64 base, int b)
{
	i64 ans = 1;
	while (b)
	{
		if (b & 1) (ans *= base) %= MOD;
		(base *= base) %= MOD;
		b >>= 1;
	}
	return ans;
}
#define inv(x) power_pow(x, MOD - 2)

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

int n, m, k;
int str[maxk][maxk];

int main()
{
#ifdef CraZYali
	file("F");
#endif
	cin >> n >> m >> k;
	str[0][0] = 1;
	REP(i, 1, k)
		REP(j, 0, i) str[i][j] = ((j ? str[i - 1][j - 1] : 0) + 1ll * str[i - 1][j] * j) % MOD;
	i64 p = inv(m);

	i64 ans = 0, nn = n, pj = p;
	REP(j, 1, min(n, k))
	{
		ans += nn * pj % MOD * str[k][j] % MOD;
		(pj *= p) %= MOD;
		(nn *= (n - j)) %= MOD;
	}
	cout << ans % MOD << endl;
	return 0;
}
