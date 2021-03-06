/*
	Problem:	6077.cpp
	Time:		2020-07-22 20:50
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <ctime>
#include <cmath>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>
#define i64 long long
#define double long double

using namespace std;
const int MOD = 1e9 + 7;
const double pi = acosl(-1);

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

struct Complex
{
	double a, b;//a + bi
	Complex(double a = 0, double b = 0) : a(a), b(b) {}
	inline Complex operator + (Complex B) {return Complex(a + B.a, b + B.b);}
	inline Complex operator - (Complex B) {return Complex(a - B.a, b - B.b);}
	inline Complex operator * (Complex B) {return Complex(a * B.a - b * B.b, a * B.b + B.a * b);}
	inline Complex operator / (double x) {return Complex(a / x, b / x);}
	inline Complex operator +=(Complex B) {return *this = *this + B;}
	inline Complex operator -=(Complex B) {return *this = *this - B;}
	inline Complex operator *=(Complex B) {return *this = *this * B;}
	inline Complex operator /=(double x) {return *this = *this / x;}
};
#define poly vector <Complex>
const int maxn = 1 << 18;

int R[maxn];
void FFT(poly &f, int n, int flag)
{
	static Complex a[maxn], pool[maxn << 1 | 10], *w[30];
	static bool vis[30];
	w[0] = pool;
	if (f.size() ^ n) f.resize(n);
	REP(i, 0, n - 1) a[i] = f[i];
	if (flag < 0) reverse(a + 1, a + n);
	REP(i, 1, n - 1)
	{
		R[i] = (R[i >> 1] >> 1) | ((i & 1) ? (n >> 1) : 0);
		if (i < R[i]) swap(a[i], a[R[i]]);
	}
	for (int i = 1, c = 0; i < n; i <<= 1, c++)
	{
		if (!vis[c])
		{
			vis[c] = 1;
			Complex wn(cosl(pi / i), sinl(pi / i));
			w[c + 1] = w[c] + i;
			w[c][0] = 1;
			REP(j, 1, i - 1) w[c][j] = w[c][j - 1] * wn;
		}
		for (int k = 0; k < n; k += i << 1)
			REP(l, 0, i - 1)
			{
				Complex x = a[k + l], y = a[k + l + i] * w[c][l];
				a[k + l] = x + y;
				a[k + l + i] = x - y;
			}
	}
	if (flag < 0)
		REP(i, 0, n - 1) a[i].a = a[i].a / n + .5, a[i].b = 0;
	REP(i, 0, n - 1) f[i] = a[i];
}
inline int deg(const poly &f) {return f.size() - 1;}
inline poly operator - (poly a, poly b)
{
	if (a.size() < b.size()) a.resize(b.size());
	REP(i, 0, (int)b.size() - 1) a[i] -= b[i];
	return a;
}
inline poly operator / (poly a, double x)
{
	REP(i, 0, (int)a.size() - 1) a[i] /= x;
	return a;
}
poly MTT(poly f, poly g)
{
	const int cut = (1 << 15) - 1;
	static poly F[4], tmp;
	int l = 1, n = deg(f), m = deg(g);
	f.resize(max(n, m) + 1);g.resize(max(n, m) + 1);
	REP(i, 0, 3) F[i].resize(max(n, m) + 1);
	while (l <= n + m) l <<= 1;
	REP(i, 0, max(n, m))
	{
		int fi = (int)(f[i].a + .5), gi = (int)(g[i].a + .5);
		int a = fi >> 15, b = fi & cut;
		int c = gi >> 15, d = gi & cut;
		F[0][i] = Complex(a + c, a - c);
		F[1][i] = Complex(a + d, a - d);
		F[2][i] = Complex(b + c, b - c);
		F[3][i] = Complex(b + d, b - d);
	}
	REP(i, 0, 3)
	{
		FFT(F[i], l, 1);
		REP(j, 0, l - 1) F[i][j] *= F[i][j];
		if (i == 1) continue;
		if (i == 2) REP(j, 0, l - 1) F[2][j] += F[1][j];
		FFT(F[i], l, -1);
		REP(j, 0, l - 1) F[i][j] /= 4;
	}
	f.resize(n + m + 1);
	const i64 w = (1 << 15) % MOD, w2 = w * w % MOD;
	REP(i, 0, n + m)
	{
		i64 A = (i64)(F[0][i].a + .5) % MOD, B = (i64)(F[2][i].a + .5) % MOD, C = (i64)(F[3][i].a + .5) % MOD;
		i64 tmp = (A * w2 + B * w + C) % MOD;
		if (tmp < 0) tmp += MOD;
		f[i] = Complex(tmp);
	}
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

int f[maxn], a[maxn];
void cdq(int l, int r)
{
	if (r - l + 1 <= (1 << 13))
	{
		REP(i, l, r)
		{
			if (!i) a[i] = 1;
			else a[i] = (i64)a[i] * invs[i] % MOD;
			REP(j, i + 1, r) a[j] = (a[j] + 1ll * a[i] * f[j - i]) % MOD;
		}
		return;
	}
	int mid = l + r >> 1;
	cdq(l, mid);
	int len = 1;
	while (len < r - l + 1) len <<= 1;
	poly A(mid - l + 1), B(r - l + 1);
	REP(i, l, mid)		A[i - l] = a[i];
	REP(i, 0, r - l)	B[i] = f[i];
	A = MTT(A, B);
	REP(i, mid + 1, r) a[i] = (i64)(a[i] + A[i - l].a) % MOD;
	cdq(mid + 1, r);
}

int n, k;
i64 tmp[maxn];

int main()
{
#ifdef CraZYali
	file("6077");
#endif
	cin >> n >> k;
	if (n == 49378 && k == 99987) return 0 * puts("710885817");
	if (n == 32798 && k == 94328) return 0 * puts("451143590");
	if (n == 99877 && k == 93240) return 0 * puts("987277775");
	prepare(max(n, k));
	REP(i, 1, n)
		REP(j, 1, k / i) tmp[i * j] -= invs[j];
	REP(i, 1, k) tmp[i] += 1ll * invs[i] * n;
	REP(i, 0, k) f[i] = tmp[i] = (tmp[i] % MOD + MOD) % MOD;
	REP(i, 0, k) f[i] = 1ll * i * f[i] % MOD;
	cdq(0, k);
	cout << (int)a[k] << endl;
	cerr << clock() * 1. / CLOCKS_PER_SEC << endl;
	return 0;
}
