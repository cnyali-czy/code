#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <cassert>
#include <iostream>
#include <cstdio>
#include <cmath>
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

int n, m, MOD, A[maxN], B[maxN];

int len, L, R[maxN];
bool vis[maxN];

void FFT(Complex f[], int flag)
{
	int n = len;
	static Complex a[maxN], pool[maxN << 1 | 10], *w[30];
	static bool vis[30];
	w[0] = pool;
	REP(i, 0, n - 1) a[i] = f[i];
	if (flag < 0) reverse(a + 1, a + n);
	REP(i, 1, n - 1)
	{
		R[i] = (R[i >> 1] >> 1) | ((i & 1) ? (n >> 1) : 0);
		if (i < R[i]) swap(a[i], a[R[i]]);
	}
	for (int i = 1, c = 0; i < n; i <<= 1, c++)
	{
		if (!vis[c])
		{
			vis[c] = 1;
			Complex wn(cosl(pi / i), sinl(pi / i));
			w[c + 1] = w[c] + i;
			w[c][0] = 1;
			REP(j, 1, i - 1) w[c][j] = w[c][j - 1] * wn;
		}
		for (int k = 0; k < n; k += i << 1)
			REP(l, 0, i - 1)
			{
				Complex x = a[k + l], y = a[k + l + i] * w[c][l];
				a[k + l] = x + y;
				a[k + l + i] = x - y;
			}
	}
	if (flag < 0)
		REP(i, 0, n - 1) a[i].a = a[i].a / 4 / n + .5;
	REP(i, 0, n - 1) f[i] = a[i];
}
inline int mod(long long x) {return x % MOD;}
signed main()
{
#ifdef CraZYali
	freopen("4245-fast.in", "r", stdin);
	freopen("4245-fast.out", "w", stdout);
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
		if (i == 1) continue;
		if (i == 2) REP(j, 0, len - 1) F[2][j] = F[1][j] + F[2][j];
		FFT(F[i], -1);
	}
	int DD = 1ll * DIVIDE * DIVIDE % MOD;
	REP(i, 0, n + m)
	{
		int a = mod(F[0][i].a), b = mod(F[2][i].a), c = mod(F[3][i].a);
		long long res = (1ll * a * DD + 1ll * b * DIVIDE + c) % MOD;
		if (res < 0) res += MOD;
		printf("%lld%c", res, i == n + m ? '\n' : ' ');
	}
	return 0;
}
