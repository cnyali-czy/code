#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)

#define chkmin(a, b) ((a = min(a, (b))) == (b))
#define chkmax(a, b) ((a = max(a, (b))) == (b))

#include <iostream>
#include <cstdio>
#define int long long
using namespace std;
const int maxn = 4e4 + 5;
int n, g, P[] = {999911659, 2, 3, 4679, 35617};

inline int power_pow(int base, int b, int MOD)
{
	if (!base) return 0;
	int ans = 1;
	while (b)
	{
		if (b & 1) ans = ans * base % MOD;
		base = base * base % MOD;
		b >>= 1;
	}
	return (ans + MOD) % MOD;
}
#define inv(x, MOD) power_pow(x, MOD - 2, MOD)
int Inv[maxn][5], fac[maxn][5], facInv[maxn][5];
inline void init()
{
	REP(j, 1, 4)
	{
		int MOD = P[j];
		Inv[0][j] = fac[0][j] = facInv[0][j] = 1;
		REP(i, 1, MOD-1) fac[i][j] =  fac[i-1][j] * i % MOD;
		facInv[MOD-1][j] = inv(fac[MOD-1][j], MOD);
		DREP(i, MOD - 2, 1) facInv[i][j] = facInv[i+1][j] * (i + 1) % MOD;
		Inv[MOD-1][j] = inv(MOD-1, MOD);
		DREP(i, MOD - 2, 1) Inv[i][j] = facInv[i][j] * fac[i-1][j] % MOD;
	}
}
inline int C(int n, int m, int j) {return m < 0 || m > n ? 0 : fac[n][j] * facInv[m][j] % P[j] * facInv[n-m][j] % P[j];}
inline int lucas(int n, int m, int j)
{
	int MOD = P[0] - 1, ans = 1, p = P[j];
	for (; m; m /= p, n /= p) ans = ans * C(n % p, m % p, j) % p;
	return ans * (MOD / p) % MOD * inv(MOD / p, p) % MOD;
}
inline int lucas(int n, int m)
{
	int res(0), MOD = P[0] - 1;
	REP(i, 1, 4) res = (res + lucas(n, m, i)) % MOD;
	return res;
}
int solve()
{
	int res(0);
	for (int i = 1; i * i <= n; i++)
		if (n % i == 0)
		{
			res = (res + lucas(n, i)) % (P[0] - 1);
			if (i * i != n) res = (res + lucas(n, n / i)) % (P[0] - 1);
		}
	return res;
}
signed main()
{
#ifdef CraZYali
	freopen("1951.in", "r", stdin);
	freopen("1951.out", "w", stdout);
#endif
	cin >> n >> g;
	init();
	cout << power_pow(g % P[0], solve(), P[0]) << endl;
	return 0;
}
