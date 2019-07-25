#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)

#include <bits/extc++.h>
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 1e7 + 10, MOD = 1e9 + 7;

int power_pow(int a, int b)
{
	int ans(1), base(a);
	while (b)
	{
		if (b & 1) ans = ans * base % MOD;
		base = base * base % MOD;
		b >>= 1;
	}
	return (ans + MOD) % MOD;
}
#define inv(x) power_pow(x, MOD - 2)
int n;
int fac[maxn], Inv[maxn];
int C(int n, int m) {return n < m || m < 0 ? 0 : fac[n] * Inv[n-m] % MOD * Inv[m] % MOD;}

int solve(int S, int n)
{
	int res(0), cur(-1);
	REP(i, 0, n) res += (cur *= -1) * C(n, i) * C(S - i * 10 + n - 1, n - 1) % MOD, res %= MOD;
	return (res + MOD) % MOD;
}
__gnu_pbds::gp_hash_table <int,int> cnt;
__gnu_pbds::gp_hash_table <int,int> :: iterator it;

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif
	Inv[0] = fac[0] = 1;
	REP(i, 1, 1e6) fac[i] = fac[i-1] * i % MOD;
	Inv[(int)1e6] = inv(fac[(int)1e6]);
	DREP(i, 1e6-1, 1) Inv[i] = Inv[i+1] * (i+1) % MOD;
	int T;cin >> T;
	while (T--)
	{
		scanf("%lld", &n);
		int ans = 0;
		if (n % 2 == 0) ans = power_pow(10, n >> 1);
		else if (n == 1) ans = 1;
		else if (n == 3) ans = 5;
		else if (n % 4 == 1) REP(i, 0, 4) ans += solve(i + 9 * (n >> 2), n >> 1) % MOD, ans %= MOD;
		else
		{
			cnt.clear();
			REP(i, 0, 4) REP(j, 0, 9) cnt[i-j]++;
			for (it = cnt.begin(); it != cnt.end(); it++)
				ans += solve(it -> first + 9 * (n >> 2), (n >> 1) - 1) * it -> second % MOD, ans %= MOD;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
