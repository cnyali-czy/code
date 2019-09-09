/*
 * File Name:	E.cpp
 * Author	:	CraZYali
 * Year		:	2019.09.09 23:01
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 100, MOD = 1e9 + 7;

template <typename T> inline T read()
{
	T ans(0), flag(1);
	char c(getchar());
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

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout);

int power_pow(long long base, int b)
{
	long long ans(1);
	for (; b; b >>= 1) (ans *= (b & 1 ? base : 1)) %= MOD, (base *= base) %= MOD;
	return ans;
}
int Inv[maxn];
#define inv(x) (x ? Inv[x] ? Inv[x] : Inv[x] = power_pow(x, MOD - 2) : 0)

inline int C(long long n, int m)
{
	n %= MOD;
	if (n < 0 || m < 0 || n < m) return 0;
	if (!n || !m) return 1;
	long long ans(1);
	REP(i, 1, m) (ans *= n) %= MOD, n--;
	REP(i, 1, m) (ans *= inv(i)) %= MOD;
	return ans;
}
int n;
long long m, a[maxn];

int main()
{
#ifdef CraZYali
	file("E");
#endif
	cin >> n >> m;
	REP(i, 1, n) a[i] = read<long long>();
	int ans = C(n + m - 1, n - 1);
	REP(x, 1, (1<<n) - 1)
	{
		long long t(n+m);
		int p(0);
		REP(i, 1, n)
			if (x & (1 << i-1)) ++p, t -= a[i];
		t -= p + 1;
		(ans -= ((p & 1) ? 1 : -1) * C(t, n - 1)) %= MOD;
	}
	cout << (ans + MOD) % MOD << endl;
	return 0;
}
