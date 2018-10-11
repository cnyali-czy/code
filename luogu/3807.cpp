#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

#define int long long
using namespace std;
const int maxp = 100000 + 10;

template <typename T> T read()
{
	T ans(0), p(1);
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}

int n, m, MOD;
int power_pow(int a, int b)
{
	int base = a % MOD, ans = 1;
	while (b)
	{
		if (b & 1) ans = ans * base % MOD;
		base = base * base % MOD;
		b >>= 1;
	}
	return ans % MOD;
}

int inv(int x) {return power_pow(x, MOD - 2);}

int fac[maxp], Inv[maxp];

void init(int n)
{
	fac[0] = 1;
	Inv[0] = 1;
	REP(i, 1, n)
		Inv[i] = inv(fac[i] = fac[i-1] * i % MOD);
}

int C(int n, int m)
{
	return m <= n ? fac[n] * Inv[m] % MOD * Inv[n - m] % MOD : 0;
}

int lucas(int n, int m)
{
	return m ? C(n % MOD, m % MOD) * lucas(n / MOD, m / MOD) % MOD : 1;
}

signed main()
{
#ifdef CraZYali
	freopen("3807.in", "r", stdin);
	freopen("3807.out", "w", stdout);
#endif

	register int T = read<int>();
	while ( T --> 0)
	{
		n = read<int>(), m = read<int>(), MOD = read<int>();
		init(MOD);

		printf("%lld\n", (lucas(n + m, m) + MOD) % MOD);
	}

	return 0;
}
