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
const int MOD = 998244353, inv3 = (MOD + 1) / 3, inv2 = MOD + 1 >> 1;
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

poly Inv(poly f)
{
	int n = deg(f);
	int l = 1;
	while (l <= n) l <<= 1;
	poly a(1, inv(f[0]));
	for (int N = 2; N <= l; N <<= 1)
	{
		const int hf = N / 2;
		poly tf(N, 0), ta = a;
		REP(i, 0, min(n, N - 1)) tf[i] = f[i];

		NTT(ta, N, 1);
		NTT(tf, N, 1);
		REP(i, 0, N - 1) tf[i] = 1ll * ta[i] * tf[i] % MOD;
		NTT(tf, N, -1);
		(tf[0] += MOD - 1) %= MOD;

		poly tta(hf, 0);
		REP(i, hf, N - 1) tta[i - hf] = tf[i];
		NTT(tta, N, 1);
		REP(i, 0, N - 1) tta[i] = 1ll * tta[i] * ta[i] % MOD;
		NTT(tta, N, -1);

		//		tta = tta * a;
		a.resize(N);
		REP(i, hf, min(n, N - 1)) a[i] = (MOD - tta[i - hf]) % MOD;
	}
	a.resize(n + 1);
	return a;
}
poly Der(poly f)
{
	int n = deg(f);
	REP(i, 0, n - 1)
		f[i] = (i + 1ll) * f[i + 1] % MOD;
	f.resize(n);
	return f;
}
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
			Invs[i] = 1ll * Invs[i - 1] * invs[i] % MOD;
		}
		last = n;
	}
}

namespace run
{
	const int maxn = 1e5 + 10;
	int A[maxn], need;
	poly cdq(int l, int r)
	{
		if (l == r) return poly{MOD - A[l], 1};
		int mid = l + r >> 1;
		return cdq(l, mid) * cdq(mid + 1, r);
	}
	poly work(int a[], int n, int m)
	{
		need = m;
		REP(i, 1, n) A[i] = a[i];
		poly f = cdq(1, n);
		poly up = Der(f), down = f;
		reverse(up.begin(), up.end());
		reverse(down.begin(), down.end());
		if (deg(up) > m)	up.resize(m + 1);
		down.resize(m + 1);
		up = up * Inv(down);up.resize(m + 1);
		return up;
	}
	int n, a[maxn], b[maxn], m, t;
	int main()
	{
		n = read<int>();m = read<int>();
		REP(i, 1, n) a[i] = read<int>();
		REP(i, 1, m) b[i] = read<int>();
		t = read<int>();
		prepare(t);

		poly fa = work(a, n, t);
		poly fb = work(b, m, t);
		const i64 iv = inv(n) * inv(m) % MOD;
		REP(i, 0, deg(fa)) fa[i] = 1ll * fa[i] * Invs[i] % MOD;
		REP(i, 0, deg(fb)) fb[i] = 1ll * fb[i] * Invs[i] % MOD;
		poly f = fa * fb;

		REP(k, 1, t)
		{
			i64 res = f[k];
			/*
			REP(l, 0, k)
			{
				i64 sa = 0, sb = 0;
//				REP(i, 1, n) sa += power_pow(a[i], l);
//				REP(i, 1, m) sb += power_pow(b[i], k - l);
				sa = fa[l];sb = fb[k - l];
				res += (sa % MOD) * (sb % MOD) % MOD * Invs[l] % MOD * Invs[k - l];
			}
			res %= MOD;
			*/
			printf("%lld\n", res * fac[k] % MOD * iv % MOD);
		}
		return 0;
	}
}
int main()
{
#ifdef CraZYali
	file("4705");
#endif
	return run :: main();
}
