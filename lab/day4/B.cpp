#define REP(i, s, e) for (int i = s; i <= e; i++)

#include <bits/stdc++.h>
#define int long long

using namespace std;
const int maxn = 1000 + 10, maxm = 1000 + 10, MOD = 1e9 + 7;

int m, n, k, ans, f[maxn];

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif
	cin >> n >> m;k = max(n, m);
	f[1] = f[2] = 1;
	REP(i, 3, k) f[i] = f[i-1] + f[i-2];
	REP(i, 1, n)
		REP(j, 1, m)
		{
			ans += __gcd(f[i], f[j]);
			if (ans >= MOD) ans %= MOD;
		}
	cout << ans % MOD << endl;
	return 0;
}
