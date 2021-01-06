/*
	Problem:	qaq.cpp
	Time:		2020-06-16 20:53
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cstdlib>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;
const int MOD = 985661441, inv3 = (MOD + 1) / 3, inv2 = MOD + 1 >> 1;
#define poly vector <int> 
#define i64 long long
#define ui64 unsigned i64

i64 power_pow(i64 base, int b)
{
	i64 ans = 1;
	while (b)
	{
		if (b & 1) (ans *= base) %= MOD;
		(base *= base) %= MOD;
		b >>= 1;
	}
	return ans;
}
#define inv(x) power_pow(x, MOD - 2)

const int maxn = 1 << 22;
ui64 NTTtmp[maxn];
int R[maxn];
void NTT(poly &a, int n, int flag)
{
	if (a.size() ^ n) a.resize(n);
	if (flag < 0) reverse(a.begin() + 1, a.end());
	static int *w[30], pool[maxn << 1 | 10];
	static bool vis[30];
	w[0] = pool;
	REP(i, 0, n - 1)
	{
		R[i] = (R[i >> 1] >> 1) | ((i & 1) ? (n >> 1) : 0);
		if (i < R[i]) swap(a[i], a[R[i]]);
	}
	REP(i, 0, n - 1) NTTtmp[i] = a[i];
	bool fff = (flag > 0);
	for (int i = 1, ccc = 0; i < n; i <<= 1, ccc++)
	{
		if (!vis[ccc])
		{
			vis[ccc] = 1;
			const i64 wn = power_pow(3, (MOD - 1) >> ccc + 1);
			if (i < maxn) w[ccc + 1] = w[ccc] + i;
			w[ccc][0] = 1;
			REP(j, 1, i - 1) w[ccc][j] = w[ccc][j - 1] * wn % MOD;
		}
		for (int k = 0; k < n; k += i + i)
			for (int l = 0; l < i; l++)
			{
				ui64 x(NTTtmp[k + l]), y(NTTtmp[k + l + i] * w[ccc][l] % MOD);
				NTTtmp[k + l] = x + y;
				NTTtmp[k + l + i] = MOD + x - y;
			}
	}
	REP(i, 0, n - 1) a[i] = NTTtmp[i] % MOD;
	if (flag < 0)
	{
		const int invn = inv(n);
		REP(i, 0, n - 1) a[i] = 1ll * a[i] * invn % MOD;
	}
}
inline int deg(const poly &a) {return a.size() - 1;}
inline poly operator * (poly a, poly b)
{
	int l = 1, n = deg(a), m = deg(b);
	while (l <= n + m) l <<= 1;
	NTT(a, l, 1);NTT(b, l, 1);
	REP(i, 0, l - 1) a[i] = 1ll * a[i] * b[i] % MOD;
	NTT(a, l, -1);
	a.resize(n + m + 1);
	return a;
}
void output(poly a)
{
	REP(i, 0, (int)a.size() - 1) printf("%d%c", a[i], i == end_i ? '\n' : ' ');
}
	template <typename T>
inline T read()
{
	T ans = 0, flag = 1;
	char c = getchar();
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

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int invs[maxn], last, Invs[maxn], fac[maxn];
void prepare(int n)
{
	if (!last)
	{
		invs[0] = invs[1] = 1;
		Invs[0] = Invs[1] = 1;
		fac[0] = fac[1] = 1;
		last = 1;
	}
	if (last < n)
	{
		REP(i, last + 1, n)
		{
			invs[i] = 1ll * (MOD - MOD / i) * invs[MOD % i] % MOD;
			Invs[i] = 1ll * Invs[i - 1] * invs[i] % MOD;
			fac[i] = 1ll * fac[i - 1] * i % MOD;
		}
		last = n;
	}
}
poly f, a;
void cdq(int l, int r)
{
	if (r - l + 1 <= 128)
	{
		REP(i, l, r)
		{
			if (!i) a[i] = 1;
			else a[i] = 1ll * a[i] * invs[i] % MOD;
			REP(j, i + 1, r) a[j] = (a[j] + 1ll * a[i] * f[j - i]) % MOD;
		}
		return;
	}
	int mid = l + r >> 1;
	cdq(l, mid);
	int len = 1;
	while (len <= r - l + 1) len <<= 1;
	poly A(mid - l + 1), B(r - l + 1);
	REP(i, l, mid)		A[i - l] = a[i];
	REP(i, 0, r - l)	B[i] = f[i];
	NTT(A, len, 1);NTT(B, len, 1);
	REP(i, 0, len - 1) A[i] = 1ll * A[i] * B[i] % MOD;
	NTT(A, len, -1);
	REP(i, mid + 1, r) (a[i] += A[i - l]) %= MOD;
	cdq(mid + 1, r);
}
poly Exp_log2(const poly &f)
{
	int n = deg(f);
	prepare(n);
	::f.resize(n + 1);
	a.clear();a.resize(n + 1);
	REP(i, 0, n) ::f[i] = 1ll * i * f[i] % MOD;
	cdq(0, n);
	return a;
}
poly move(poly f)
{
	DEP(i, deg(f), 1) f[i] = f[i - 1];
	f[0] = 0;
	return f;
}

int main()
{
#ifdef CraZYali
	file("1728");
#endif
	poly f[4];
	const int N = 2e6;
	f[1].resize(N + 1);
	prepare(N);
	REP(i, 0, N) f[1][i] = Invs[i];
	REP(i, 2, 3)
	{
		f[i] = f[i - 1];
		f[i].resize(N / i + 1);
		f[i] = Exp_log2(move(f[i]));
	}
	REP(Case, 1, read<int>())
	{
		int n = read<int>(), k = read<int>();
		printf("Case #%d: %lld\n", Case, 1ll * fac[n] * f[k][n] % MOD);
	}
	return 0;
}
