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

#include <cstring>
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

i64 power_pow(i64 base, i64 b)
{
	b %= (MOD - 1);
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
inline poly operator * (i64 a, poly b)
{
	for (auto &i : b) i = a * i % MOD;
	return b;
}
void output(poly a, const char Split = ' ', const char End = '\n')
{
	REP(i, 0, (int)a.size() - 1) printf("%d%c", a[i], i == end_i ? End : Split);
}
inline poly operator << (poly f, int len)
{
	int n = deg(f);
	REP(i, 0, n - len) f[i] = f[i + len];
	f.resize(n - len + 1);
	return f;
}
inline poly operator >> (poly f, int len)
{
	int n = deg(f);
	f.resize(f.size() + len);
	DEP(i, n + len, len) f[i] = f[i - len];
	REP(i, 0, len - 1) f[i] = 0;
	return f;
}
inline poly sqr(poly f)
{
	int n = deg(f);
	int len = 1;while (len <= n + n) len <<= 1;
	NTT(f, len, 1);
	REP(i, 0, len - 1) f[i] = 1ll * f[i] * f[i] % MOD;
	NTT(f, len, -1);
	f.resize(n + 1);
	return f;
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
		poly tmp(f.begin(), f.begin() + min(N, n + 1));
		NTT(a, N + N, 1);
		NTT(tmp, N + N, 1);
		REP(i, 0, N + N - 1)
		{
			a[i] = (2 - 1ll * a[i] * tmp[i]) % MOD * a[i] % MOD;
			if (a[i] < 0) a[i] += MOD;
		}
//		REP(i, 0, N + N - 1) a[i] = 1ll * a[i] * (2 + MOD - 1ll * a[i] * tmp[i] % MOD) % MOD;
		NTT(a, N + N, -1);
		a.resize(N);
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
int fac[maxn], invs[maxn], Invs[maxn], last;
void prepare(int n)
{
	if (!last)
	{
		fac[0] = invs[0] = Invs[0] = 1;
		fac[1] = invs[1] = Invs[1] = 1;
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
poly Int(poly f)
{
	int n = deg(f);
	prepare(n + 1);
	f.push_back(0);
	DEP(i, n + 1, 1)
		f[i] = 1ll * invs[i] * f[i - 1] % MOD;
	f[0] = 0;
	return f;
}
poly Ln(poly f)
{
	int n = deg(f);
	poly res = Int(Der(f) * Inv(f));
	res.resize(n + 1);
	return res;
}
poly Exp(poly f)
{
	int n = deg(f);
	int l = 1;
	while (l <= n) l <<= 1;
	poly a(1, 1);
	for (int N = 2; N <= l; N <<= 1)
	{
		poly tmp(f.begin(), f.begin() + min(N, n + 1));
		poly ard = a;
		a.resize(N);
		poly ln = Ln(a);
		NTT(a, N, 1);
		NTT(ln, N, 1);
		NTT(tmp, N, 1);
		REP(i, 0, N - 1) a[i] = a[i] * (1ll + MOD - ln[i] + tmp[i]) % MOD;
		NTT(a, N, -1);
		REP(i, 0, deg(ard)) a[i] = ard[i];
	}
	a.resize(n + 1);
	return a;
}
namespace Less
{
	int II;
	struct num
	{
		int x, y;
		inline num(int x = 0, int y = 0) : x(x), y(y) {}
		inline num operator * (num B) {return num((1ll * x * B.x + 1ll * II * y % MOD * B.y) % MOD, (1ll * x * B.y + 1ll * y * B.x) % MOD);}
		inline num operator *=(num B) {return *this = *this * B;}
	};

	num power_pow(num base, int b)
	{
		num ans(1);
		while (b)
		{
			if (b & 1) ans *= base;
			base *= base;
			b >>= 1;
		}
		return ans;
	}
	int solve(int n)
	{
		int a = MOD - 1;
		while (1)
		{
			II = (1ll * a * a + MOD - n) % MOD;
			if (a && ::power_pow(II, MOD - 1 >> 1) == MOD - 1) break;
			a = rand() % MOD;
		}
		int ans1 = power_pow(num(a, 1), MOD + 1 >> 1).x, ans2 = (MOD - ans1) % MOD;
		return min(ans1, ans2);
	}
}
poly Sqrt(poly f)
{
	int n = deg(f);
	int l = 1;
	while (l <= n) l <<= 1;
	poly a(1, Less :: solve(f[0]));
	for (int N = 2; N <= l; N <<= 1)
	{
		poly tmp(f.begin(), f.begin() + min(N, n + 1));
		a.resize(N);
		tmp = tmp * Inv(a);
		REP(i, N / 2, N - 1) a[i] = 1ll * inv2 * tmp[i] % MOD;
	}
	a.resize(n + 1);
	return a;
}
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
inline poly operator - (poly f, int x) {f[0] = (f[0] + MOD - x) % MOD;return f;}

int cdqLIM, inEXP;
poly f, g, mem[30];
const ui64 LIM = 17e18;
void cdq(int l, int r, int L)
{
	if (l > cdqLIM) return;
	if (r - l + 1 <= 64)
	{
		f[0] = 1;
		REP(i, l, min(cdqLIM, r))
		{
			ui64 res = 0;
			REP(j, l, i - 1)
			{
				res += 1ull * f[j] * g[i - j];
				if (res >= LIM) res %= MOD;
			}
			f[i] = (f[i] + res) % MOD;
			if (inEXP) f[i] = 1ll * f[i] * invs[i] % MOD;
		}
		return;
	}
	if (l == r)
	{
		if (!l) f[l] = 1;
		if (inEXP) f[l] = 1ll * invs[l] * f[l] % MOD;
		return;
	}
	int mid = l + r >> 1;
	cdq(l, mid, L + 1);
	if (mid + 1 > cdqLIM) return;

	int len = 1;
//	while (len <= (r - l + mid - l)) len <<= 1; unnecessary?
	while (len <= r - l) len <<= 1;

	poly a(mid - l + 1), b;
	REP(i, 0, mid - l)	a[i] = f[i + l];

	if (mem[L].size()) b = mem[L];
	else
	{
		b.resize(r - l + 1);
		REP(i, 0, r - l)	b[i] = g[i];
		NTT(b, len, 1);
		mem[L] = b;
	}
	NTT(a, len, 1);
	REP(i, 0, len - 1) a[i] = 1ll * a[i] * b[i] % MOD;
	NTT(a, len, -1, 0);
	const int ilen = inv(len);
	REP(i, mid + 1, min(cdqLIM, r)) f[i] = (f[i] + NTTtmp[i - l] % MOD * ilen) % MOD;

	cdq(mid + 1, r, L + 1);
}
poly Exp_log2(const poly &f)
{
	int n = deg(f);
	int len = 1;
	while (len <= n) len <<= 1;
	prepare(len);
	::f.clear(); ::f.resize(len);
	::g.clear(); ::g.resize(len);
	REP(i, 1, n) ::g[i] = 1ll * i * f[i] % MOD;
	cdqLIM = n;
	REP(i, 0, 29) mem[i].clear();
	inEXP = 1;cdq(0, len - 1, 0);inEXP = 0;
	::f.resize(n + 1);
	return ::f;
}

namespace FASTER_CDQ
{
	int main4721()
	{
		int n = read<int>() - 1;
		int N = 1;while (N <= n) N <<= 1;
		g.resize(N);f.resize(N);
		REP(i, 1, n) g[i] = read<int>();
		cdqLIM = n;
		REP(i, 0, 29) mem[i].clear();
		cdq(0, N - 1, 0);
		f.resize(n + 1);
		output(f);
		return 0;
	}
}

pair <poly, poly> DIV(poly f, poly g)
{
	int n = deg(f), m = deg(g);
	if (n < m) return make_pair(poly(1, 0), f);
	poly rf = f;reverse(rf.begin(), rf.end());
	poly rg = g;reverse(rg.begin(), rg.end());
	rf.resize(n - m + 1);rg.resize(n - m + 1);
	poly d = rf * Inv(rg);
	d.resize(n - m + 1);
	reverse(d.begin(), d.end());
	poly r = f - g * d;
	r.resize(m);
	return make_pair(d, r);
}

poly operator / (poly f, poly g) {return DIV(f, g).first;}
poly operator % (poly f, poly g) {return DIV(f, g).second;}
int calc(const poly &f, i64 x)
{
	int ans = 0;
	DEP(i, deg(f), 0)
		ans = (ans * x + f[i]) % MOD;
	return ans;
}

namespace ddqz
{
	const int MAXN = 64000 + 10;
	poly MEM[maxn << 2];
#define ls p << 1
#define rs p << 1 | 1
#define lson ls, l, mid
#define rson rs, mid + 1, r
#define mid (l + r >> 1)
	int ask[MAXN], n, m;
	const int B = 64;
	poly cdq(int l, int r)
	{
		if (l == r)
		{
			poly f(2);
			f[0] = MOD - ask[l];
			f[1] = 1;
			return f;
		}
		return cdq(l, mid) * cdq(mid + 1, r);
	}
	void init(int p, int l, int r)
	{
		MEM[p].clear();
		if (r - l + 1 <= B) {MEM[p] = cdq(l, r);return;}
		init(lson);init(rson);
		if (p > 1) MEM[p] = MEM[ls] * MEM[rs];
	}
	poly ans;
	void work(int p, int l, int r, poly f)
	{
		if (r - l + 1 <= B)
		{
			REP(i, l, r) ans[i - 1] = calc(f, ask[i]);
			return;
		}
		work(lson, f % MEM[ls]);
		work(rson, f % MEM[rs]);
	}
	poly solve(poly f, poly g) // unique g
	{
		n = deg(f);m = g.size();
		REP(i, 1, m) ask[i] = g[i - 1];
		init(1, 1, m);
		ans.resize(m);
		work(1, 1, m, f);
		return ans;
	}
}

namespace linear_recurrence
{
	int calc(poly g, poly ard, int n)
	{
		int m = deg(g);
		if (n < m) return ard[n];
		g[0] = 1;
		REP(i, 1, m) g[i] = MOD - g[i];
		reverse(g.begin(), g.end());
		poly base(2, 0), ans(1, 1);
		base[1] = 1;
	
		while (n)
		{
			if (n & 1) ans = ans * base % g;
			base = base * base % g;
			n >>= 1;
		}
		int Ans = 0;
		REP(i, 0, m - 1) Ans = (Ans + 1ll * ans[i] * ard[i]) % MOD;
		return Ans;
	}
}
poly fhn(poly f)
{
	int n = deg(f);
	prepare(n);
	const int block = sqrt(n);
	static poly p1[1 << 10 | 10], p2[1 << 10 | 10];
	REP(i, 0, n - 1) f[i] = f[i + 1];f.resize(n);
	f = Inv(f);
	p1[0] = poly(1, 1);REP(i, 1, block)
	{
		p1[i] = p1[i - 1] * f;
		p1[i].resize(n);
	}p1[0].resize(n);
	p2[0] = poly(1, 1);REP(i, 1, n / block + 1)
	{
		p2[i] = p2[i - 1] * p1[block];
		p2[i].resize(n);
	}p2[0].resize(n);
	poly g(n + 1, 0);
	REP(i, 1, n)
	{
		i64 res = 0;
		int id1 = i % block, id2 = i / block;
		REP(j, 0, i - 1) (res += 1ll * p1[id1][j] * p2[id2][i - 1 - j]) %= MOD;
		g[i] = res * invs[i] % MOD;
	}
	return g;
}
inline poly operator ^ (poly f, int x)
{
	f = Ln(f);
	REP(i, 0, (int)f.size() - 1) f[i] = 1ll * f[i] * x % MOD;
	return Exp_log2(f);
}

namespace real
{
	const int maxn = 114514 + 10;

	inline i64 C(int n, int m) { return n < m || m < 0 ? 0 : 1ll * fac[n] * Invs[m] % MOD * Invs[n - m] % MOD;}

	i64 n, k, a[maxn], R;

	//int f[maxn][128];
	int dp[105][105][105], X[maxn];

	inline i64 calc0(int n, i64 len)
	{
		if (n < 0) return 0;
		static bool calced[maxn];
		static int mem[maxn];
		i64 res = 0;
		if (calced[n]) res = mem[n];
		else
		{
			calced[n] = 1;
			REP(i, 0, n / 2) res += C(n, i + i);
			res %= MOD;	mem[n] = res;
		}
		return power_pow(res, len);
	}
	inline i64 calc1(int n)
	{
		static bool calced[maxn];
		static int mem[maxn];
		i64 res = 0;
		if (calced[n]) res = mem[n];
		else
		{
			calced[n] = 1;
			REP(i, 0, n / 2) res += C(n, i << 1 | 1);
			res %= MOD;mem[n] = res;
		}
		return res;
	}

	int S[maxn], T[maxn];
#define fi first
#define se second
	pair <poly, poly> cdq(int l, int r)
//		 <up, down>
	{
		if (l == r)
		{
			poly res(2);
			res[0] = T[l];
			res[1] = MOD - 1ll * S[l] * T[l] % MOD;
			return make_pair(poly(1, 1), res);
		}
		auto LHS = cdq(l, mid), RHS = cdq(mid + 1, r);
		return make_pair(LHS.fi * RHS.se + RHS.fi * LHS.se, LHS.se * RHS.se);
	}

	int pre[maxn], here[maxn];
	poly work(int zz[])
	{
		REP(i, 1, k) S[i] = 1ll * zz[i] * zz[i] % MOD;
		auto res = cdq(1, k);
		poly up = res.fi, down = res.se;
		down.resize(n / 2 + 1);
		down = Inv(down) * up;
		down.resize(n / 2 + 1);
		return down;
	}
	void getf()
	{
		REP(i, 1, k) pre[i] = (pre[i - 1] + (here[i] = power_pow(2, a[i]))) % MOD;
		R = pre[k];
		X[0] = 1;
		static int pzk1[maxn], pzk2[maxn], pzk3[maxn];
		REP(i, 1, k) pzk1[i] = (here[i] + pre[i - 1]) % MOD;
		REP(i, 1, k) pzk2[i] = (here[i] + MOD - pre[i - 1]) % MOD;
		REP(i, 1, k) pzk3[i] = pre[i - 1];
		REP(i, 1, k) T[i] = here[i];

		poly tx = inv2 * (work(pzk1) + work(pzk2) - 2 * work(pzk3));
		REP(i, 1, n / 2) X[i << 1] = tx[i];
		/*

		REP(i, 1, n / 2)
		{
			i64 res = 0;
			REP(j, 1, k)
			{
				i64 s = pre[j - 1], t = here[j];
				i64 cur = power_pow(t + s, i + i) + power_pow(t + MOD - s, i + i) + 2 * (MOD - power_pow(s, i + i));
				(res += cur * inv(2 * t)) %= MOD;
			}
			X[i << 1] = res;
			cerr << res << ' ' << tx [i] << endl;
		}
		*/
		REP(i, 1, n) if (i & 1)
		{
			i64 res = 0, s = pre[k - 1], t = here[k];
			i64 cur = power_pow(t + s, i) + power_pow(t + MOD - s, i);
			(res += cur * inv(2 * t)) %= MOD;
			X[i] = res;
		}
	}
	int A[maxn], m, cnt[maxn];
	i64 ans;

	int bin[maxn];
	signed main()
	{
		cin >> n >> k;
		prepare(n);
		REP(i, 1, k) scanf("%lld", a + i);
		getf();
		bin[0] = 1;REP(i, 1, n) bin[i] = 1ll * (MOD - R) * bin[i - 1] % MOD;

		poly F(n + 1, 0), G(n + 1, 0);
		REP(i, 1, n) if (i & 1) F[i] = invs[i];else G[i] = 1ll * (MOD - R) * invs[i] % MOD;
		G = Exp_log2(G);

		poly ni(n + 1, 0), H(n + 1, 0);
		for (i64 b = 1, i = 0; i <= n; i++, (b *= 2) %= MOD)
			ni[i] = b * Invs[i] % MOD;
		ni[0]++;
		ni = poly(1, 1) - 2 * Inv(ni);

		H = Exp_log2(1ll * R * inv2 % MOD * Ln((poly(1, 1) - sqr(ni))));
		H.resize(n + 1);poly dH = Der(H);

		poly qaq = ni << 1, gg = qaq ^ (MOD - n);
		poly up1 = dH * gg, up2 = ((dH >> 1) - H) * gg;
		const i64 invn = inv(n);
		poly SKY(n + 1, 0);
		REP(i, 0, n - 1)
			SKY[i] = (i + 1ll) * up1[n - 1 - i] % MOD * invn % MOD;
		REP(i, 0, n - 1)
			SKY[i + 1] = (SKY[i + 1] - (i + 1ll) * up2[n - 1 - i] % MOD * invn) % MOD;
		REP(i, 0, n) if (SKY[i] < 0) SKY[i] += MOD;

		REP(i, 0, n)
			(ans += 1ll * X[i] * SKY[i] % MOD * Invs[i]) %= MOD;
		cout << ans % MOD << endl;

		return 0;
	}
}
signed main()
{
#ifdef CraZYali
	file("C");
#endif
	return real :: main();
}