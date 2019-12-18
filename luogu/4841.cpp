#define REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;
const int MOD = 1004535809, maxn = 1 << 18, inv2 = MOD + 1 >> 1;

inline int mul(int x, int y)
{
	register long long res(1ll * x * y);
	if (res >= MOD) res %= MOD;
	return res;
}
inline int add(int x, int y)
{
	register int res(x + y);
	if (res >= MOD) res -= MOD;
	return res;
}
inline int sub(int x, int y)
{
	register int res(x - y);
	if (res < 0) res += MOD;
	return res;
}

int power_pow(int base, long long b)
{
	int ans(1);
	while (b)
	{
		if (b & 1) ans = mul(ans, base);
		base = mul(base, base);
		b >>= 1;
	}
	return ans;
}
#define inv(x) power_pow(x, MOD - 2)

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

int R[maxn];
void NTT(int a[], int L, int flag)
{
	const int n = 1 << L;
	REP(i, 1, n - 1)
		if (i < R[i]) swap(a[i], a[R[i]]);
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
		const int invN(inv(n));
		REP(i, 0, n - 1) a[i] = mul(a[i], invN);
//		int l(0), r(n - 1);
//		while (l < r) swap(a[l++], a[r--]);
	}
}

int tmp[maxn];
void getInv(int F[], int B[], int L)
{
	if (L == -1) return B[0] = inv(F[0]), void();
	const int n(1 << L), N(1 << L + 1);
	getInv(F, B, L - 1);
	copy(F, F + n, tmp);
	REP(i, 1, N - 1) R[i] = (R[i >> 1] >> 1) | ((i & 1) ? n : 0);
	NTT(tmp, L + 1, 1);
	NTT(B, L + 1, 1);
	REP(i, 0, N - 1) B[i] = mul(B[i], sub(2, mul(B[i], tmp[i])));
	NTT(B, L + 1, -1);
	REP(i, n, N - 1) B[i] = 0;
}

int n, a[maxn], Inv[maxn];
inline int C2(int n) {return mul(mul(n, n - 1), inv2);}
signed main()
{
#ifdef CraZYali
	file("4841");
#endif
	cin >> n;
	int len(1), L(0);
	while (len <= n)
	{
		len <<= 1;
		L++;
	}
	int fac(1);
	REP(i, 0, len - 1)
	{
		if (i) fac = mul(fac, i);
		a[i] = mul(power_pow(2, 1ll * i * (i - 1) / 2), inv(fac));
	}
	getInv(a, Inv, L);
	REP(i, 0, len - 1)
		a[i] = mul(a[i + 1], i + 1);
	NTT(Inv, L + 1, 1);
	NTT(a, L + 1, 1);
	REP(i, 0, len + len - 1) a[i] = mul(a[i], Inv[i]);
	NTT(a, L + 1, -1);
	DEP(i, len - 1, 1) a[i] = mul(a[i-1], inv(i));
	a[0] = 0;
	fac = 1;
	REP(i, 2, n) fac = mul(fac, i);
	cout << mul(fac, a[n]) << endl;
	return 0;
}
