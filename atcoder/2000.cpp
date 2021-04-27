#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <set>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 2000 + 10, MOD = 1e9 + 7;

int n, k;

int fac[maxn * maxn], invs[maxn * maxn], Invs[maxn * maxn];
void init(int n)
{
	fac[0] = invs[0] = Invs[0] = 1;
	fac[1] = invs[1] = Invs[1] = 1;
	REP(i, 2, n)
	{
		fac[i] = 1ll * i * fac[i - 1] % MOD;
		invs[i] = 1ll * (MOD - MOD / i) * invs[MOD % i] % MOD;
		Invs[i] = 1ll * invs[i] * Invs[i - 1] % MOD;
	}
}
inline i64 C(int n, int m) {return n == m ? 1 : n < m || m < 0 ? 0 : 1ll * fac[n] * Invs[m] % MOD * Invs[n - m] % MOD;}

int f[maxn][maxn];

int main()
{
#ifdef CraZYali
	freopen("2000.in", "r", stdin);
	freopen("2000.out", "w", stdout);
#endif
	cin >> n >> k;
	if (k == 1)
	{
		puts("1");
		return 0;
	}
	init(n * k);
	f[0][0] = 1;
	REP(i, 0, n) REP(j, 0, i) if (f[i][j])
	{
		//place a white ball
		(f[i + 1][j] += f[i][j]) %= MOD;
		if (j < i)
			f[i][j + 1] = (f[i][j + 1] + C(n * k - i - j * (k - 1) - 1, k - 2) * (n - j) % MOD * f[i][j]) % MOD;
	}
	cout << f[n][n] << '\n';
	return 0;
}
