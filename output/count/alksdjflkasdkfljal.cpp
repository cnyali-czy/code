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
const int MOD = 998244353, inv3 = (MOD + 1) / 3, inv2 = MOD + 1 >> 1;
#define poly vector <int> 
#define i64 long long
#define ui64 unsigned i64

i64 power_pow(i64 base, i64 b)
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

const int maxn = 1 << 21;
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

int invs[maxn], fac[maxn], Invs[maxn], last;
poly Ln(poly f)
{
	int n = deg(f);
	poly a(n + 1, 0);
	REP(i, 0, n - 1)
	{
		i64 res = (i + 1ll) * f[i + 1];
		REP(j, 0, i - 1) res = (res - (j + 1ll) * a[j + 1] % MOD * f[i - j]) % MOD;
		res %= MOD;if (res < 0) res += MOD;
		a[i + 1] = res * invs[i + 1] % MOD;
	}
	return a;
}

#define poly2D vector <poly>

void NTT2D(poly2D &a, int n, int m, int flag)
{
	a.resize(n);
	for (auto &i : a) NTT(i, m, flag);
	static poly b;
	b.resize(n);
	REP(i, 0, m - 1)
	{
		REP(j, 0, n - 1) b[j] = a[j][i];
		NTT(b, n, flag);
		REP(j, 0, n - 1) a[j][i] = b[j];
	}
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

int n;

int main()
{
	file("count");
	n = read<int>();
	int k = read<int>();
	poly2D f(n);
	REP(i, 0, n - 1)
	{
		f[i].resize(k);
		REP(j, 0, k - 1) f[i][j] = read<int>();
	}
	NTT2D(f, n, k, 1);
	REP(i, 0, n - 1)
		REP(j, 0, k - 1) printf("%d%c", f[i][j], j == end_j ? '\n' : ' ');
	srand(233);
	REP(i, 0, n - 1) REP(j, 0, k - 1)
	{
		int x = rand();
		f[i][j] = 1ll * f[i][j] *x % MOD;
		cerr<<x<<endl;
	}
	NTT2D(f, n, k, -1);
	REP(i, 0, n - 1)
		REP(j, 0, k - 1) printf("%d%c", f[i][j], j == end_j ? '\n' : ' ');

	/*
	fac[0] = invs[0] = Invs[0] = 1;
	fac[1] = invs[1] = Invs[1] = 1;
	REP(i, 2, n)
	{
		fac[i] = 1ll * fac[i - 1] * i % MOD;
		invs[i] = 1ll * (MOD - MOD / i) * invs[MOD % i] % MOD;
		Invs[i] = 1ll * invs[i] * Invs[i - 1] % MOD;
	}
	poly f(n + 1, 0);
	REP(i, 0, n)
		f[i] = power_pow(2, i * (i - 1ll) / 2) * Invs[i] % MOD;
	f = Ln(f);
	cout << 1ll * fac[n] * f[n] % MOD << endl;
	*/
	return 0;
}
