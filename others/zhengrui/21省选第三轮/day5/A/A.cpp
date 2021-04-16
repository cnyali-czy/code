#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)

#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int MOD = 1e9 + 7;

i64 power_pow(i64 base, i64 b)
{
	i64 ans = 1;
	if (base >= MOD) base %= MOD;
	while (b)
	{
		if (b & 1) (ans *= base) %= MOD;
		if (b >>= 1) (base *= base) %= MOD;
	}
	return ans;
}
#define inv(x) power_pow(x, MOD - 2)

i64 n, k;

i64 f(int x)
{
	i64 ans = 1;
	for (int i = 2; i * i <= x; i++) if (x % i == 0)
	{
		int l = 0;
		while (x % i == 0) x /= i, l++;
		(ans *= (power_pow(l + 1, k) + MOD - power_pow(l, k))) %= MOD;
	}
	if (x > 1) (ans *= power_pow(2, k) - 1) %= MOD;
	return ans;
}

int main()
{
#ifdef CraZYali
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	cin >> n >> k;
	i64 ans = 0;
	REP(i, 1, n) (ans += n / i * f(i)) %= MOD;
	cout << ans << '\n';
	return 0;
}
