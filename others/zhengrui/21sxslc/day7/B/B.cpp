/*
	Problem:	B.cpp
	Time:		2021-02-28 20:07
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cassert>
#include <vector>
#include <iostream>
#include <cstdio>
#define i64 long long
#define u64 unsigned i64

using namespace std;
const int maxn = 10, maxl = 1e6 + 10, MOD = 1e9 + 7;

inline i64 power_pow(i64 base, int b)
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

	template <typename T>
inline T read()
{
	T ans = 0, ty = 1;
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') ty = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * ty;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int fac[maxn], invs[maxn], Invs[maxn];
void init(int n)
{
	fac[0] = invs[0] = Invs[0] = 1;
	fac[1] = invs[1] = Invs[1] = 1;
	REP(i, 2, n)
	{
		fac[i] = 1ll * fac[i - 1] * i % MOD;
		invs[i] = 1ll * invs[MOD % i] * (MOD - MOD / i) % MOD;
		Invs[i] = 1ll * Invs[i - 1] * invs[i] % MOD;
	}
}
inline i64 C(i64 n, i64 m)
{
	if (n < m || m < 0) return 0;
	if (n - m < m) m = n - m;
	i64 res = 1;
	REP(i, 1, m) (res *= (n - i + 1)) %= MOD;
	return res * Invs[m] % MOD;
}

#define poly vector <int>
inline int deg(const poly &f) {return (int)f.size() - 1;}
poly operator + (poly a, poly b)
{
	if (a.size() < b.size()) a.resize(b.size());
	REP(i, 0, deg(b)) (a[i] += b[i]) %= MOD;
	return a;
}
const u64 LIM = 17e18;
poly operator * (poly a, poly b)
{
	int n = deg(a), m = deg(b);
	static u64 res[66666];
	REP(i, 0, n) if (a[i]) REP(j, 0, m) if (b[j])
	{
		res[i + j] += (u64) a[i] * b[j];
		if (res[i + j] >= LIM) res[i + j] %= MOD;
	}
	a.resize(n + m + 1);
	REP(i, 0, n + m)
	{
		a[i] = res[i] % MOD;
		res[i] = 0;
	}
	return a;
}
void output(const poly &f)
{
	REP(i, 0, deg(f)) printf("%d%c", f[i], i == end_i ? '\n' : ' ' );
}
int n, l, y, x, k;

int a[maxn], m, ty;
i64 N, ans;
poly P(int x)
{
	poly res(x + 1, 0);
	res[0] = 1;res[x] = MOD - 1;
	return res;
}

poly Inv(poly f)
{
	int n = deg(f);
	const i64 iv = inv(f[0]);
	poly g(n + 1, 0);g[0] = iv;
	REP(i, 1, n)
	{
		i64 res = 0;
		REP(j, 0, i - 1) (res += 1ll * g[j] * f[i - j]) %= MOD;
		g[i] = (MOD - res) * iv % MOD;
	}
	return g;
}
poly Mod(poly f, const poly &g) // return f % g
{
	int n(deg(f)), m(deg(g));
	if (m > n) return f;
	const i64 Invs = inv(g[m]);
	DEP(i, n, m) if (f[i])
	{
		const i64 qaq = Invs * f[i] % MOD;
		REP(j, 0, m)
			f[j - m + i] = (f[j - m + i] - g[j] * qaq) % MOD;
	}
	f.resize(m);
	REP(i, 0, m - 1) if (f[i] < 0) f[i] += MOD;
	return f;
}
namespace far
{
	int n;
	poly g, rf;
	void init(poly f)
	{
		n = deg(f);
		g = Inv(f);
		rf.resize(n + 1);
		REP(i, 1, n) rf[i - 1] = f[n - i + 1];rf[n] = 1;
		assert(f[0] == 1);
	}
	int calc(i64 N)
	{
		if (N <= n) return g[N];
		N--;
		poly base(2, 0), xs(2, 0);base[1] = xs[1] = 1;
		while (N)
		{
			if (N & 1) xs = Mod(xs * base, rf);
			if (N > 1) base = Mod(base * base, rf);
			N >>= 1;
		}
		i64 ans = 0;
		REP(i, 0, deg(xs)) (ans += 1ll * xs[i] * g[i]) %= MOD;
		return ans;
	}
}

void calc()
{
//	REP(i, 1, m) printf("%d%c", a[i], i == end_i ? '\n' : ' ');
	i64 xs = 1;
	static int cnt[maxn];
	REP(i, 1, m) cnt[a[i]]++, (xs *= invs[a[i]]) %= MOD;
	REP(i, 1, n) (xs *= Invs[cnt[i]]) %= MOD, cnt[i] = 0;
	poly down(1, 1);
	REP(i, 1, m)
	{
		int x = a[i];
		down = down * P(x);
		if (x % (k + 1) == 0) (xs *= (MOD - k)) %= MOD;
	}
	poly up = down;//need ^ (x + 1)
	if (ty >= 2) down = down * (P(1) * P(1));
	far :: init(down);
	i64 res = 0;
	REP(i, 0, deg(up))
	{
		int vi = up[i];
		i64 ri = i * (x + 1ll);
		if (ri > N) break;
		(res += 1ll * vi * (far :: calc(N - ri))) %= MOD;
	}
	(ans += res * xs) %= MOD;
}
void dfs(int x, int lst = 1)
{
	if (x == n - 1) calc();
	else
	{
		++m;
		REP(i, lst, n - 1 - x)
		{
			a[m] = i;
			dfs(x + i, i);
		}
		m--;
	}
}

int f(i64 x, int T)
{
	ans = 0;
	ty = T;
	N = x;
	dfs(0);
	return ans;
}
//0 : origin ~ useless now
//1 : sum ~ useless now
//2 : sum of sum

/*
inline i64 s(i64 N)
{
	static map <i64, int> mem;
	if (mem[N]) return mem[N];
	return mem[N] = f(N, 1);
}
*/
inline i64 s2(i64 N) {return f(N, 2);}
/*
inline i64 ss(i64 N)
{
	return ((N + 1) % MOD * s(N) - s2(N) + MOD) % MOD;
}
*/

int main()
{
#ifdef CraZYali
	file("B");
#endif
	cin >> n >> l >> y >> x >> k;
	init(n);
/*	
	REP(i, 0, 20)
		printf("%d%c", f(i, 0), i == end_i ? '\n' : ' ');
	REP(i, 0, 20)
		printf("%d%c", f(i, 1), i == end_i ? '\n' : ' ');
	REP(i, 0, 20)
		printf("%d%c", f(i, 2), i == end_i ? '\n' : ' ');
		*/

	i64 sum = 0;
	REP(i, 0, (n - 1) / (k + 1))
	{
		i64 res = C(x + 1, i) * C(n + x - i * (k + 1ll) - 1, x) % MOD;
		if (i & 1) res = MOD - res;
		sum += res;
	}
	sum %= MOD;
	i64 ans = (l - y + 1) * sum - (s2(l) - s2(y - 1));
	cout << (ans % MOD + MOD) % MOD << endl;
	return 0;
}
