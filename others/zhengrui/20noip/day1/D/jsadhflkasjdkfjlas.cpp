#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cstdio>
#define i64 long long
using namespace std;
const int maxn = 5000 + 10, MOD = 1e9 + 7, inf = 1e9;

int bg[maxn], ne[maxn], to[maxn], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
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

int fac[maxn], invs[maxn], Inv[maxn];
void init(int n)
{
	fac[0] = invs[0] = Inv[0] = 1;
	fac[1] = invs[1] = Inv[1] = 1;
	REP(i, 2, n)
	{
		fac[i] = 1ll * fac[i - 1] * i % MOD;
		invs[i] = 1ll * invs[MOD % i] * (MOD - MOD / i) % MOD;
		Inv[i] = 1ll * invs[i] * Inv[i - 1] % MOD;
	}
}
inline i64 C(int n, int m) {return n < m || m < 0 ? 0 : 1ll * fac[n] * Inv[n - m] % MOD * Inv[m] % MOD;}

int n, m;
int a[maxn], p[maxn], fa[maxn];
bool used[maxn];

int siz[maxn], dp[maxn];
void dfs0(int x)
{
	siz[x] = 1;
	dp[x] = 1;
	for (int i = bg[x]; i; i = ne[i])
	{
		dfs0(to[i]);
		siz[x] += siz[to[i]];
		dp[x] = 1ll * dp[x] * dp[to[i]] % MOD;
	}
	dp[x] = 1ll * dp[x] * invs[siz[x]] % MOD;
}

int rule[maxn], k, cur;
void dfs(int x)
{
	k++;
	for (int i = bg[x]; i; i = ne[i])
	{
		int y = to[i];
		if (y <= m) continue;
		dfs(y);
	}
}

int count(int M)
{
	REP(i, 2, M)
		if (p[fa[i]] > p[i])
		{
			DEBUG;
			return 0;
		}
	static int gd[maxn];
	REP(i, 1, n) gd[i] = 1;
	REP(i, 1, M) gd[p[i]] = 0;
	DEP(i, n, 1) gd[i] += gd[i + 1];
	REP(i, 1, n) rule[i] = 0;
	REP(i, 1, M) rule[p[i]] = i;
	i64 res = 1, ard = 0;
	DEP(v, n, 1) if (rule[v])
	{
		int x = rule[v];
		int need = 0;
		for (int i = bg[x]; i; i = ne[i])
		{
			int y = to[i];
			if (y <= M) continue;
			need += siz[y];
			res = res * dp[y] % MOD;
		}
		if (gd[v] - ard < need) return 0;
		res = res * fac[gd[v] - ard] % MOD;
		ard += need;
	}
	return res;
}

int main()
{
#ifdef CraZYali
	file("D");
#endif
	n = read<int>();init(n);
	REP(i, 2, n) add(fa[i] = read<int>(), i);
	dfs0(1);
	REP(i, 1, n) a[i] = read<int>();
	bool good = 0;
	REP(i, 1, n)
		DEP(k, good ? n : a[i], 1) if (!used[k])
		{
			p[i] = k;
			if (count(i))
			{
				used[k] = 1;
				good |= (k < a[i]);
				break;
			}
			p[i] = 0;
		}
	REP(i, 1, n) printf("%d%c", p[i], i == end_i ? '\n' : ' ' );

	i64 rnk = 0;
	REP(i, 1, n) used[i] = 0;
	REP(i, 1, n)
	{
		REP(j, 1, p[i] - 1) if (!used[j])
		{
			used[j] = 1;
			swap(p[i], j);
			rnk += count(i);
			cerr << count(i) << endl;
			swap(p[i], j);
			used[j] = 0;
		}
		used[p[i]] = 1;
	}
	cout << (rnk + 1) % MOD << endl;
	return 0;
}
