#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>
#include <cmath>
#define double long double

using namespace std;
const int maxn = 100000 + 10;
const double pi = acos(-1);

struct Complex
{
	double a, b;
	Complex(double _a = 0, double _b = 0) : a(_a), b(_b) {}
	Complex operator +	(Complex B) {return Complex(a + B.a, b + B.b);}
	Complex operator +=	(Complex B) {return *this = *this + B;}
	Complex operator -	(Complex B) {return Complex(a - B.a, b - B.b);}
	Complex operator -=	(Complex B) {return *this = *this - B;}
	Complex operator *	(Complex B) {return Complex(a * B.a - b * B.b, a * B.b + b * B.a);}
	Complex operator *=	(Complex B) {return *this = *this * B;}
}F[maxn << 2], FF[maxn << 2], G[maxn << 2];

int n;
double q[maxn];

int len, L, R[maxn << 2];
void FFT(Complex a[], int flag)
{
	REP(i, 0, len - 1)
		if (i < R[i]) swap(a[i], a[R[i]]);
	for (int i = 1; i < len; i <<= 1)
	{
		Complex T(cos(pi / i), sin(pi / i) * flag);
		for (int k = 0; k < len; k += (i << 1))
		{
			Complex t(1, 0);
			for (int l = 0; l < i; l++, t *= T)
			{
				Complex x(a[k + l]), y(t * a[k + l + i]);
				a[k + l] = x + y;
				a[k + l + i] = x - y;
			}
		}
	}
	if (flag < 0) REP(i, 0, len - 1) a[i].a /= len; 
}

int main()
{
#ifdef CraZYali
	freopen("3527.in", "r", stdin);
	freopen("3527.out", "w", stdout);
#endif
	cin >> n;n--;
	REP(i, 0, n) scanf("%LF", q + i);
	len = 1;
	while (len <= n + n) len <<= 1;
	L = log2(len);
	REP(i, 0, len) R[i] = (R[i >> 1] >> 1) | ((i & 1) << L - 1);
	REP(i, 0, n) F[i].a = FF[n-i].a = q[i], G[i].a = (!i ? 0 : 1. / i / i);
	FFT(F, 1);FFT(FF, 1);FFT(G, 1);
	REP(i, 0, len - 1) F[i] *= G[i];
	REP(i, 0, len - 1) FF[i] *= G[i];
	FFT(F, -1);FFT(FF, -1);
	REP(i, 0, n)
		printf("%.3LF\n", F[i].a - FF[n-i].a);
	return 0;
}
