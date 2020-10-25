#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

<<<<<<< HEAD
#include <tuple>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;
const int MOD1 = 998244353, MOD2 = (5 << 25) + 1, MOD3 = (7 << 26) + 1;
#define poly vector <num>
#define i64 long long
#define ui64 unsigned i64

struct num
{
	int x1, x2, x3;
	num(int x1 = 0, int x2 = 0, int x3 = 0) : x1(x1), x2(x2), x3(x3) {}
	num operator + (num B) {return num((x1 + B.x1) % MOD1, (x2 + B.x2) % MOD2, (x3 + B.x3) % MOD3);}
	num operator - (num B) {return num((x1 + MOD1 - B.x1) % MOD1, (x2 + MOD2 - B.x2) % MOD2, (x3 + MOD3 - B.x3) % MOD3);}
	num operator * (num B) {return num(1ll * x1 * B.x1 % MOD1, 1ll * x2 * B.x2 % MOD2, 1ll * x3 * B.x3 % MOD3);}
};
num power_pow(num base, int b)
{
	num ans(1, 1, 1);
	while (b)
	{
		if (b & 1) ans = ans * base;
		base = base * base;
		b >>= 1;
	}
	return ans;
}
i64 power_pow(i64 base, int b, const int MOD)
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
=======
#include <cstring>
#include <cmath>
#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 1e5 + 10;
>>>>>>> 795ce3cf86d2711d1ec0562bcb4ab72eea06f1fd

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
<<<<<<< HEAD
		ans = ans * 10 + c - 48;
=======
		ans = ans * 10 + (c - 48);
>>>>>>> 795ce3cf86d2711d1ec0562bcb4ab72eea06f1fd
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

<<<<<<< HEAD
const int maxn = 1 << 21;

#define NUM tuple <ui64, ui64, ui64>
NUM operator + (NUM A, NUM B) {return make_tuple(get<0>(A) + get<0>(B), get<1>(A) + get<1>(B), get<2>(A) + get<2>(B));}
NUM operator - (NUM A, NUM B) {return make_tuple(get<0>(A) + MOD1 - get<0>(B), get<1>(A) + MOD2 - get<1>(B), get<2>(A) + MOD3 - get<2>(B));}
NUM operator * (NUM A, num B) {return make_tuple(get<0>(A) * B.x1 % MOD1, get<1>(A) * B.x2 % MOD2, get<2>(A) * B.x3 % MOD3);}

i64 inv(int x, const int MOD) {return power_pow(x, MOD - 2, MOD);}

