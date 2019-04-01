#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;
const int maxn = 50000 + 10, maxN = (1 << 17) + 10;
const double pi = acos(-1);

struct Complex
{
	double a, b;
	Complex(double _a = 0, double _b = 0) : a(_a), b(_b) {}
	Complex operator + (Complex B) {return Complex(a + B.a, b + B.b);}
	Complex operator - (Complex B) {return Complex(a - B.a, b - B.b);}
	Complex operator * (Complex B) {return Complex(a * B.a - b * B.b, a * B.b + b * B.a);}
	Complex operator *=(Complex B) {return *this = *this * B;}
}F[maxN];

int n, m;
char A[maxn], B[maxn];

int len, L, R[maxN];
double Cos[maxN], Sin[maxN];
bool vis[maxN];

void FFT(Complex a[], int flag)
{
	REP(i, 0, len - 1)
		if (i < R[i]) swap(a[i], a[R[i]]);
	for (int i = 1; i < len ; i <<= 1)
	{
		Complex T;
		if (vis[i]) T = Complex(Cos[i], flag * Sin[i]);
		else T = Complex(Cos[i] = cos(pi / i), flag * (Sin[i] = sin(pi / i))), vis[i] = 1;
		for (int k = 0; k < len ; k += (i << 1))
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
		REP(i, 0, len - 1) a[i].a = a[i].a / (len * 4) + 0.5;
}

int C[maxn << 1];

int main()
{
#ifdef CraZYali
	freopen("E.in", "r", stdin);
	freopen("E.out", "w", stdout);
#endif
	while (scanf("%s\n%s", A, B) != EOF)
	{
		n = strlen(A) - 1;
		m = strlen(B) - 1;
		REP(i, m + 1, n) B[i]='0';
		REP(i, n + 1, m) A[i]='0';
		REP(i, 0, n/2) swap(A[i], A[n - i]);
		REP(i, 0, m/2) swap(B[i], B[m - i]);
		REP(i, 0, max(n, m)) F[i] = Complex(A[i] + B[i] - '0'*2, A[i] - B[i]);
		len = 1;
		while (len <= n + m) len <<= 1;
		L = log2(len);
		REP(i, 1, len) R[i] = (R[i >> 1] >> 1) | ((i & 1) << L - 1);
		FFT(F, 1);
		REP(i, 0, len - 1) F[i] *= F[i];
		FFT(F, -1);
		REP(i, 0, n + m + 1) C[i] = 0;
		REP(i, 0, n + m) C[i] = (int)F[i].a;
		REP(i, 0, len - 1) F[i] = Complex(0,0);
		REP(i, 0, n + m)
		{
			C[i+1] += C[i] / 10;
			C[i] %= 10;
		}
		int now = n + m + 1;
		while (now && !C[now])now--;
		DREP(i, now, 0) putchar(C[i] + '0');putchar(10);
	}
	return 0;
}
