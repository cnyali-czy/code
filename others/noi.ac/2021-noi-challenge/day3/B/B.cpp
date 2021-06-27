#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <ctime>
#include <iostream>
#include <cstdio>
#define int long long

using namespace std;
const int MOD = 19260817, maxn = 1e7 + 1000;

int nn;
	template <typename T>
inline T read()
{
	T ans = 0, flag = 1;
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = (ans * 10ll + (c - 48)) % MOD;
		nn = (nn * 10ll + (c - 48)) % (MOD - 1);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n;

int power_pow(int base, int b)
{
	base %= MOD;
	int ans = 1;
	while (b)
	{
		if (b & 1) (ans *= base) %= MOD;
		if (b >>= 1) (base *= base) %= MOD;
	}
	return ans;
}
#define inv(x) power_pow(x, MOD - 2)
signed main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read<int>();
	int ans = 0;
	ans = (-10 + power_pow(10, nn + 1) - 9 * n) % MOD * (2 + n) % MOD * (3 + n) % MOD * (4 + n) % MOD * (5 + n) % MOD * (6 + n) % MOD * (7 + n) % MOD * (8 + n) % MOD * (9 + n) % MOD * inv(3265920) % MOD;
	cout << (ans + MOD) % MOD << endl;
	return 0;
}