void NTT(poly &a, int n, int flag)
{
	static tuple <ui64, ui64, ui64> NTTtmp[maxn];
	static int R[maxn];
	if (a.size() ^ n) a.resize(n);
	if (flag < 0) reverse(a.begin() + 1, a.end());
	static num *w[30], pool[maxn << 1 | 10];
	static bool vis[30];
	w[0] = pool;
	REP(i, 0, n - 1)
	{
		R[i] = (R[i >> 1] >> 1) | ((i & 1) ? (n >> 1) : 0);
		if (i < R[i]) swap(a[i], a[R[i]]);
	}
	REP(i, 0, n - 1) NTTtmp[i] = make_tuple(a[i].x1, a[i].x2, a[i].x3);
	for (int i = 1, c = 0; i < n; i <<= 1, c++)
	{
		if (!vis[c])
		{
			vis[c] = 1;
			const num wn(power_pow(3, (MOD1 - 1) >> c + 1, MOD1), power_pow(3, (MOD2 - 1) >> c + 1, MOD2), power_pow(3, (MOD3 - 1) >> c + 1, MOD3));
			if (i < maxn) w[c + 1] = w[c] + i;
			w[c][0] = num(1, 1, 1);
			REP(j, 1, i - 1) w[c][j] = w[c][j - 1] * wn;
		}
		for (int k = 0; k < n; k += i + i)
			for (int l = 0; l < i; l++)
			{
				auto x = NTTtmp[k + l], y = NTTtmp[k + l + i] * w[c][l];
				NTTtmp[k + l] = x + y;
				NTTtmp[k + l + i] = x - y;
			}
	}
	REP(i, 0, n - 1) a[i] = num(get<0>(NTTtmp[i]) % MOD1, get<1>(NTTtmp[i]) % MOD2, get<2>(NTTtmp[i]) % MOD3);
	if (flag < 0)
	{
		const int inv1 = inv(n, MOD1), inv2 = inv(n, MOD2), inv3 = inv(n, MOD3);
		REP(i, 0, n - 1)
		{
			a[i].x1 = 1ll * a[i].x1 * inv1 % MOD1;
			a[i].x2 = 1ll * a[i].x2 * inv2 % MOD2;
			a[i].x3 = 1ll * a[i].x3 * inv3 % MOD3;
		}
	}
}
inline int deg(const poly &a) {return (int)a.size() - 1;}
int n, p;
inline int fix(num x)
{
	static const int MOD = p;
	static const i64 inv1 = inv(MOD1, MOD2);
	static const i64 inv12 = inv(1ll * MOD1 * MOD2 % MOD3, MOD3);
	i64 k1 = (x.x2 + MOD2 - x.x1 % MOD2) * inv1 % MOD2;
	i64 x4 = x.x1 + k1 * MOD1;
	i64 k4 = (x.x3 + MOD3 - x4 % MOD3) % MOD3 * inv12 % MOD3;
	return (x4 + k4 * MOD1 % MOD * MOD2) % MOD;
}
poly fix(poly a)
{
	for (auto &i : a)
	{
		int r = fix(i);
		i = num(r, r, r);
	}
	return a;
}
poly operator * (poly A, poly B)
{
	int n = deg(A), m = deg(B), l = 1;
	while (l <= n + m) l <<= 1;
	NTT(A, l, 1);NTT(B, l, 1);
	REP(i, 0, l - 1) A[i] = A[i] * B[i];
	NTT(A, l, -1);
	A.resize(n + m + 1);
	return fix(A);
}
poly Inv(poly f)
{
	static const int MOD = p;
	int n = deg(f);
	int l = 1;
	while (l <= n) l <<= 1;
	poly a(1, num(inv(f[0].x1, MOD1), inv(f[0].x2, MOD2), inv(f[0].x3, MOD3)));
	for (int N = 2; N <= l; N <<= 1)
	{
		poly tmp(f.begin(), f.begin() + min(N, n + 1));
		tmp = tmp * a;
		for (auto &i : tmp) i = num(MOD - i.x1, MOD - i.x2, MOD - i.x3);
		tmp[0] = tmp[0] + num(2, 2, 2);
		a = a * tmp;
		a.resize(N);
	}
	a.resize(n + 1);
	return a;
}
num invs[maxn];
poly exp(poly f)
{
	int n = deg(f);
	poly a(n + 1, num(1, 1, 1));
	REP(i, 0, n) f[i] = f[i] * num(i, i, i);
	REP(m, 0, n - 1)
	{
		num z(0, 0, 0);
		REP(i, 0, m) z = z + (f[i + 1] * a[m - i]);
		int r = fix(z * invs[m + 1]);
		a[m + 1] = num(r, r, r);
	}
	return a;
}
int solve(int S)
{
	if (S > n) return 0;
	poly res(n + 1);
	REP(i, S, n)
		REP(j, 1, n / i)
		res[i * j] = res[i * j] + invs[j];
	res = exp(fix(res));
	return fix(res[n]);
}
=======
int n, p, B;

int solve(int s)
{
	if (s > n) return 0;
	const int MOD = p;
	static int f[maxn], g[maxn], G[maxn];
	REP(i, 1, n) f[i] = 0;f[0] = 1;
	int B = max(::B, s - 1);
	REP(i, s, B)
		REP(j, i, n) f[j] = (f[j] + f[j - i]) % MOD;
	memset(g, 0, sizeof g);
	memset(G, 0, sizeof G);
	g[0] = G[0] = 1;
	REP(i, 1, n / B)
	{
		REP(j, 0, n)
		{
			if (j >= i) g[j] = (g[j] + g[j - i]) % MOD;
			if (j + i * (B + 1) <= n)
				G[j + i * (B + 1)] = (G[j + i * (B + 1)] + g[j]) % MOD;
		}
	}
	i64 ans = 0;
	REP(i, 0, n) ans = (ans + 1ll * f[i] * G[n - i]) % MOD;
	return ans;
}

>>>>>>> 795ce3cf86d2711d1ec0562bcb4ab72eea06f1fd
int x, y;

int main()
{
#ifdef CraZYali
	file("C");
#endif
	cin >> x >> y >> n >> p;
<<<<<<< HEAD
	invs[0] = num(1, 1, 1);
	invs[1] = num(1, 1, 1);
	REP(i, 2, n)
	{
		invs[i].x1 = 1ll * (MOD1 - MOD1 / i) * invs[MOD1 % i].x1 % MOD1;
		invs[i].x2 = 1ll * (MOD2 - MOD2 / i) * invs[MOD2 % i].x2 % MOD2;
		invs[i].x3 = 1ll * (MOD3 - MOD3 / i) * invs[MOD3 % i].x3 % MOD3;
	}
	cout << (solve(x) + p - solve(y + 1)) % p << endl;
=======
	B = sqrt(n);
	cout << (solve(x) - solve(y + 1) + p) % p << endl;
>>>>>>> 795ce3cf86d2711d1ec0562bcb4ab72eea06f1fd
	return 0;
}
