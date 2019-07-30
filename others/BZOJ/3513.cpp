#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;
const int l = 18, len = 1 << l, maxn = 1e5 + 10;
const double pi = acos(-1);

template <typename T> inline T read()
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

inline void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

struct Complex
{
	double x, y;
	inline Complex(double _x = 0, double _y = 0) : x(_x), y(_y) {}
	inline Complex operator + (Complex B) {return Complex(x + B.x, y + B.y);}
	inline Complex operator - (Complex B) {return Complex(x - B.x, y - B.y);}
	inline Complex operator * (Complex B) {return Complex(x * B.x - y * B.y, x * B.y + B.x * y);}
	inline Complex operator *=(Complex B) {return *this = *this * B;}
	inline Complex operator / (double v)  {return Complex(x / v, y / v);}
	inline Complex operator /=(double v)  {return *this = *this / v;}
	//(x + yi) / (B.x + B.yi)
	//(x + yi) * (B.x - B.yi) / (B.x^2 + B.y^2)
	inline Complex operator / (Complex B) {return Complex(x, y) * Complex(B.x, -B.y) / (B.x * B.x + B.y * B.y);}
}F[len];

int m, n, k, R[len];
inline void FFT(Complex a[], int flag)
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
long long t[len], G[len];

signed main()
{
#ifdef CraZYali
	file("3513");
#endif
	REP(i, 1, len - 1) R[i] = (R[i >> 1] >> 1) | ((i & 1) << l - 1);
	int T = read<int>();
	while (T--)
	{
		REP(i, 0, len-1) F[i] = Complex();
		memset(t, 0, sizeof(t));
		memset(G, 0, sizeof(G));
		n = read<int>();
		REP(i, 1, n)
		{
			int x = read<int>();
			t[x]++;
			F[x].x += 1;
			G[x << 1]--;
		}
		FFT(F, 1);
		REP(i, 0, len - 1) F[i] *= F[i];
		FFT(F, -1);
		DREP(i, 1e5, 1) t[i] += t[i+1];
		REP(i, 0, len - 1) G[i] += (long long)(F[i].x + .5);
		long long ans = 0, tot = 1ll * n * (n-1) * (n-2) / 6;
		REP(i, 0, len - 1) ans += (G[i] >> 1) * t[i];
		printf("%.7lf\n", 1. - ans * 1. / tot);
	}
	return 0;
}
