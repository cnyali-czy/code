#define REP(i, s, e) for (int i = s; i <= e ;i++)

#include <bits/stdc++.h>
#define int long long 

using namespace std;
const int maxn = 2000 + 10, MOD = 998244353;

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

int n, k, x[maxn], y[maxn], ans;

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("4781.in", "r", stdin);
	freopen("4781.out", "w", stdout);
#endif
	cin >> n >> k;
	REP(i, 1, n) scanf("%lld%lld", x + i, y + i);
	REP(i, 1, n)
	{
		int up(1), down(1);
		REP(j, 1, n)
			if (i != j) up = up * (k - x[j]) % MOD, down = down * inv(x[i] - x[j]) % MOD;
		ans += y[i] * up % MOD * down % MOD, ans %= MOD;
	}
	cout << (ans + MOD) % MOD << endl;
	return 0;
}
