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
#define ui64 unsigned i64

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

const int maxn = 1 << 21;
ui64 NTTtmp[maxn];
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
	bool fff = (flag > 0);
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
				ui64 x(NTTtmp[k + l]), y(NTTtmp[k + l + i] * w[ccc][l] % MOD);
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

inline poly operator + (poly f, poly g)
{
	if (f.size() < g.size()) f.resize(g.size());
	REP(i, 0, (int)g.size() - 1) (f[i] += g[i]) %= MOD;
	return f;
}
inline poly operator - (poly f, poly g)
{
	if (f.size() < g.size()) f.resize(g.size());
	REP(i, 0, (int)g.size() - 1) f[i] = (f[i] + MOD - g[i]) % MOD;
	return f;
}
inline poly operator + (poly f, int x) {(f[0] += x) %= MOD;return f;}
inline poly operator + (int x, poly f) {(f[0] += x) %= MOD;return f;}

poly Div(poly f, const poly &g) // return f / g
{
	int n(deg(f)), m(deg(g));
	const i64 Invs = inv(g[m]);
	poly res(n - m + 1, 0);
	DEP(i, n, m) if (f[i])
	{
		const i64 qaq = Invs * f[i] % MOD;
		res[i - m] = qaq;
		REP(j, 0, m)
			f[j - m + i] = (f[j - m + i] - g[j] * qaq) % MOD;
	}
	for (auto &i : res) if (i < 0) i += MOD;
	return res;
}

namespace real
{
	int n, r, m;
	inline int a(int i) {return i + (i >= r);}
	poly f(int i)
	{
		poly res(2);
		res[0] = MOD + 1 - a(i);
		res[1] = MOD + a(i) - 1 - n;
		return res;
	}
	poly g(int i)
	{
		poly res(2);
		res[0] = a(i);
		res[1] = MOD + n - a(i);
		return res;
	}
	struct Node
	{
		poly mf, mg, r;
		Node() {}
		Node(int i)
		{
			mf = f(i);
			mg = g(i);
			r = poly(2, 0);r[1] = n - i & 1 ? 1 : MOD - 1;
		}
	};
	Node cdq(int l, int r)
	{
		if (l == r) return Node(l);
		int mid = l + r >> 1;
		auto LHS = cdq(l, mid), RHS = cdq(mid + 1, r);
		int len = 1;while (len <= r - l + 1) len <<= 1;
		NTT(LHS.mf, len, 1);NTT(LHS.mg, len, 1);NTT(LHS.r, len, 1);
		NTT(RHS.mf, len, 1);NTT(RHS.mg, len, 1);NTT(RHS.r, len, 1);
		REP(i, 0, len) LHS.r[i] = (1ll * LHS.r[i] * RHS.mg[i] + 1ll * RHS.r[i] * LHS.mf[i]) % MOD;
		REP(i, 0, len - 1) LHS.mf[i] = 1ll * LHS.mf[i] * RHS.mf[i] % MOD;
		REP(i, 0, len - 1) LHS.mg[i] = 1ll * LHS.mg[i] * RHS.mg[i] % MOD;
#define res LHS
		NTT(res.mf, len, -1);NTT(res.mg, len, -1);NTT(res.r, len, -1);
		res.mf.resize(r - l + 2);res.mg.resize(r - l + 2);res.r.resize(r - l + 2);
		return res;
	}
	int main()
	{
		cin >> n >> r >> m;
		poly ans(1, 0);
		poly t(2, 0);t[0] = MOD + 1 - a(n - 1);t[1] = MOD - (n - a(n - 1));

		i64 Ans = 0;
		if (n > 2)
		{
			auto pzk = cdq(1, n - 1);
			poly tf;
			t = t * (tf = Div(pzk.mf, f(n - 1)));
			Ans += pzk.r[m];
//			ans = ans + pzk.r;
//			tf.emplace_back(0);DEP(i, deg(tf), 1) tf[i] = tf[i - 1];tf[0] = 0;
//			ans = ans - tf;
			Ans -= tf[m - 1];			
		}
		Ans += t[m];
//		ans = ans + t;
//		Ans = ans[m];
		if (n % 2 == 0) Ans = MOD - Ans;
		cout << (Ans % MOD + MOD) % MOD << endl;
		return 0;
	}
}

int main()
{
#ifdef CraZYali
	file("B");
#endif
	return real :: main();
}
