#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>
#define int long long

using namespace std;
const int maxn = 3e6 + 10, maxm = 3e6 + 10;
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

int n, m, lim = 1, L, R[maxn];

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
}F[maxn], G[maxm];

void FFT(Complex *a, int flag)
{
	REP(i, 0, lim - 1)
		if (i < R[i]) swap(a[i], a[R[i]]);
	for (register int j = 1; j < lim; j <<= 1)
	{
		Complex T(cos(pi / j), flag * sin(pi / j));
		for (register int k = 0;k < lim;k += (j << 1))
		{
			Complex t(1, 0); 
			for (int l = 0; l < j;l++, t *= T)
			{
				Complex x = a[k + l], y = t * a[k + l + j];
				a[k + l] = x + y;
				a[k + l + j] = x - y;
			}
		}
	}
}

signed main()
{
#ifdef CraZYali
	freopen("3803.in", "r", stdin);
	freopen("3803.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 0, n) F[i].x = read<int>();
	REP(i, 0, m) G[i].x = read<int>();
	while (lim <= n + m) lim <<= 1;
	L = log2(lim);
	REP(i, 0, lim) R[i] = (R[i >> 1] >> 1) | ((i & 1) << L - 1);
	FFT(F, 1);FFT(G, 1);
	REP(i, 0, lim) F[i] *= G[i];
	FFT(F, -1);
	REP(i, 0, n + m)
		printf("%lld ", (int)(F[i].x / lim + 0.5));
	return 0;
}
