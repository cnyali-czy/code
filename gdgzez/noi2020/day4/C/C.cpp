#define REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;
const int maxn = 2000 + 10, MOD = 1e9 + 7;
#define i64 long long
inline void inc(int &x, int y) {x += y; if (x >= MOD) x -= MOD;}
template <typename T> T read()
{
	T ans(0), flag(1);
	char c(getchar());
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

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

int m, n, k;

int fac[maxn << 1], Inv[maxn << 1];
struct __init__
{
	__init__(const int N = 4000)
	{
		fac[0] = fac[1] = Inv[0] = Inv[1] = 1;
		REP(i, 2, N) fac[i] = 1ll * fac[i - 1] * i % MOD, Inv[i] = (MOD - MOD / i) * 1ll * Inv[MOD % i] % MOD;
		REP(i, 2, N) Inv[i] = 1ll * Inv[i - 1] * Inv[i] % MOD;
	}
}__INIT__;
inline int C(int n, int m) {return n < m || m < 0 ? 0 : 1ll * fac[n] * Inv[m] % MOD * Inv[n - m] % MOD;}
inline int F(int n, int m) {return C(n + m, n);}
int g[maxn], bin[maxn], s[maxn];

int solve(int n, int m)
{
	int ans = 0;
	g[0] = 1;
	REP(i, 1, n)
	{
		g[i] = 0;
		REP(j, 1, m) inc(g[i], 1ll * F(i - 1, j - 1) * F(i, m - j) % MOD);
	}
	bin[0] = 1;
	REP(i, 1, n) bin[i] = (m + 1ll) * bin[i - 1] % MOD;
	REP(i, 0, n) REP(j, 0, n - i - 1)
		inc(ans, 1ll * g[i] * g[j] % MOD * bin[n - i  -j] % MOD);
	REP(i, 1, n - 1)
	{
		REP(j, 1, m) s[j] = (s[j - 1] + 1ll * F(n - i, j - 1) * F(n - i - 1, m - j)) % MOD;
		REP(j, 3, m) inc(ans, 2ll * F(i - 1, j - 1) * F(i, m - j) % MOD * s[j - 2] % MOD);
	}
	return ans;
}

int main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();m = read<int>();
	long long ans = solve(n, m) + solve(m, n);
	REP(i, 1, n - 1) REP(j, 1, m - 1) ans += 2ll * F(i - 1, j) * F(i, m - j - 1) % MOD * F(n - i, j - 1) % MOD * F(n - i - 1, m - j) % MOD;
	cout << ans % MOD << endl;
	return 0;
}
