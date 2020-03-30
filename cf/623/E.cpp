#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <iostream>
#include <cstdio>
#include <cmath>
#define i64 long long
using namespace std;
const int maxn = 1 << 18, maxk = 3e4 + 10, MOD = 1000000007;


int add() {return 0;}
	template <typename ...T>
int add(int x, T... y)
{
	int res = x + add(y...);
	if (res >= MOD) res -= MOD;
	return res;
}

int sub(int x, int y)
{
	int res = x - y;
	if (res < 0) res += MOD;
	return res;
}

int mul() {return 1;}
	template <typename ...T>
int mul(int x, T... y)
{
	long long res = (long long)x * mul(y...);
	if (res >= MOD) res %= MOD;
	return res;
}
int power_pow(int base, int b)
{
	int ans = 1;
	while (b)
	{
		if (b & 1) ans = mul(ans, base);
		base = mul(base, base);
		b >>= 1;
	}
	return ans;
}
#define inv(x) power_pow(x, MOD - 2)

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

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout);

int fac[maxn], Inv[maxn], bin[maxn];
struct __init__
{
	__init__(int n = maxn - 1)
	{
		fac[0] = bin[0] = 1;
		REP(i, 1, n)
		{
			fac[i] = mul(fac[i-1], i);
			bin[i] = mul(bin[i-1], 2);
		}
		Inv[n] = inv(fac[n]);
		DEP(i, n - 1, 0) Inv[i] = mul(Inv[i + 1], i + 1);
	}
}__INIT__;

int R[maxn];
void NTT(int a[], int n, int flag)
{
	REP(i, 1, n - 1) if (i < R[i])
		swap(a[i], a[R[i]]);
	for (int i = 1; i < n; i <<= 1)
	{
		int wn = power_pow(3, (MOD - 1) / (i << 1));
		if (flag < 0) wn = inv(wn);
		for (int k = 0; k < n; k += i << 1)
			for (int l = 0, w = 1; l < i; l++, w = mul(w, wn))
			{
				int x(a[k + l]), y(mul(w, a[k + l + i]));
				a[k + l] = add(x, y);
				a[k + l + i] = sub(x, y);
			}
	}
	if (flag < 0)
	{
		const int Invn = inv(n);
		REP(i, 0, n - 1) a[i] = mul(a[i], Invn);
	}
}

i64 n;
int  k, l;
inline int A(int n, int m) {return mul(fac[n], Inv[n - m]);}
int z[maxn], nz[maxn], tmp[maxn], res[maxn];

#undef REP
namespace matthew
{
#define REP(i, a, b) for (int i = (a), _end_ = (b); i < _end_; ++i)
	typedef long long LL;

	const int oo = 0x3f3f3f3f;

	const int max0 = maxn;

	struct comp
	{
		double x, y;

		comp(): x(0), y(0) { }
		comp(const double &_x, const double &_y): x(_x), y(_y) { }

	};

	inline comp operator+(const comp &a, const comp &b) { return comp(a.x + b.x, a.y + b.y); }
	inline comp operator-(const comp &a, const comp &b) { return comp(a.x - b.x, a.y - b.y); }
	inline comp operator*(const comp &a, const comp &b) { return comp(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x); }
	inline comp conj(const comp &a) { return comp(a.x, -a.y); }

	const double PI = acos(-1);

	int N, L;

	comp w[max0 + 5];
	int bitrev[max0 + 5];

	void fft(comp *a, const int &n)
	{
		REP(i, 0, n) if (i < bitrev[i]) swap(a[i], a[bitrev[i]]);
		for (int i = 2, lyc = n >> 1; i <= n; i <<= 1, lyc >>= 1)
			for (int j = 0; j < n; j += i)
			{
				comp *l = a + j, *r = a + j + (i >> 1), *p = w;
				REP(k, 0, i >> 1)
				{
					comp tmp = *r * *p;
					*r = *l - tmp, *l = *l + tmp;
					++l, ++r, p += lyc;
				}
			}
	}

