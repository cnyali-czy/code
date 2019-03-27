#define REP(i, s, e) for (int i = s; i <= e; i++)

#include <iostream>
#include <cstdio>
#include <cmath>
#include <complex>
#define double long double

using namespace std;
const int maxn = 1e5 + 10;
const double pi = acos(-1);

int n;
int len, L, R[maxn << 2];

void FFT(complex <double> a[], int flag)
{
	REP(i, 0, len - 1)
		if (i < R[i]) swap(a[i], a[R[i]]);
	for (int i = 1; i < len; i <<= 1)
	{
		complex <double> T(cos(pi / i), flag * sin(pi / i));
		for (int k = 0; k < len; k += (i << 1))
		{
			complex <double> t(1, 0);
			for (int l = 0; l < i; l++, t *= T)
			{
				complex <double> x(a[k+l]), y(t * a[k+l+i]);
				a[k + l] = x + y;
				a[k + l + i] = x - y;
			}
		}
	}
	if (flag < 0)
		REP(i, 0, len - 1) a[i].real(a[i].real() / len + 0.5);
}
complex <double> F[maxn << 2], G[maxn << 2];

int main()
{
#ifdef CraZYali
	freopen("2194.in", "r", stdin);
	freopen("2194.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n)
	{
		double a, b;
		scanf("%LF%LF", &a, &b);
		F[i].real(a);G[n-i+1].real(b);
	}
	len = 1;
	while (len <= n + n) len <<= 1;
	L = log2(len);
	REP(i, 1, len) R[i] = (R[i >> 1] >> 1) | ((i & 1) << L - 1);
	FFT(F, 1);FFT(G, 1);
	REP(i, 0, len - 1) F[i] *= G[i];
	FFT(F, -1);
	REP(i, 1, n) printf("%d\n", (int)F[n + i].real());
	return 0;
}
