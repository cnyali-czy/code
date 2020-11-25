/*
	Problem:	E.cpp
	Time:		2020-11-25 15:49
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 2e5 + 10, MOD = 1e9 + 7;

int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
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
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

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

int n, a[maxn];

vector <int> Div[maxn];
int prime[maxn], phi[maxn], p_cnt, mu[maxn], f[maxn], invs[maxn];
bool notp[maxn];
void init(int n)
{
	invs[0] = invs[1] = 1;
	REP(i, 2, n)
		invs[i] = 1ll * (MOD - MOD / i) * invs[MOD % i] % MOD;
	phi[1] = mu[1] = 1;
	REP(i, 2, n)
	{
		if (!notp[i])
		{
			phi[prime[++p_cnt] = i] = i - 1;
			mu[i] = MOD - 1;
		}
		REP(j, 1, p_cnt)
		{
			int tmp = i * prime[j];
			if (tmp > n) break;
			notp[tmp] = 1;
			if (i % prime[j])
			{
				phi[tmp] = phi[i] * (prime[j] - 1);
				mu[tmp] = MOD - mu[i];
			}
			else
			{
				phi[tmp] = phi[i] * prime[j];
				break;
			}
		}
	}
	REP(i, 1, n)
	{
		const i64 U = 1ll * i * invs[phi[i]] % MOD;
		REP(j, 1, n / i)
		{
			Div[i * j].emplace_back(i);
			f[i * j] = (f[i * j] + 1ll * U * mu[j]) % MOD;
		}
	}
}
i64 ans;
int siz[maxn], Max[maxn], allnode, rt;
bool vis[maxn];
void findrt(int x, int fa = 0)
{
	siz[x] = 1;Max[x] = 0;
	for (int i = bg[x]; i; i = ne[i]) if (!vis[to[i]] && to[i] ^ fa)
	{
		findrt(to[i], x);
		siz[x] += siz[to[i]];
		Max[x] = max(Max[x], siz[to[i]]);
	}
	Max[x] = max(Max[x], allnode - siz[x]);
	if (Max[x] < Max[rt] || !rt) rt = x;
}
int dep[maxn], stk[maxn], top;
void qaq(int x, int fa = 0)
{
	stk[++top] = x;
	for (int i = bg[x]; i; i = ne[i]) if (!vis[to[i]] && to[i] ^ fa)
	{
		dep[to[i]] = dep[x] + 1;
		qaq(to[i], x);
	}
}
int calc(int x, int d)
{
	dep[x] = d;
	top = 0;
	qaq(x);
	static int cnt1[maxn], cnt2[maxn], Stk[maxn];
	static bool Vis[maxn];
	int Top = 0;
	REP(i, 1, top)
	{
		int u = stk[i], A = a[u];
		for (int j : Div[A])
		{
			if (!Vis[j]) Vis[Stk[++Top] = j] = 1;
			cnt1[j] = (cnt1[j] + phi[A]) % MOD;
			cnt2[j] = (cnt2[j] + 1ll * phi[A] * dep[u]) % MOD;
		}
	}
	i64 res = 0;
	REP(i, 1, Top)
	{
		int T = Stk[i];
		res = (res + 1ll * f[T] * cnt1[T] % MOD * cnt2[T]) % MOD;
	}
	REP(i, 1, Top)
		Vis[Stk[i]] = cnt1[Stk[i]] = cnt2[Stk[i]] = 0;
	return res;
}
void dfs(int x)
{
	vis[x] = 1;
	ans += calc(x, 0);
	for (int i = bg[x]; i; i = ne[i]) if (!vis[to[i]])
	{
		ans += MOD - calc(to[i], 1);
		allnode = siz[to[i]];
		rt = 0;
		findrt(to[i]);
		dfs(rt);
	}
}

int main()
{
#ifdef CraZYali
	file("E");
#endif
	n = read<int>();
	init(n);
	REP(i, 1, n) a[i] = read<int>();
	REP(i, 2, n)
	{
		int x = read<int>(), y = read<int>();
		add(x, y);add(y, x);
	}
	allnode = n;
	findrt(1);
	dfs(rt);
	ans = ans % MOD * 2 % MOD;
	ans = ans * invs[n] % MOD * invs[n - 1] % MOD;
	cout << ans << endl;
	return 0;
}
