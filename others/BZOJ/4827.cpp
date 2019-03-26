#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>
#include <cmath>
#define double long double
#define int long long

using namespace std;
const int maxn = 50000 + 10 << 1, inf = 1ll << 60;
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
	double x, y;
	Complex(double _x = 0, double _y = 0) : x(_x), y(_y){}
	Complex operator +	(Complex B) {return Complex(x + B.x, y + B.y);}
	Complex operator += (Complex B) {return *this = *this + B;}
	Complex operator -	(Complex B) {return Complex(x - B.x, y - B.y);}
	Complex operator -= (Complex B) {return *this = *this - B;}
	Complex operator *	(Complex B) {return Complex(x * B.x - y * B.y, x * B.y + y * B.x);}
	Complex operator *= (Complex B) {return *this = *this * B;}
}F[3 * maxn], G[3 * maxn];
int n, m, a[maxn], b[maxn];
int R[maxn * 3], len, L;

int static_sum, all_sum, ans = inf;

void FFT(Complex *a, int flag)
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
				Complex x = a[k + l], y = t * a[k + l + i];
				a[k + l] = x + y;
				a[k + l + i] = x - y;
			}
		}
	}
	if (flag < 0) REP(i, 0, len - 1) a[i].x = (int)(a[i].x / len + 0.5);
}
signed main()
{
#ifdef CraZYali
	freopen("4827.in", "r", stdin);
	freopen("4827.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, n) a[i] = read<int>();
	REP(i, 1, n) b[i] = read<int>();
	REP(i, 1, n) static_sum += a[i] * a[i] + b[i] * b[i], all_sum += a[i] - b[i];
	len = 1;
	while (len <= n + n + n) len <<= 1;
	L = log2(len);
	REP(i, 0, len) R[i] = (R[i >> 1] >> 1) | ((i & 1) << L - 1);
	int l(1), r(n);
	while (l < r) swap(b[l++], b[r--]);
	REP(i, 1, n) F[i].x = F[i + n].x = a[i];
	REP(i, 1, n) G[i].x = b[i];
	FFT(F, 1);
	FFT(G, 1);
	REP(i, 0, len) F[i] *= G[i];
	FFT(F, -1);
	REP(i, 1, n)
		REP(c, -m, m)
		chkmin(ans, static_sum + n * c * c + 2 * c * all_sum - 2 * (int)F[i+n].x);
	cout << ans << endl;
	return 0;
}
