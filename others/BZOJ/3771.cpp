#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <iostream>
#include <cstdio>
#include <cmath>
#define double long double

using namespace std;
const double pi = acos(-1);
const int l = 17, len = 1 << l;

template <typename T> T read()
{
	T ans(0), flag(1);
	char c(getchar());
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

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

struct Complex
{
	double x, y;
	Complex(double _x = 0, double _y = 0) : x(_x), y(_y) {}
	Complex operator + (Complex B) {return Complex(x + B.x, y + B.y);}
	Complex operator - (Complex B) {return Complex(x - B.x, y - B.y);}
	Complex operator * (Complex B) {return Complex(x * B.x - y * B.y, x * B.y + B.x * y);}
	Complex operator *=(Complex B) {return *this = *this * B;}
	Complex operator / (double v)  {return Complex(x / v, y / v);}
	Complex operator /=(double v)  {return *this = *this / v;}
	//(x + yi) / (B.x + B.yi)
	//(x + yi) * (B.x - B.yi) / (B.x^2 + B.y^2)
	Complex operator / (Complex B) {return Complex(x, y) * Complex(B.x, -B.y) / (B.x * B.x + B.y * B.y);}
}F[len], G[len], T[len], two(2), three(3), six(6);

int m, n, k, R[len];
void FFT(Complex a[], int flag)
{
	REP(i, 1, len-1) if (i < R[i]) swap(a[i], a[R[i]]);
	for (int i(1); i < len; i <<= 1)
	{
		Complex T(cos(pi / i), flag * sin(pi / i));
		for (int k(0); k < len; k += (i << 1))
		{
			Complex t(1);
			for (int l(0); l < i;l++, t *= T)
			{
				Complex x(a[k + l]), y(t * a[k + l + i]);
				a[k + l] = x + y;
				a[k + l + i] = x - y;
			}
		}
	}
	if (flag == -1)
		REP(i, 0, len-1) a[i] /= len;
}

int main()
{
#ifdef CraZYali
	file("3771");
#endif
	n = read<int>();
	while (n--)
	{
		int x = read<int>();
		F[x] = G[x * 2] = T[x * 3] = Complex(1);
	}
	REP(i, 1, len-1) R[i] = (R[i >> 1] >> 1) | ((i & 1) << l-1);
	FFT(F, 1);FFT(G, 1);FFT(T, 1);
	REP(i, 0, len-1) F[i] = (F[i] * F[i] * F[i] - three * F[i] * G[i] + two * T[i]) / six + (F[i] * F[i] - G[i]) / two + F[i];
	FFT(F, -1);
	REP(i, 0, len - 1)
		if (int(F[i].x + 0.5)) printf("%d %d\n", i, int(F[i].x + 0.5));
	return 0;
}
