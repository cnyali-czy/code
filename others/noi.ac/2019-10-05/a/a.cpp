#define REP(i, s, e) for (int i(s); i <= e; i++)

#include <iostream>
using namespace std;
const int MOD = 1e9 + 7;

int power_pow(long long base, int b)
{
	long long ans(1);
	while (b)
	{
		if (b & 1) (ans *= base) %= MOD;
		(base *= base) %= MOD;
		b >>= 1;
	}
	return (ans + MOD) % MOD;
}
#define inv(x) power_pow(x, MOD - 2)

int main()
{
	int n, m;
	long long res(1);
	cin >> n >> m;
	REP(i, 1, n) (res *= inv(i)) %= MOD;
	REP(i, 1, m) (res *= inv(i)) %= MOD;
	REP(i, 1, n + m) (res *= i) %= MOD;
	long long ans = 1ll * power_pow(2, n + m) * inv(res) % MOD;
	cout << ans << endl;
	return 0;
}
