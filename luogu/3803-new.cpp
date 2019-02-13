#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 3e6 + 10;
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
	Complex(double _x = 0, double _y = 0) : x(_x), y(_y){}
	Complex operator +	(Complex B) {return Complex(x + B.x, y + B.y);}
	Complex operator += (Complex B) {return *this = *this + B;}
	Complex operator -	(Complex B) {return Complex(x - B.x, y - B.y);}
	Complex operator -= (Complex B) {return *this = *this - B;}
	Complex operator *	(Complex B) {return Complex(x * B.x - y * B.y, x * B.y + y * B.x);}
	Complex operator *= (Complex B) {return *this = *this * B;}
}F[maxn], G[maxn];

int n, m, lim = 1, L, R[maxn];

void FFT(Complex *a, int flag)
{
	REP(i, 0, lim - 1)
		if (i < R[i]) swap(a[i], a[R[i]]);
	for (int i = 1; i < lim; i <<= 1)
	{
		Complex T(cos(pi / i), flag * sin(pi / i));
		for (int k = 0; k < lim; k += (i << 1))
		{
			Complex t(1, 0);
			for (int l = 0; l < i; l++, t *= T)
			{
				Complex x = a[k + l], y = t * a[k + l + i];
				a[k + l] = x + y;
				a[k + l + i] = x - y;
			}
		}
	}
	if (flag < 0) REP(i, 0, lim - 1) a[i].x /= lim;
}

int main()
{
#ifdef CraZYali
	freopen("3803-new.in", "r", stdin);
	freopen("3803-new.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 0, n) F[i].x = read<int>();
	REP(i, 0, m) G[i].x = read<int>();
	while (lim <= n + m) lim <<= 1;L = log2(lim);
	REP(i, 0, lim) R[i] = (R[i >> 1] >> 1) | ((i & 1) << L - 1);
	FFT(F, 1);FFT(G, 1);
	REP(i, 0, lim - 1) F[i] *= G[i];
	FFT(F, -1);
	REP(i, 0, n + m) printf("%d ", (int)(F[i].x + 0.5));
	return 0;
}
