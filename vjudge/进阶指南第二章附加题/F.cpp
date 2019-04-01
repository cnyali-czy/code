#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;
const int maxN = (1 << 21) + 10;
const double pi = acos(-1);
struct Complex
{
	double a, b;
	Complex(double _a = 0, double _b = 0) : a(_a), b(_b) {}
	Complex operator +	(Complex B) {return Complex(a + B.a, b + B.b);}
	Complex operator -	(Complex B) {return Complex(a - B.a, b - B.b);}
	Complex operator *	(Complex B) {return Complex(a * B.a - b * B.b, a * B.b + b * B.a);}
	Complex operator *=	(Complex B) {return *this = *this * B;}
}F[maxN], G[maxN];

int n, m, Round, M;double r;

int len, L, R[maxN];

bool vis[maxN];
double Cos[maxN], Sin[maxN]; 
void FFT(Complex a[], int flag)
{
	REP(i, 0, len - 1)
		if (i < R[i]) swap(a[i], a[R[i]]);
	for (int i = 1; i < len; i <<= 1)
	{
		Complex T;
		if (vis[i]) T = Complex(Cos[i], flag * Sin[i]);
		else
		{
			T = Complex(Cos[i] = cos(pi / i), flag * (Sin[i] = sin(pi / i)));
			vis[i] = 1;
		}
		for (int k = 0; k < len; k += (i << 1))
		{
			Complex t(1);
			for (int l = 0; l < i; l++, t *= T)
			{
				Complex x(a[k + l]), y(a[k + l + i] * t);
				a[k + l] = x + y;
				a[k + l + i] = x - y;
			}
		}
	}
	if (flag < 0)
		REP(i, 0, len - 1) a[i].a /= 4 * len;
}

double A[maxN], B[maxN];

int main()
{
#ifdef CraZYali
	freopen("F.in", "r", stdin);
	freopen("F.out", "w", stdout);
#endif
	while (scanf("%d%d%lf", &n, &m, &r) != EOF)
	{
		Round = ceil(r);
		M = max(n, m) + 2 * Round;
		len = 1;
		while (len <= M * M) len <<= 1;
		L = log2(len);
		REP(i, 0, len) R[i] = (R[i >> 1] >> 1) | ((i & 1) << L - 1);

		REP(i, 1, n)
			REP(j, 1, m)
			scanf("%lf", A + (i-1) * M + j - 1);
		REP(i, -Round, Round)
			REP(j, -Round, Round)
			if (i * i + j * j < r * r) B[(i + Round) * M + j + Round] = 1. / (sqrt(i * i + j * j) + 1);
		REP(i, 0, len - 1) F[i] = A[i];
		REP(i, 0, len - 1) G[i] = B[i];
		FFT(F, 1);
		FFT(G, 1);
		REP(i, 0, len - 1) F[i] *= G[i];
		FFT(F, -1);
		double ans = 0;
		REP(i, 1, n)
			REP(j, 1, m)
			chkmax(ans, F[(i - 1 + Round) * M + j - 1 + Round].a);
		REP(i, 0, len - 1) F[i] = Complex(A[i] = 0, B[i] = 0);
		printf("%.3lf\n", ans * 4);
	}
	return 0;
}
