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
const int maxn = 1e5 + 10, MOD = 998244353;

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

int m, n, k;

inline int mul(int x, int y)
{
	long long res = 1ll * x * y;
	if (res >= MOD) res %= MOD;
	return res;
}
inline int add(int x, int y)
{
	int res = x + y;
	if (res >= MOD) res -= MOD;
	return res;
}
inline int nadd(int x, int y)
{
	int res = x - y;
	if (res < 0) res += MOD;
	return res;
}
int power_pow(int base, int b)
{
	int ans(1);
	while (b)
	{
		if (b & 1) ans = mul(ans, base);
		base = mul(base, base);
		b >>= 1;
	}
	return ans % MOD;
}
#define inv(x) power_pow(x, MOD - 2)

vector <int> DIF(vector <int> F)
{
	if (F.size() == 1) return vector<int>(1, 0);
	vector <int> res(F.size() - 1);
	REP(i, 0, res.size() - 1)
		res[i] = mul(i + 1, F[i + 1]);
	return res;
}
const int qaq = 1 << 18;
int Inv[qaq + 5];
struct __init__
{
	__init__(const int n = qaq)
	{
		Inv[0] = Inv[1] = 1;
		REP(i, 2, n) Inv[i] = nadd(MOD, mul(MOD / i, Inv[MOD % i]));
	}
}__INIT__;
vector <int> INT(vector <int> F)
{
	vector <int> res(F.size() + 1);
	res[0] = 0;
	REP(i, 1, F.size())
		res[i] = mul(Inv[i], F[i-1]);
	return res;
}

void NTT(vector <int> &a, int L, int flag)
{
	const int n = 1 << L;
	a.resize(n);
	vector <int> R(n);
	R[0] = 0;
	REP(i, 1, n - 1)
	{
		R[i] = (R[i >> 1] >> 1) | ((i & 1) << L - 1);
		if (i < R[i]) swap(a[i], a[R[i]]);
	}
	for (int i = 1; i < n; i <<= 1)
		for (int k = 0; k < n; k += i << 1)
		{
			int wn = power_pow(3, (MOD - 1) / (i << 1));
			if (flag < 0) wn = inv(wn);
			for (int l = 0, w = 1; l < i; l++, w = mul(w, wn))
			{
				int x(a[k + l]), y(mul(a[k + l + i], w));
				a[k + l] = add(x, y);
				a[k + l + i] = nadd(x, y);
			}
		}
	if (flag < 0)
		REP(i, 0, n - 1) a[i] = mul(a[i], Inv[n]);
}

vector <int> getInv(vector <int> f, int L)
{
	if (!L) return vector<int>(1, inv(f[0]));
	const int n = 1 << L;
	vector <int> tmp(f);tmp.resize(n >> 1);
	vector <int> A(n + n, 0), B(getInv(tmp, L - 1));
	f.resize(n);
	NTT(f, L + 1, 1);
	NTT(B, L + 1, 1);
	REP(i, 0, n + n - 1) A[i] = mul(B[i], nadd(2, mul(f[i], B[i])));
	NTT(A, L + 1, -1);
	A.resize(n);
	return A;
}

vector <int> f;

signed main()
{
#ifdef CraZYali
	file("4725");
#endif
	cin >> n;
	int l(1), L(0);
	while (l <= n + n) l <<= 1, L++;
	f.resize(l);
	REP(i, 0, n - 1) f[i] = read<int>();
	vector <int> Inv(getInv(f, L-1)), res(l,0);
	f = DIF(f);
	NTT(Inv, L, 1);
	NTT(f, L, 1);
	REP(i, 0, l - 1) res[i] = mul(f[i], Inv[i]);
	NTT(res, L, -1);
	res = INT(res);
	REP(i, 0, n-1) printf("%d%c", (res[i] + MOD) % MOD, i == n - 1 ? '\n' : ' ');
	return 0;
}
