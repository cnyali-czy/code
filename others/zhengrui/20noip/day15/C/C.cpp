#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <ctime>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <cstdio>
#define i64 long long
#define fi first
#define se second

using namespace std;
const int maxn = 1e6 + 10, MOD = 998244353, inv2 = MOD + 1 >> 1;

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
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, p[maxn], q[maxn], s[maxn];

int fac[maxn], Inv[maxn];
void init(int n)
{
	fac[0] = 1;
	REP(i, 1, n) fac[i] = 1ll * i * fac[i - 1] % MOD;
	Inv[n] = inv(fac[n]);
	DEP(i, n - 1, 0) Inv[i] = (i + 1ll) * Inv[i + 1] % MOD;
}

struct fenwick1
{
	int s[maxn], dfn[maxn], dfs_clock;
	fenwick1()
	{
		memset(s, 0, sizeof s);
		memset(dfn, 0, sizeof dfn);
		dfs_clock = 0;
	}
	void add(int x)
	{
		while (x <= n)
		{
			if (dfn[x] ^ dfs_clock) dfn[x] = dfs_clock, s[x] = 0;
			s[x]++;
			x += x & -x;
		}
	}
	int sum(int x)
	{
		int y = 0;
		while (x > 0)
		{
			if (dfn[x] == dfs_clock) y += s[x];
			x &= (x - 1);
		}
		return y;
	}
	void clear() {dfs_clock++;}
}A;
struct fenwick2
{
	int s[maxn];
	fenwick2()
	{
		memset(s, 0, sizeof s);
	}
	void add(int x, int y)
	{
		while (x <= n)
		{
			s[x] += y;
			if (s[x] >= MOD) s[x] -= MOD;
			x += x & -x;
		}
	}
	i64 sum(int x)
	{
		i64 y = 0;
		while (x > 0)
		{
			y += s[x];
			x &= (x - 1);
		}
		return y % MOD;
	}
}B;
i64 ykw;
int a[maxn], b[maxn], c[maxn];

int calc(int x[], int y[], int n)
{
	static pair <int, int> dog[maxn];
	REP(i, 1, n) dog[i] = make_pair(x[i], y[i]);
	sort(dog + 1, dog + 1 + n);
	A.clear();
	i64 res = 0;
	REP(i, 1, n)
	{
		res += A.sum(dog[i].se - 1);
		A.add(dog[i].se);
	}
	return res % MOD;
}

void work(int n)
{
	i64 tot = 0;
	tot += calc(a, b, n);
	tot += calc(a, c, n);
	tot += calc(b, c, n);
	tot -= n * (n - 1ll) / 2;
	tot = (tot % MOD + MOD) % MOD;
	ykw = tot * inv2 % MOD;
}

void gen()
{
	n = 1e6;
	REP(i, 1, n) p[i] = q[i] = i;
	random_shuffle(p + 1, p + 1 + n);
	random_shuffle(q + 1, q + 1 + n);
}

int main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();
	REP(i, 1, n) p[i] = read<int>();
	REP(i, 1, n) q[i] = read<int>();
	init(n);
	REP(i, 1, n) s[i] = 1;
	REP(i, 1, n) if (q[i] > 0) s[q[i]] = 0;
	REP(i, 1, n) s[i] += s[i - 1];
	int m = s[n], qaq = 1ll * fac[m] * inv2 % MOD;
	i64 ans = 0;
	REP(i, 1, n)
		if (q[i] == -1)
		{
			ans = (ans + 1ll * qaq * A.sum(p[i] - 1)) % MOD;
			A.add(p[i]);
			ans = (ans + 1ll * fac[m - 1] * B.sum(p[i] - 1)) % MOD;
		}
		else
		{
			B.add(p[i], m - s[q[i]]);
			ans = (ans + 1ll * s[q[i] - 1] * A.sum(p[i] - 1) % MOD * fac[m - 1]) % MOD;
		}
//	REP(i, 1, n) REP(j, i + 1, n) if (p[i] < p[j] && q[i] > 0 && q[j] > 0 && q[i] < q[j])
//		ykw++;
	int k = 0;
	REP(i, 1, n) if (q[i] > 0)
	{
		++k;
		a[k] = i;
		b[k] = p[i];
		c[k] = q[i];
	}
	work(k);
	ans = (ans + ykw % MOD * fac[m]) % MOD;
	cout << ans % MOD * Inv[m] % MOD << endl;
	cerr << clock() * 1. / CLOCKS_PER_SEC << endl;
	return 0;
}
