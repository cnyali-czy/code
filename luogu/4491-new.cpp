/*
	Problem:	qaq.cpp
	Time:		2020-06-16 20:53
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cmath>
#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;
const int MOD = 1004535809, inv3 = (MOD + 1) / 3, inv2 = MOD + 1 >> 1;
#define poly vector <int> 
#define i64 long long
#define u64 unsigned i64

i64 power_pow(i64 base, int b)
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

const int maxn = 1 << 18;
u64 NTTtmp[maxn];
int R[maxn];
void NTT(poly &a, int n, int flag, bool NEED = 1)
{
	if (a.size() ^ n) a.resize(n);
	if (flag < 0) reverse(a.begin() + 1, a.end());
	static int *w[30], pool[maxn << 1 | 10];
	static bool vis[30];
	w[0] = pool;
	REP(i, 0, n - 1)
	{
		R[i] = (R[i >> 1] >> 1) | ((i & 1) ? (n >> 1) : 0);
		if (i < R[i]) swap(a[i], a[R[i]]);
	}
	REP(i, 0, n - 1) NTTtmp[i] = a[i];
	for (int i = 1, ccc = 0; i < n; i <<= 1, ccc++)
	{
		if (!vis[ccc])
		{
			vis[ccc] = 1;
			const i64 wn = power_pow(3, (MOD - 1) >> ccc + 1);
			if (i < maxn) w[ccc + 1] = w[ccc] + i;
			w[ccc][0] = 1;
			REP(j, 1, i - 1) w[ccc][j] = w[ccc][j - 1] * wn % MOD;
		}
		for (int k = 0; k < n; k += i + i)
			for (int l = 0; l < i; l++)
			{
				u64 x(NTTtmp[k + l]), y(NTTtmp[k + l + i] * w[ccc][l] % MOD);
				NTTtmp[k + l] = x + y;
				NTTtmp[k + l + i] = MOD + x - y;
			}
	}
	if (!NEED) return;
	REP(i, 0, n - 1) a[i] = NTTtmp[i] % MOD;
	if (flag < 0)
	{
		const int invn = inv(n);
		REP(i, 0, n - 1) a[i] = 1ll * a[i] * invn % MOD;
	}
}
inline int deg(const poly &a) {return (int)a.size() - 1;}
inline poly operator * (poly a, poly b)
{
	int l = 1, n = deg(a), m = deg(b);
	while (l <= n + m) l <<= 1;
	NTT(a, l, 1);NTT(b, l, 1);
	REP(i, 0, l - 1) a[i] = 1ll * a[i] * b[i] % MOD;
	NTT(a, l, -1);
	a.resize(n + m + 1);
	return a;
}

void output(poly a, const char Split = ' ', const char End = '\n')
{
	REP(i, 0, (int)a.size() - 1) printf("%d%c", a[i], i == end_i ? End : Split);
}
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

int invs[maxn], fac[maxn], Invs[maxn], last;
void prepare(int n)
{
	if (!last)
	{
		invs[0] = fac[0] = Invs[0] = 1;
		invs[1] = fac[1] = Invs[1] = 1;
		last = 1;
	}
	if (last < n)
	{
		REP(i, last + 1, n)
		{
			fac[i] = 1ll * i * fac[i - 1] % MOD;
			invs[i] = 1ll * (MOD - MOD / i) * invs[MOD % i] % MOD;
			Invs[i] = 1ll * invs[i] * Invs[i - 1] % MOD;
		}
		last = n;
	}
}

namespace run
{
	inline i64 C(int n, int m) {return n < m || m < 0 ? 0 : 1ll * fac[n] * Invs[m] % MOD * Invs[n - m] % MOD;}
	inline i64 single_fac(int n)
	{
		i64 res = 1;
		REP(i, 2, n) (res *= i) %= MOD;
		return res;
	}

	int n, m, s;
	int main()
	{
		cin >> n >> m >> s;
		if (s > m)
		{
			cout << read<i64>() * power_pow(m, n) % MOD << endl;
			return 0;
		}
		prepare(m);

		poly f(m + 1, 0);
		i64 is = 1, fn = single_fac(n), in = inv(fn);
		REP(i, 0, min(n / s, m))
		{
			f[i] = C(m, i) * is % MOD * power_pow(m - i, n - s * i) % MOD * in % MOD;
			(is *= Invs[s]) %= MOD;
			DEP(j, n - i * s, n - (i + 1) * s + 1) (in *= j) %= MOD;
		}

		/*
		REP(i, 0, m) f[i] = 1ll * f[i] * fn % MOD;
		poly g(m + 1, 0), e(m + 1, 0);
		REP(i, 0, m) g[m - i] = 1ll * f[i] * fac[i] % MOD;
		REP(i, 0, m) e[i] = (i & 1 ? MOD - Invs[i] : Invs[i]);
		g = g * e;
		REP(i, 0, m) f[i] = 1ll * g[m - i] * Invs[i] % MOD;
		*/
		REP(i, 0, m) f[i] = fn * f[i] % MOD * fac[i] % MOD;
		reverse(f.begin(), f.end());
		poly e(m + 1, 0);
		REP(i, 0, m) e[i] = (i & 1 ? MOD - Invs[i] : Invs[i]);
		f = f * e;

		i64 ans = 0;
		REP(i, 0, m) (ans += read<i64>() * f[m - i] % MOD * Invs[i]) %= MOD;
		cout << ans << endl;
		
		return 0;
	}
}

int main()
{
#ifdef CraZYali
	file("4491-new");
#endif
	return run :: main();
}
