#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>
#include <cmath>
#define int long long
#define double long double

using namespace std;
const int maxn = 1e5 + 10, maxN = (1 << 18) + 10, DIVIDE = 32768;
const double pi = acos(-1);

template <typename T> T read()
{
	T ans = 0, p = 1;
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

struct Complex
{
	double a, b;
	Complex(double _a = 0, double _b = 0) : a(_a), b(_b) {}
	Complex operator + (Complex B) {return Complex(a + B.a, b + B.b);}
	Complex operator - (Complex B) {return Complex(a - B.a, b - B.b);}
	Complex operator * (Complex B) {return Complex(a * B.a - b * B.b, a * B.b + b * B.a);}
	Complex operator *=(Complex B) {return *this = *this * B;}
}F[4][maxN];

int n, m, MOD, A[maxn], B[maxn];

int len, L, R[maxN];
void FFT(Complex a[], int flag)
{
	REP(i, 0, len - 1)
		if (i < R[i]) swap(a[i], a[R[i]]);
	for (int i = 1; i < len ; i <<= 1)
	{
		Complex T(cos(pi / i), flag * sin(pi / i));
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
	if (flag < 0) REP(i, 0, len - 1) a[i].a = a[i].a / 4 / len + 0.5;
}

int mod(int x) {return (x % MOD + MOD) % MOD;}
signed main()
{
#ifdef CraZYali
	freopen("4245-new.in", "r", stdin);
	freopen("4245-new.out", "w", stdout);
#endif
	cin >> n >> m >> MOD;
	REP(i, 0, n) A[i] = read<int>();
	REP(i, 0, m) B[i] = read<int>();
	len = 1;
	while (len <= n + m) len <<= 1;
	L = log2(len);
	REP(i, 0, len) R[i] = (R[i >> 1] >> 1) | ((i & 1) << L - 1);
	int l = max(n, m);
	REP(i, 0, l)
	{
		int a(A[i] / DIVIDE), b(A[i] % DIVIDE), c(B[i] / DIVIDE), d(B[i] % DIVIDE);
		F[0][i] = Complex(a + c, a - c);
		F[1][i] = Complex(a + d, a - d);
		F[2][i] = Complex(b + c, b - c);
		F[3][i] = Complex(b + d, b - d);
	}
	REP(i, 0, 3)
	{
		FFT(F[i], 1);
		REP(j, 0, len - 1) F[i][j] *= F[i][j];
		FFT(F[i], -1);
	}
	REP(i, 0, n + m)
	{
		int a((int)F[0][i].a), b((int)F[1][i].a), c((int)F[2][i].a), d((int)F[3][i].a);
		a = mod(a * DIVIDE % MOD * DIVIDE);
		b = mod(b * DIVIDE);
		c = mod(c * DIVIDE);
		d = mod(d);
		printf("%lld%c", mod(mod(mod(a + b) + c) + d), i == n + m ? '\n' : ' ');
	}
	return 0;
}
