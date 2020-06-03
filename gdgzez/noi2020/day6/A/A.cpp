#define REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>
#include <random>

using namespace std;
const int maxn = 1e5 + 10, MOD = 998244353, Inv2 = MOD + 1 >> 1;
#define i64 long long
inline int add(int x, int y) {x += y;return x >= MOD ? x - MOD : x;}
inline int sub(int x, int y) {x -= y;return x <    0 ? x + MOD : x;}
inline i64 mul(i64 x, int y) {x *= y;return x >= MOD ? x % MOD : x;}
inline void inc(int &x, int y) {x += y;if (x >= MOD) x -= MOD;}
inline void dec(int &x, int y) {x -= y;if (x <    0) x += MOD;}
int power_pow(i64 base, int b)
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

int bg[maxn], ne[maxn << 1], to[maxn << 1], e;

inline void Add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

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
inline int min(int x, int y) {if (x < y) return x;return y;}
#define poly vector <int>
#define i64 long long
#define maxn maxN
const int maxN = 1 << 18;

inline int deg(const poly &A) {return A.size() - 1;}
unsigned i64 NTTtmp[maxn];
int R[maxn], lastRN;
vector <int> w[30][2];
struct __init__
{
	__init__()
	{
		REP(i, 0, 18)
		{
			int Wn = power_pow(3, (MOD - 1) / (1 << i + 1));
			int InvWn = inv(Wn);
			i64 w0 = 1, w1 = 1;
			REP(j, 0, (1 << i) - 1)
			{
				w[i][0].emplace_back(w0);(w0 *= Wn) %= MOD;
				w[i][1].emplace_back(w1);(w1 *= InvWn) %= MOD;
			}
		}
	}
}__INIT__;
void NTT(poly &a, int n, int flag)
{
	if (a.size() ^ n) a.resize(n);
	bool fff = (flag > 0);
	if (lastRN ^ n)
	{
		lastRN = n;
		REP(i, 1, n - 1) R[i] = (R[i >> 1] >> 1) | (i & 1 ? n >> 1 : 0);
	}
	REP(i, 1, n - 1) if (i < R[i]) swap(a[i], a[R[i]]);
	REP(i, 0, n - 1) NTTtmp[i] = a[i];
	for (int ccc = 0, i = 2, i2 = 1; i <= n; i <<= 1, i2 <<= 1, ccc++)
		for (int k = 0; k < n; k += i)
			REP(l, 0, i2 - 1)
			{
				unsigned i64 x(NTTtmp[k + l]), y(1ll * w[ccc][fff][l] * NTTtmp[k + l + i2] % MOD);
				NTTtmp[k + l] = x + y;
				NTTtmp[k + l + i2] = MOD + x - y;
			}
	REP(i, 0, n - 1)
	{
		a[i] = NTTtmp[i] % MOD;
		if (a[i] < 0) a[i] += MOD;
	}
	if (flag < 0)
	{
		const int invn = inv(n);
		REP(i, 0, n - 1) a[i] = 1ll * a[i] * invn % MOD;
	}
}
inline poly operator * (poly a, poly b)
{
	int n(deg(a)), m(deg(b));
	int l = 1;
	while (l <= n + m) l <<= 1;
	NTT(a, l, 1);NTT(b, l, 1);
	REP(i, 0, l - 1) a[i] = 1ll * a[i] * b[i] % MOD;
	NTT(a, l, -1);
	a.resize(n + m + 1);
	return a;
}
inline poly&operator *=(poly&a, poly b)
{
	int n(deg(a)), m(deg(b));
	int l = 1;
	while (l <= n + m) l <<= 1;
	NTT(a, l, 1);NTT(b, l, 1);
	REP(i, 0, l - 1) a[i] = 1ll * a[i] * b[i] % MOD;
	NTT(a, l, -1);
	a.resize(n + m + 1);
	return a;
}
#undef maxn

int n, k;

int fac[maxn], iinv[maxn];
void init()
{
	fac[0] = 1;
	REP(i, 1, k) fac[i] = 1ll * fac[i - 1] * i % MOD;
	iinv[k] = inv(fac[k]);
	DEP(i, k - 1, 0) iinv[i] = (i + 1ll) * iinv[i + 1] % MOD;
}
inline int A(int n, int m) {return 1ll * fac[n] * iinv[n - m] % MOD;}

poly need[maxn];
int siz[maxn], fa[maxn], ssr[maxn], N;
poly cdq(int l, int r)
{
	if (l == r)
	{
		poly res(2);
		res[0] = 1;res[1] = ssr[l];
		return res;
	}
	int mid = l + r >> 1;
	return cdq(l, mid) * cdq(mid + 1, r);
}
void dfs(int x)
{
	siz[x] = 1;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa[x])
	{
		fa[to[i]] = x;
		dfs(to[i]);
		siz[x] += siz[to[i]];
	}
	N = 0;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa[x])
		ssr[++N] = siz[to[i]];
	need[x].resize(N + 1);
	if (!N) need[x][0] = 1;
	else need[x] = cdq(1, N);
}
i64 get(poly a)
{
	i64 res = 0;
	REP(i, 0, min((int)a.size() - 1, k)) res += 1ll * iinv[k - i] * a[i] % MOD;
	return res % MOD * fac[k] % MOD;
}
poly mmul(poly f, int a)
{
	int df = deg(f), dr = df + 1;
	poly res(dr + 1);
	res[0] = f[0];
	REP(i, 1, dr) res[i] = ((i <= df ? f[i] : 0) + 1ll * f[i - 1] * a) % MOD;
	return res;
}
poly ddiv(poly f, int a)
{
	int df = deg(f), dr = df - 1;
	poly res(dr + 1);
	res[0] = f[0];
	REP(i, 1, dr) res[i] = (MOD + f[i] - 1ll * a * res[i - 1] % MOD) % MOD;
	return res;
}
void output(poly f) {for (auto i : f) cout << i << ' ';cout << '\n';}
int mem[maxn];
i64 Ans;

int dp[maxn], sm[maxn];

unordered_map <int, int> shit[maxn];
void dfs1(int x)
{
	i64 res = 0, s2 = 0, New = 0, s1 = 0;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa[x])
	{
		dfs1(to[i]);
		s1 += sm[to[i]];
		New -= 1ll * sm[to[i]] * sm[to[i]] % MOD;
		res += dp[to[i]];
	}
	s1 %= MOD;
	(New += s1 * s1) %= MOD;
	dp[x] = (New * Inv2 + res) % MOD;
	sm[x] = (mem[x] + s1) % MOD;
	if (x != 1)
	{
		int f = fa[x];
		if (!shit[f].count(siz[x]))
			shit[f][siz[x]] = get(ddiv(need[f], siz[x]));
		Ans += 1ll * sm[x] * shit[f][siz[x]] % MOD;
	}
}

int main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();k = read<int>();
	if (k == 1)
	{
		cout << n * (n - 1ll) / 2 % MOD << endl;
		return 0;
	}
	init();
	REP(i, 2, n)
	{
		int x(read<int>()), y(read<int>());
		Add(x, y);Add(y, x);
	}
	dfs(1);
	REP(i, 1, n) mem[i] = get(need[i]);
	REP(i, 1, n) need[i] = mmul(need[i], n - siz[i]);
	dfs1(1);
	cout << (Ans + dp[1]) % MOD << endl;
	return 0;
}
