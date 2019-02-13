#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>
#define int long long

using namespace std;
const int maxn = 5e5 + 10, DIVIDE = 32768;
const long double pi = acos(-1);

template <typename T> inline T read()
{
	T ans(0), p(1);
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}

int n, m, MOD;

int A[maxn], B[maxn], R[maxn];
struct Complex
{
	long double x, y;
	Complex(long double _x = 0, long double _y = 0) : x(_x), y(_y) {}
	Complex operator +	(Complex B) {return Complex(x + B.x, y + B.y);}
	Complex operator +=	(Complex B) {return *this = *this + B;}
	Complex operator -	(Complex B) {return Complex(x - B.x, y - B.y);}
	Complex operator -=	(Complex B) {return *this = *this - B;}
	Complex operator *	(Complex B) {return Complex(x * B.x - y * B.y, x * B.y + B.x * y);}
	Complex operator *=	(Complex B) {return *this = *this * B;}
};

int lim = 1, L;
void FFT(Complex *a, int flag)
{
	REP(i, 0, lim - 1) if (i < R[i]) swap(a[i], a[R[i]]);
	for (int i = 1; i < lim; i <<= 1)
	{
		Complex T(cos(pi / i), flag * sin(pi / i));
		for (int k = 0; k < lim; k += (i << 1))
		{
			Complex t(1, 0);
			for (int l = 0; l < i; l++, t *= T)
			{
				Complex x = a[k + l], y = t * a[i + k + l];
				a[k + l] = x + y;
				a[i + k + l] = x - y;
			}
		}
	}
	if (flag < 0)
		REP(i, 0, lim - 1) a[i].x /= lim;
}

Complex a[maxn], b[maxn], c[maxn], d[maxn], e[maxn], f[maxn], g[maxn], h[maxn];

signed main()
{
#ifdef CraZYali
	freopen("4245.in", "r", stdin);
	freopen("4245.out", "w", stdout);
#endif
	cin >> n >> m >> MOD;
	REP(i, 0, n) A[i] = read<int>();
	REP(i, 0, m) B[i] = read<int>();
	while (lim <= n + m) lim <<= 1;L = log2(lim);
	REP(i, 0, lim) R[i] = (R[i >> 1] >> 1) | ((i & 1) << L - 1);
	REP(i, 0, lim - 1) a[i].x = A[i] / DIVIDE, b[i].x = A[i] % DIVIDE, c[i].x = B[i] / DIVIDE, d[i].x = B[i] % DIVIDE;;
	FFT(a, 1);FFT(b, 1);FFT(c, 1);FFT(d, 1);
	REP(i, 0, lim - 1) e[i] = a[i] * c[i], f[i] = a[i] * d[i], g[i] = b[i] * c[i], h[i] = b[i] * d[i];
	FFT(e, -1);FFT(f, -1);FFT(g, -1);FFT(h, -1);
	REP(i, 0, n + m) printf("%lld ", ((int)(e[i].x + 0.1) * DIVIDE % MOD * DIVIDE % MOD + (int)(f[i].x + 0.1) * DIVIDE % MOD + (int)(g[i].x + 0.1) * DIVIDE % MOD + (int)(h[i].x + 0.1)) % MOD);
	return 0;
}
