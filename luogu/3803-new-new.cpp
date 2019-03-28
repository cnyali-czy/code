#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;
const int maxn = 1e6 + 10, maxm = 1e6 + 10, maxN = (1 << 21) + 10;
const double pi = acos(-1);

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
struct Complex
{
	double x, y;
	Complex(double _x = 0, double _y = 0) : x(_x), y(_y) {}
	Complex operator +	(Complex B)  {return Complex(x + B.x, y + B.y);}
	Complex operator +=	(Complex B)  {return *this = *this + B;}
	Complex operator -	(Complex B)  {return Complex(x - B.x, y - B.y);}
	Complex operator -=	(Complex B)  {return *this = *this - B;}
	Complex operator *	(Complex B)  {return Complex(x * B.x - y * B.y, x * B.y + y * B.x);}
	Complex operator *=	(Complex B)  {return *this = *this * B;}
}F[maxN];

int n, m, M, a[maxn], b[maxm];
int len, L, R[maxN];

void FFT(Complex a[], int flag)
{
	REP(i, 1, len-1)
		if (i < R[i]) swap(a[i], a[R[i]]);
	for (int i = 1; i < len; i <<= 1)
	{
		Complex T(cos(pi / i), flag * sin(pi / i));
		for (int k = 0; k < len; k += (i << 1))
		{
			Complex t(1);
			for (int l = 0; l < i;l++, t *= T)
			{
				Complex x(a[k + l]), y(a[k + l + i] * t);
				a[k + l] = x + y;
				a[k + l + i] = x - y;
			}
		}
	}
	if (flag < 0)
		REP(i, 0, len - 1) a[i].x = a[i].x / len / 4 + 0.5;
}

int main()
{
#ifdef CraZYali
	freopen("3803-new-new.in", "r", stdin);
	freopen("3803-new-new.out", "w", stdout);
#endif
	cin >> n >> m;M = max(n, m);
	REP(i, 0, n) a[i] = read<int>();
	REP(i, 0, m) b[i] = read<int>();
	len = 1;
	while (len <= n + m) len <<= 1;
	L = log2(len);
	REP(i, 0, len) R[i] = (R[i >> 1] >> 1) | ((i & 1) << L - 1);
	REP(i, 0, M) F[i] = Complex(a[i] + b[i], a[i] - b[i]);
	FFT(F, 1);
	REP(i, 0, len - 1) F[i] *= F[i];
	FFT(F, -1);
	REP(i, 0, n + m) printf("%d ", (int)F[i].x);
	return 0;
}
