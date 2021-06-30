/*
	Problem:	B.cpp
	Time:		2021-06-29 08:57
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
const int maxn = 100 + 5, maxw = 100 + 5, MOD = 998244353;

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

int n, a[maxn], fac[maxn];
int f[maxn][maxw * maxw / 2], s;

void init(int n)
{
	fac[0] = 1;
	REP(i, 1, n) fac[i] = 1ll * i * fac[i - 1] % MOD;
}
inline void reduce(int &x) {x += x >> 31 & MOD;}
int main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read<int>();init(n);
	REP(i, 1, n) s += (a[i] = read<int>());
	f[0][0] = 1;
	REP(i, 1, n) DEP(j, i, 1) DEP(k, s / 2, a[i])
		reduce(f[j][k] += f[j - 1][k - a[i]] - MOD);
	if (s & 1) {puts("0");return 0;}
	i64 ans = 0;
	REP(i, 0, n) (ans += 1ll * fac[i] * fac[n - i] % MOD * f[i][s / 2]) %= MOD;
	cout << ans << endl;
	return 0;
}
