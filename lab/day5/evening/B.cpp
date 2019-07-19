#define REP(i, s, e) for (int i = s; i <= e ;i++)

#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 5000 + 10, maxm = 1e8 + 10, MOD = 998244353;

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

int m, n, k, a[maxn], ans;

void dfs(int x, int res = 0)
{
	if (x == m) ans = (ans + res) % MOD;
	else
	{
		x++;
		REP(i, 1, n)
		{
			a[i]--;
			int temp = 1;
			REP(j, 1, n)
				if (i ^ j) temp = temp * a[j] % MOD;
			dfs(x, (res + temp) % MOD);
			a[i]++;
		}
	}
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, n) scanf("%lld", a + i);
	dfs(0);
	ans = ans * inv(power_pow(n, m)) % MOD;
	cout << (ans + MOD) % MOD << endl;
	return 0;
}
