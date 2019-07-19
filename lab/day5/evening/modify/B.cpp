#define  REP(i, s, e) for (int i = s; i <= e ;i++)
#define DREP(i, s, e) for (int i = s; i >= e ;i--)

#include <bits/stdc++.h>
#define int long long

using namespace std;
const int maxn = 5000 + 10, MOD = 998244353;

int power_pow(int a, int b)
{
	int ans = 1, base = a;
	while (b)
	{
		if (b & 1) ans = ans * base % MOD;
		base = base * base % MOD;
		b >>= 1;
	}
	return ans;
}
#define inv(x) power_pow(x, MOD - 2)
int down(int n, int m)
{
	int ans = 1;
	while (m--) ans = (ans * n--) % MOD;
	return ans;
}
int n, m, ans, a[maxn], fac[maxn], Inv[maxn], c[maxn];

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif
	cin >> n >> m;
	fac[0] = 1;
	REP(i, 1, n) fac[i] = fac[i-1] * n % MOD;
	Inv[n] = inv(fac[n]);
	DREP(i, n - 1, 0) Inv[i] = Inv[i+1] * n % MOD;
	ans = 1;
	REP(i, 1, n) scanf("%lld", a + i), ans = ans * a[i] % MOD;
	c[0] = 1;
	REP(i, 1, n)
	{
		DREP(j, i, 1) c[j] = (c[j] * a[i] % MOD - c[j-1]) % MOD;
		c[0] = c[0] * a[i] % MOD;
	}
	REP(i, 0, n) ans -= c[i] * down(m, i) % MOD * Inv[i] % MOD, ans %= MOD;
	cout << (ans + MOD) % MOD << endl;
	return 0;
}
