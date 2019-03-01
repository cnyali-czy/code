#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>
#define int long long

using namespace std;
const int MOD = 100003;

int power_pow(int a, int b)
{
	int ans = 1, base = a;
	while (b)
	{
		if (b & 1) (ans *= base) %= MOD;
		(base *= base) %= MOD;
		b >>= 1;
	}
	return (ans + MOD) % MOD;
}

signed main()
{
#ifdef CraZYali
	freopen("1008.in", "r", stdin);
	freopen("1008.out", "w", stdout);
#endif
	int n, m;
	cin >> m >> n;
	cout << ((power_pow(m, n) - m * power_pow(m - 1, n - 1) % MOD) % MOD + MOD) % MOD;
	return 0;
}