	inline void fft_prepare()
	{
		L = 0;
		for ( ; (1 << L) <= k + k; ++L);
		N = 1 << L;
		REP(i, 0, N) bitrev[i] = bitrev[i >> 1] >> 1 | ((i & 1) << (L - 1));
		REP(i, 0, N) w[i] = comp(cos(2 * PI * i / N), sin(2 * PI * i / N));
	}

	inline void conv(int *x, int *y, int *z)
	{
		const int n = k;
		const int Mod = ::MOD;
		static comp a[max0 + 5], b[max0 + 5];
		static comp dfta[max0 + 5], dftb[max0 + 5], dftc[max0 + 5], dftd[max0 + 5];

		REP(i, n + 1, N) a[i] = b[i] = comp(0, 0);
		REP(i, 0, n + 1) a[i] = comp(x[i] & 32767, x[i] >> 15);
		REP(i, 0, n + 1) b[i] = comp(y[i] & 32767, y[i] >> 15);
		fft(a, N), fft(b, N);
		REP(i, 0, N)
		{
			int j = (N - i) & (N - 1);
			static comp da, db, dc, dd;
			da = (a[i] + conj(a[j])) * comp(0.5, 0);
			db = (a[i] - conj(a[j])) * comp(0, -0.5);
			dc = (b[i] + conj(b[j])) * comp(0.5, 0);
			dd = (b[i] - conj(b[j])) * comp(0, -0.5);
			dfta[j] = da * dc;
			dftb[j] = da * dd;
			dftc[j] = db * dc;
			dftd[j] = db * dd;
		}
		REP(i, 0, N) a[i] = dfta[i] + dftb[i] * comp(0, 1);
		REP(i, 0, N) b[i] = dftc[i] + dftd[i] * comp(0, 1);
		fft(a, N), fft(b, N);
		REP(i, 0, n + n)
		{
			i64 da = (LL)(a[i].x / N + 0.5) % Mod;if (da < 0) da += Mod;
			i64 db = (LL)(a[i].y / N + 0.5) % Mod;if (db < 0) db += Mod;
			i64 dc = (LL)(b[i].x / N + 0.5) % Mod;if (dc < 0) dc += Mod;
			i64 dd = (LL)(b[i].y / N + 0.5) % Mod;if (dd < 0) dd += Mod;
			i64 res = (da + (db + dc << 15) % Mod + (dd << 30) % Mod) % Mod;
			if (res < 0) res += Mod;
			z[i] = res;
		}
	}

}
#undef REP
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
void solve(int res[], int n)
{
	if (n == 1)
	{
		copy(z, z + l, res);
		return;
	}
	solve(res, n / 2);
	copy(res, res + l, tmp);
	const int ccc = bin[n / 2];
	REP(i, 0, k)
		tmp[i] = mul(tmp[i], power_pow(ccc, i));
	matthew::conv(tmp, res, res);
	if (n & 1)
	{
		REP(i, k + 1, l - 1) res[i] = 0;
		REP(i, 0, k) res[i] = mul(res[i], bin[i]);
		matthew::conv(res, z, res);
//		NTT(res, l, 1);
//		REP(i, 0, l - 1) res[i] = mul(res[i], nz[i]);
	}
//	NTT(res, l, -1);
	REP(i, k + 1, l - 1) res[i] = tmp[i] = 0;
}

int main()
{
#ifdef CraZYali
	file("E");
#endif
	cin >> n >> k;
	if (n > k)
	{
		puts("0");
		return 0;
	}
	l = 1;
	while (l <= k + k) l <<= 1;
	matthew::fft_prepare();
	REP(i, 1, k)
		nz[i] = z[i] = Inv[i];
	REP(i, 1, l - 1)
		R[i] = (R[i >> 1] >> 1) | (i & 1 ? l >> 1 : 0);
	NTT(nz, l, 1);
	solve(res, n);
	int ans(0);
	REP(i, 1, k) ans = add(ans, mul(A(k, i), res[i]));
	cout << ans << endl;
	return 0;
}
