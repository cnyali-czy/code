/*
	Problem:	B.cpp
	Time:		2020-05-01 19:43
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
const int maxn = 2e5 + 10, MOD = 998244353;
#define i64 long long

int power_pow(i64 base, int b)
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

const int inv2 = MOD + 1 >> 1;
int n, q, fac[maxn], Inv[maxn], bin[maxn], pre[maxn];
inline int C(int n, int m) {return n < m || m < 0 ? 0 : 1ll * fac[n] * Inv[m] % MOD * Inv[n - m] % MOD;}
inline void init(int N)
{
	fac[0] = Inv[0] = 1;
	REP(i, 1, N) fac[i] = 1ll * fac[i - 1] * i % MOD;
	Inv[N] = inv(fac[N]);
	DEP(i, N - 1, 0) Inv[i] = Inv[i + 1] * (i + 1ll) % MOD;
	bin[0] = 1;
	REP(i, 1, N) bin[i] = 1ll * bin[i - 1] * inv2 % MOD;
	REP(i, 1, N) pre[i] = (pre[i - 1] + 1ll * bin[i] * C(i - 1, n - 1)) % MOD;
}
int range(int l, int r, int k)
{
	if (l > r) return 0;
	return 1ll * (pre[r - k] - pre[l - k - 1] + MOD) % MOD * bin[k] % MOD;
}
int a[maxn], F[500][maxn], cnt, vis[maxn];
int calc(int l, int k)
{
	if (!vis[k])
	{
		vis[k] = ++cnt;
		int res = 0;
		DEP(i, n + n - 1, 1)
		{
			F[cnt][i] = (res + 1ll * C(i - k, n - k) * bin[i]) % MOD;
			res = (res + 1ll * C(i - k - 1, n - k - 1) * bin[i] % MOD) % MOD;
		}
	}
	return F[vis[k]][l];
}
int main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read<int>();q = read<int>();
	init(n + n);
	while (q--)
	{
		int k(read<int>()), ans(0);
		REP(i, 1, k) a[i] = read<int>();a[k + 1] = n + n;
		REP(i, 0, k) (ans += range(a[i] + 1, a[i + 1] - 1, i)) %= MOD;
		cout << 2ll * (ans + calc(a[k], k)) % MOD << '\n';
	}
	return 0;
}
