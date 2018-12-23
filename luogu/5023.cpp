#define  REP(i, s, e) for (register int i = s; i <= e; i++)
#define DREP(i, s, e) for (register int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>
#define int long long

using namespace std;
const int MOD = 1e9 + 7;

int ans[] = {0, 0, 12, 112, 912, 7136, 56768, 453504, 3626752};

int power_pow(int a, int b)
{
	int ans = 1, base = a;
	while (b)
	{
		if (b & 1) ans = ans * base % MOD;
		base = base * base % MOD;
		b >>= 1;
	}
	return (ans + MOD) % MOD;
}

signed main()
{
#ifdef CraZYali
	freopen("5023.in", "r", stdin);
	freopen("5023.out", "w", stdout);
#endif
	int n, m;
	cin >> n >> m;
	if (n > m) swap(n, m);
	if (n == 1) cout << power_pow(2, m);
	else if (n == m) cout << ans[n];
	else if (n == 2) cout << 4ll * power_pow(3, m - 1) % MOD;
	else if (n == 3) cout << 112ll * power_pow(3, m - 3) % MOD;
	else if (n == 5) cout << 2688ll * power_pow(3, m - 5) % MOD;
	else if (n == 6) cout << 170112ll * power_pow(3, m - 7) % MOD;
	else if (n == 7) cout << 1360128ll * power_pow(3, m - 8) % MOD;
	else if (n == 8) cout << 10879488ll * power_pow(3, m - 9) % MOD;
	return 0;
}
