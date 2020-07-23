/*
	Problem:	B.cpp
	Time:		2020-07-23 19:35
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <iostream>
#include <cstdio>
#define i64 long long
using namespace std;
const int maxn = 5e5 + 10, MOD = 1e9 + 7;

i64 power_pow(i64 base, i64 b)
{
	i64 ans = 1;
	while (b)
	{
		if (b & 1) (ans *= base) %= MOD;
		(base *= base) %= MOD;
		b >>= 1;
	}
	return ans;
}
#define inv(x) power_pow(x, MOD - 2)

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
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

i64 n;
int k, x, F[maxn];

int fac[maxn], Inv[maxn];
inline i64 C(int n, int m) {return 1ll * fac[n] * Inv[m] % MOD * Inv[n - m] % MOD;}
inline i64 sgn(int i) {return (i & 1) ? MOD - 1 : 1;}

struct func
{
	int a, b;//a + bx
	func(int a = 0, int b = 0) : a(a), b(b) {}
	inline func operator + (func B)	{return func((a + B.a) % MOD, (b + B.b) % MOD);}
	inline func operator * (i64 x)	{return func(a * x % MOD, b * x % MOD);}
	inline i64 solve(int y) //a + bx = y, x = (y - a) / b
	{
		return inv(b) * (y + MOD - a) % MOD;
	}
}G[maxn];
i64 g[maxn], N;

int orzjjs(i64 n)
{
	i64 nn = n;
	n %= MOD;
	i64 qaq = 1;
	REP(j, 0, k) qaq = qaq * (j - n) % MOD;
	
	i64 gn = 0;
	REP(i, 0, k)
	{
		i64 tmp = sgn(i) * Inv[i] % MOD * Inv[k - i] % MOD * qaq % MOD * inv(i - n) % MOD;
		gn += tmp % MOD * g[i] % MOD;
	}
	gn = (gn % MOD + MOD) % MOD;
	return (power_pow(x, nn % (MOD - 1)) * gn + MOD - g[0]) % MOD;
}

int main()
{
#ifdef CraZYali
	file("B");
#endif
	cin >> n >> k >> x;
	N = k + 1;
	fac[0] = 1;
	REP(i, 1, N) fac[i] = 1ll * i * fac[i - 1] % MOD;
	Inv[N] = inv(fac[N]);
	DEP(i, N - 1, 0) Inv[i] = (i + 1ll) * Inv[i + 1] % MOD;
	REP(i, 0, k) F[i] = read<int>();
	if (n <= k)
	{
		i64 xi = 1, ans = 0;
		REP(i, 0, n)
		{
			ans += xi * F[i] % MOD;
			(xi *= x) %= MOD;
		}
		cout << ans % MOD << endl;
		return 0;
	}
	G[0] = func(0, 1);
	i64 Invx = inv(x);
	REP(i, 0, N - 1)
		G[i + 1] = (G[i] + F[i]) * Invx;
	func res(0, 0);
	REP(i, 0, N) res = res + (G[i] * sgn(N - i)) * C(N, i);
	g[0] = res.solve(0);
	REP(i, 0, N - 1) g[i + 1] = (g[i] + F[i]) * Invx % MOD;
	cout << orzjjs(n + 1) << endl;
	return 0;
}
