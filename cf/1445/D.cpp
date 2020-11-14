/*
	Problem:	D.cpp
	Time:		2020-11-01 19:55
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
#define i64 long long
using namespace std;
const int maxn = 3e5 + 10, MOD = 998244353;

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

int abs(int x) {return max(x, -x);}

int a[maxn], b[maxn];
int fac[maxn], invs[maxn], Inv[maxn];
int C(int n, int m) {return 1ll * fac[n] * Inv[m] % MOD * Inv[n - m] % MOD;}

int main()
{
#ifdef CraZYali
	file("D");
#endif
	const int N = 3e5;
	fac[0] = invs[0] = Inv[0] = 1;
	fac[1] = invs[1] = Inv[1] = 1;
	REP(i, 2, N)
	{
		fac[i] = 1ll * i * fac[i - 1] % MOD;
		invs[i] = 1ll * (MOD - MOD / i) * invs[MOD % i] % MOD;
		Inv[i] = 1ll * Inv[i - 1] * invs[i] % MOD;
	}
	int n = read<int>();
	i64 ans = 0;
	REP(i, 1, n) a[i] = read<int>();sort(a + 1, a + 1 + n);
	REP(i, 1, n) b[i] = read<int>();sort(b + 1, b + 1 + n);reverse(b + 1, b + 1 + n);
	REP(i, 1, n) ans += abs(a[i] - b[i]);
	cout << ans % MOD * C(n + n, n) % MOD << endl;
	return 0;
}
