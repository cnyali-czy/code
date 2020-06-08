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
#include <random>

using namespace std;
const int maxn = 1e5 + 10, maxm = 2e5 + 10;

int bg[maxn], ne[maxm << 1], to[maxm << 1], e = 1;
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

int w[maxn], p[maxn], q[maxn];

const int MOD = 998244353, Inv2 = MOD + 1 >> 1;
inline int add(int x, int y) {x += y;return x >= MOD ? x - MOD : x;}
inline int sub(int x, int y) {x -= y;return x <    0 ? x + MOD : x;}
inline void inc(int &x, int y) {x += y;if (x >= MOD) x -= MOD;}
inline void dec(int &x, int y) {x -= y;if (x <    0) x += MOD;}
namespace polynomial
{
#define poly vector <int>
#define i64 long long
	const int maxn = 1 << 21;
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

	inline int deg(const poly &A) {return A.size() - 1;}
	unsigned i64 NTTtmp[maxn];
	int R[maxn], lastRN;
	vector <int> w[30][2];
	struct __init__
	{
		__init__()
		{
			REP(i, 0, 19)
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
	inline poly operator + (poly a, poly b)
	{
		if (a.size() < b.size()) swap(a, b);
		REP(i, 0, (int)b.size() - 1) inc(a[i], b[i]);
		return a;
	}
	inline poly operator - (poly a, poly b)
	{
		if (a.size() < b.size()) a.resize(b.size());
		REP(i, 0, (int)a.size() - 1) dec(a[i], b[i]);
		return a;
	}
	inline poly operator * (int k, poly a)
	{
		for (auto &i : a) i = 1ll * i * k % MOD;
		return a;
	}
	inline poly operator * (poly a, int k) {return k * a;}
	inline poly operator / (poly a, int k) {return inv(k) * a;}
	poly cdq(int l, int r)
	{
		if (l == r)
		{
			poly res(3);
			res[0] = ::w[l];
			res[1] = p[l];
			res[2] = q[l];
			return res;
		}
		int mid = l + r >> 1;
		return cdq(l, mid) * cdq(mid + 1, r);
	}
}

int n, m, a[maxn];

int dfn[maxn], low[maxn], dfs_clock, f[maxn][2][2];
vector <int> v[maxn];
void dfs(int x, int fr)
{
	dfn[x] = low[x] = ++dfs_clock;
	int Min = n + 1, pos = 0;
	for (int i = bg[x]; i; i = ne[i]) if (i ^ fr ^ 1)
		if (!dfn[to[i]])
		{
			dfs(to[i], i);
			chkmin(low[x], low[to[i]]);
			if (low[to[i]] < dfn[x]) pos = to[i];
			else v[x].emplace_back(to[i]);
		}
		else
		{
			chkmin(low[x], dfn[to[i]]);
			chkmin(Min, dfn[to[i]]);
		}
	int N = 0;
	for (auto y : v[x])
	{
		++N;
		w[N] = f[y][0][0];
		p[N] = f[y][1][0];
		q[N] = 0;
		if (low[y] == dfn[x])
		{
			(p[N] += f[y][0][1]) %= MOD;
			q[N] = f[y][1][1];
		}
	}
	poly res(1, 1);
	if (N) res = polynomial :: cdq(1, N);
//	printf("%d %d\n", x, N + N);
//	for (auto i : res) cout << i << ' ' ;cout<<endl;
	long long tmp = 0, tmp1 = 0, tmp2 = 0;
	REP(i, 0, min(a[x] - 2, N + N)) tmp2 += res[i];
	tmp1 = tmp2;
	if (a[x] && a[x] <= N + N + 1) tmp1 += res[a[x] - 1];
	tmp = tmp1;
	if (a[x] <= N + N) tmp += res[a[x]];
	tmp %= MOD;tmp1 %= MOD;tmp2 %= MOD;
	if (Min == low[x])
	{
		f[x][0][0] = tmp2;
		f[x][0][1] = tmp1;
		f[x][1][0] = tmp1;
		f[x][1][1] = tmp;
	}
	else if (low[x] < dfn[x])
	{
		f[x][0][1] = (tmp2 * f[pos][1][1] + tmp1 * f[pos][0][1]) % MOD;
		f[x][1][1] = (tmp1 * f[pos][1][1] + tmp  * f[pos][0][1]) % MOD;
		f[x][0][0] = (tmp1 * f[pos][0][0] + tmp2 * f[pos][1][0]) % MOD;
		f[x][1][0] = (tmp1 * f[pos][1][0] + tmp  * f[pos][0][0]) % MOD;
	}
	else f[x][0][0] = tmp1, f[x][1][0] = tmp;
}

int main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();m = read<int>();
	while (m--)
	{
		int x(read<int>()), y(read<int>());
		Add(x, y);Add(y, x);
	}
	REP(i, 1, n) a[i] = read<int>();
	dfs(1, 0);
	cout << f[1][1][0] << endl;
	return 0;
}
