#define REP(i, s, e) for(int i = s; i <= e ;i++)

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
}F[maxn << 2], G[maxn << 2], GG[maxn << 2];

int n;
double q[maxn];

int len, L, R[maxn << 2];
void FFT(Complex a[], int flag)
{
	REP(i, 1, len - 1)
		if (i < R[i]) swap(a[i], a[R[i]]);
	for (int i = 1; i < len; i <<= 1)
	{
		Complex T(cos(pi / i), flag * sin(pi / i));
		for (int k = 0; k < len; k += (i << 1))
		{
			Complex t(1);
			for (int l = 0; l < i; l++, t *= T)
			{
				Complex x(a[k + l]), y(t * a[k + l + i]);
				a[k + l] = x + y;
				a[k + l + i] = x - y;
			}
		}
	}
	if (flag < 0)
		REP(i, 0, len - 1) a[i].a /= len;
}

int main()
{
#ifdef CraZYali
	freopen("3527-new.in", "r", stdin);
	freopen("3527-new.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n) scanf("%LF", q + i);
	REP(i, 1, n)
	{
		F[i].a = q[i];
		G[i].a = GG[n - i + 1].a = 1. / i / i;
	}
	len = 1;
	while (len <= n + n) len <<= 1;
	L = log2(len);
	REP(i, 1, len) R[i] = (R[i >> 1] >> 1) | ((i & 1) << L - 1);
	FFT(F, 1);FFT(G, 1);FFT(GG, 1);
	REP(i, 0, len-1) G[i] *= F[i];
	REP(i, 0, len-1) GG[i] *= F[i];
	FFT(G, -1);FFT(GG, -1);
	REP(i, 1, n) printf("%.3LF\n", G[i].a - GG[n + i + 1].a);
	return 0;
}
