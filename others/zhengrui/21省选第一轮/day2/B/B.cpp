#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <vector>
#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 1e5 + 10, MOD = 998244353;

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

inline int read()
{
	char c = getchar();
	while (!isdigit(c)) c = getchar();
	int res = 0;
	while (isdigit(c)) res = res * 10 + (c - 48), c = getchar();
	return res;
}

int n, q;
vector <int> G[maxn];

int fa[maxn], f[maxn][2];

void dfs(int u)
{
	f[u][0] = G[u].size();f[u][1] = 0;
	i64 res = 0;
	for (int v : G[u]) if (v ^ fa[u])
	{
		fa[v] = u;
		dfs(v);
		res += 1 + f[v][0];
		f[u][1] = (f[u][1] + 2ll * f[v][0] + f[v][1]) % MOD;
		(f[u][0] += f[v][0]) %= MOD;
	}
	f[u][1] = (f[u][1] + res * 2 % MOD * f[u][0]) % MOD;
}

int dfn[maxn], dfs_clock, back[maxn], siz[maxn];
void dfs0(int x, int fa = 0)
{
	siz[x] = 1;
	back[dfn[x] = ++dfs_clock] = x;
	for (int y : G[x]) if (y ^ fa) dfs0(y, x), siz[x] += siz[y];
}
#define pii pair <i64, i64>
#define fi first
#define se second
pii operator * (pii A, pii B)
{
	A.se = (A.se + 2 * A.fi * B.fi + B.se) % MOD;
	(A.fi += B.fi) %= MOD;
	return A;
}

int main()
{
#ifdef CraZYali
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif
	n = read();q = read();
	REP(i, 2, n)
	{
		int x = read(), y = read();
		G[x].emplace_back(y);
		G[y].emplace_back(x);
	}
	dfs0(1);
	while (q--)
	{
		int s = read(), t = read();
		i64 ans = 0;
		REP(j, dfn[t], dfn[t] + siz[t] - 1)
		{
			int y = back[j];
			fa[y] = 0;dfs(y);
			REP(i, dfn[s], dfn[s] + siz[s] - 1)
			{
				int x = back[i];
				pii res(0, 0);
//				i64 ans0 = 0, ans1 = 0;
				while (x ^ y)
				{
					res = res * make_pair(f[x][0], f[x][1]);
//					ans1 = (ans1 + 2 * ans0 * f[x][0] + f[x][1]) % MOD;
//					(ans0 += f[x][0]) %= MOD;
					x = fa[x];
				}
				ans += res.fi + res.se;
			}
		}
		printf("%lld\n", ans % MOD);
	}
	return 0;
}
