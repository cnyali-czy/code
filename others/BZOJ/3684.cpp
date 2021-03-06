#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;
const int MOD = 950009857, inv3 = (MOD + 1) / 3, inv2 = MOD + 1 >> 1;
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
			const i64 wn = power_pow(5, (MOD - 1) >> ccc + 1);
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
inline int deg(const poly &a) {return a.size() - 1;}
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
void output(poly a)
{
	REP(i, 0, (int)a.size() - 1) printf("%d%c", a[i], i == end_i ? '\n' : ' ');
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
int invs[maxn], last;
void prepare(int n)
{
	if (!last)
	{
		invs[0] = invs[1] = 1;
		last = 1;
	}
	if (last < n)
	{
		REP(i, last + 1, n) invs[i] = 1ll * (MOD - MOD / i) * invs[MOD % i] % MOD;
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
inline poly operator ^ (poly f, int x)
{
	f = Ln(f);
	REP(i, 0, (int)f.size() - 1) f[i] = 1ll * f[i] * x % MOD;
	return Exp_log2(f);
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

int main()
{
#ifdef CraZYali
	file("3684");
#endif
	int n = read<int>(), m = read<int>();
	poly f(n, 0);f[0] = 1;
	while (m--) (f[read<int>() - 1] += MOD - 1) %= MOD;
	cout << Inv(f ^ n)[n - 1] * inv(n) % MOD << endl;
	return 0;
}
