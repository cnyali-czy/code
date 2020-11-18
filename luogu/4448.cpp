/*
	Problem:	4448.cpp
	Time:		2020-11-18 14:44
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <iostream>
#include <cstdio>
#include <cmath>
#define poly vector <int>
#define i64 long long
#define ui64 unsigned i64

using namespace std;
const int maxn = 300 + 5, MOD = 1e9 + 7;

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
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, a[maxn];

bool judge(i64 x, i64 y)
{
	x *= y;y = sqrt(x);
	return y * y == x;
}

int fac[maxn], invs[maxn], Inv[maxn];
void init()
{
	fac[0] = invs[0] = Inv[0] = 1;
	fac[1] = invs[1] = Inv[1] = 1;
	REP(i, 2, n)
	{
		fac[i] = 1ll * i * fac[i - 1] % MOD;
		invs[i] = 1ll * (MOD - MOD / i) * invs[MOD % i] % MOD;
		Inv[i] = 1ll * invs[i] * Inv[i - 1] % MOD;
	}
}
inline i64 C(int n, int m) {return n < m || m < 0 ? 0 : 1ll * fac[n] * Inv[m] % MOD * Inv[n - m] % MOD;}
int f[maxn];

const ui64 LIM = 17e18;
inline int deg(const poly &f) {return f.size() - 1;}
poly operator * (poly f, poly g)
{
	static ui64 res[maxn << 1];
	int n = deg(f), m = deg(g);
	REP(i, 0, n) if (f[i]) REP(j, 0, m) if (g[j])
	{
		res[i + j] += 1ll * f[i] * g[j];
		if (res[i + j] >= LIM) res[i + j] %= MOD;
	}
	f.resize(n + m + 1);
	REP(i, 0, n + m)
	{
		if (res[i] >= MOD) res[i] %= MOD;
		f[i] = res[i];res[i] = 0;
	}
	return f;
}

int fa[maxn], siz[maxn];
int find(int x) {return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);}
void uni(int x, int y)
{
	x = find(x);y = find(y);
	if (x == y) return;
	fa[x] = y;siz[y] += siz[x];
}

int main()
{
#ifdef CraZYali
	file("4448");
#endif
	n = read<int>();init();
	REP(i, 1, n) a[i] = read<int>();
	REP(i, 1, n) siz[fa[i] = i] = 1;
	REP(i, 1, n) REP(j, i + 1, n) if (judge(a[i], a[j])) uni(i, j);
	poly g(1, 1);
	REP(i, 1, n) if (fa[i] == i)
	{
		int c = siz[i];
		poly h(c + 1, 0);
		REP(j, 1, c)
			h[j] = fac[c] * C(c - 1, j - 1) % MOD * Inv[j] % MOD;
		g = g * h;
	}
	REP(i, 1, n) g[i] = 1ll * g[i] * fac[i] % MOD * fac[n - i] % MOD * fac[i] % MOD;
	i64 ans = 0;
	REP(i, 0, n)
	{
		i64 res = g[i] * C(n, i) % MOD;
		if ((n - i) & 1) res = MOD - res;
		ans += res;
	}
	ans %= MOD;
	(ans *= Inv[n]) %= MOD;
	cout << ans << endl;
	return 0;
}
