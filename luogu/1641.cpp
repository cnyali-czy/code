#define  REP(i, s, e) for(register long long i = s; i <= e ;i++)
#define DREP(i, s, e) for(register long long i = s; i >= e ;i--)

#define DEBUG fprlong longf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const long long maxn = 1000000 + 10, maxm = maxn, MOD = 20100403;

long long power_pow(long long a, long long b)
{
	a %= MOD;
	long long ans = 1, base = a;
	while (b)
	{
		if (b & 1) ans = ans * base % MOD;
		base = base * base % MOD;
		b >>= 1;
	}
	return (ans + MOD) % MOD;
}

inline long long inv(long long x) {return power_pow(x, MOD - 2);}

long long m, n, k;

long long fac(long long x)
{
	register long long ans = 1;
	REP(i, 2, x) ans = (ans * i) % MOD;
	return (ans + MOD) % MOD;
}

long long C(long long A, long long B)
{
	return fac(A) * inv(fac(B) * fac(A - B) % MOD) % MOD;
}

int main()
{
#ifdef CraZYali
	freopen("1641.in", "r", stdin);
	freopen("1641.out", "w", stdout);
#endif
	cin >> n >> m;
	cout << ((C(n + m, m) - C(n + m, n + 1)) % MOD + MOD) % MOD;
	return 0;
}
