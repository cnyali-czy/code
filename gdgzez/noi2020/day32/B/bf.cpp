/*
	Problem:	B.cpp
	Time:		2020-07-23 08:12
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
const int maxn = 2000 + 10, MOD = 1e9 + 7;

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

int n, k, q, F[maxn];
int pre[maxn], invs[maxn], mem[maxn];

int f(int x)
{
	if (x <= k) return F[x];
	i64 ans = 0;
	REP(i, 0, k)
		ans += 1ll * pre[i] * mem[x] % MOD * invs[x - i] % MOD;
	return ans % MOD;
}

int main()
{
	freopen("B.in", "r", stdin);
	freopen("bf.out", "w", stdout);
	cin >> n >> k >> q;
	REP(i, 0, k) F[i] = read<int>();
	invs[0] = invs[1] = 1;
	REP(i, 2, max(n, k)) invs[i] = 1ll * (MOD - MOD / i) * invs[MOD % i] % MOD;
	REP(i, 0, k)
	{
		i64 res = 1;
		REP(j, 0, k) if (j ^ i)
			(res *= (j > i ? invs[j - i] : MOD - invs[i - j])) %= MOD;
		pre[i] = res * F[i] % MOD;
	}
	REP(i, k + 1, n)
	{
		i64 res = 1;
		REP(j, 0, k) (res *= i - j) %= MOD;
		mem[i] = res;
	}
	i64 ans = 0, qi = 1;
	REP(i, 0, n)
	{
		ans += f(i) * qi % MOD;
		(qi *= q) %= MOD;
	}
	cout << ans % MOD << endl;
	return 0;
}

