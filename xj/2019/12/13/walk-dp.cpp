#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <map>
#include <iostream>
#include <cstdio>
#define int long long
using namespace std;
int base, MOD;
int power_pow(int b, int base = ::base)
{
	int ans(1);
	while (b)
	{
		if (b & 1) (ans *= base) %= MOD;
		(base *= base) %= MOD;
		b >>= 1;
	}
	return ans;
}
int n, m;
int ans[5050][5050], bin[5050];
signed main()
{
#ifdef CraZYali
	freopen("walk.in", "r", stdin);
	freopen("walk.out", "w", stdout);
#endif
	int T;
	cin >> T >> base >> MOD;
	bin[0] = 1;
	REP(i, 1, 5000) bin[i] = bin[i-1] * base % MOD;
	REP(i, 0, 5000) ans[0][i] = ans[i][0] = 1;
	REP(i, 1, 5000)
		REP(j, 1, 5000)
		ans[i][j] = (ans[i][j-1] * bin[i] % MOD + ans[i-1][j]) % MOD;
	while (T--)
	{
		scanf("%lld%lld", &n, &m);
		printf("%lld\n", ans[n][m]);
	}
	return 0;
}
