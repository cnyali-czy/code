#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <complex>
#include <cstring>
#include <cstdio>
#include <cmath>
#define double long double

using namespace std;
const int maxn = 1e5 + 10, maxN = (1<<18) + 10;
const double pi = acos(-1), eps = 1e-2;

char s[maxn], t[maxn];
int n, m, S[maxn], S2[maxn], T[maxn], T2[maxn], T3[maxn], sum[maxn];

struct Complex
{
	double a, b;
	Complex(double _a = 0, double _b = 0) : a(_a), b(_b) {}
	Complex operator +	(Complex B) {return Complex(a + B.a, b + B.b);}
	Complex operator -	(Complex B) {return Complex(a - B.a, b - B.b);}
	Complex operator *	(Complex B) {return Complex(a * B.a - b * B.b, a * B.b + b * B.a);}
	Complex operator *=	(Complex B) {return *this = *this * B;}
};

int L, len, R[maxN];
Complex F1[maxN], F2[maxN];

void FFT(Complex a[], int flag)
{
	REP(i, 0, len - 1)
		if (i < R[i]) swap(a[i], a[R[i]]);
	for (int i = 1; i < len; i <<= 1)
	{
		Complex T(cos(pi / i), flag * sin(pi / i));
		for (int k = 0; k < len; k += (i << 1))
		{
			Complex t(1, 0);
			for (int l = 0; l < i; l++, t *= T)
			{
				Complex x(a[k+l]), y(t * a[k+l+i]);
				a[k + l] = x + y;
				a[k + l + i] = x - y;
			}
		}
	}
	if (flag < 0)
		REP(i, 0, len - 1) a[i].a /= 4*len;
}

int ans[maxn];

signed main()
{
#ifdef CraZYali
	freopen("4503.in", "r", stdin);
	freopen("4503.out", "w", stdout);
#endif
	scanf("%s\n%s", s + 1, t + 1);
	n = strlen(s + 1);
	m = strlen(t + 1);
	REP(i, 1, n)
	{
		S[i] = s[i] - 'a' + 1;
		S2[i] = S[i] * S[i];
	}
	REP(i, 1, m)
	{
		T[i] = t[m - i + 1] == '?' ? 0 : t[m - i + 1] - 'a' + 1;
		T2[i] = T[i] * T[i];
		T3[i] = T2[i] * T[i];
		sum[i] = sum[i-1] + T3[i];
	}
	REP(i, m + 1, n) sum[i] = sum[i-1];
	len = 1;
	while (len <= n + n) len <<= 1;
	L = log2(len);
	REP(i, 0, len) R[i] = (R[i >> 1] >> 1) | ((i & 1) << L - 1);
	REP(i, 1, n) F1[i] = Complex(S2[i] + T[i], S2[i] - T[i]);
	REP(i, 1, n) F2[i] = Complex(S[i] + T2[i], S[i] - T2[i]);
	FFT(F1, 1);FFT(F2, 1);
	REP(i, 0, len-1) F1[i] *= F1[i], F2[i] *= F2[i];
	FFT(F1, -1);FFT(F2, -1);
	REP(k, 1, n)
	{
		//	printf("%lld %lld %lld\n", (int)F1[i].real(), (int)F2[i].real(), sum[i]);
		double c = F1[k+1].a + sum[k] - 2. * F2[k+1].a;
		//		cout << c << endl;
		if (k-m >= 0 && fabs(c)<eps) ans[++ans[0]] = k-m;
	}
	cout << ans[0] << endl;
	REP(i, 1, ans[0])printf("%d\n", ans[i]);
	return 0;
}
