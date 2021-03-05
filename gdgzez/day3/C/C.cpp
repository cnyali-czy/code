/*
	Problem:	C.cpp
	Time:		2021-03-05 08:08
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

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
const int maxn = 5e5 + 10, MOD = 998244353;

int bg[maxn], ne[maxn << 1], to[maxn << 1], w[maxn << 1], e;
inline void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
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

int n, deg[maxn];
int f[maxn], g[maxn], h[maxn];

void dfs0(int x, int fa = 0)
{
	g[x] = f[x] = deg[x] * (deg[x] - 1ll) / 2 % MOD;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
	{
		dfs0(to[i], x);
		(f[x] += f[to[i]]) %= MOD;
	}
}
void dfs2(int x, int fa = 0)
{
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
	{
		h[to[i]] = ((i64)f[x] + h[x] - f[to[i]]) % MOD;
		dfs2(to[i], x);
	}
}
i64 ans;
int in[maxn], out[maxn], id[maxn], v[maxn];
void dfs(int x, int fa = 0)
{
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa) dfs(to[i], x);
	i64 sum = 0, N = 0;
	for (int i = bg[x]; i; i = ne[i])
	{
		sum += (v[id[++N] = to[i]] = w[i]);
		if (to[i] == fa)
		{
			in[to[i]] = h[x];
			out[to[i]] = f[x];
		}
		else
		{
			in[to[i]] = f[to[i]];
			out[to[i]] = h[to[i]];
		}
	}sum %= MOD;
	sort(id + 1, id + 1 + N, [&](int x, int y) {return v[x] < v[y];});
	REP(i, 1, N)
	{
		(ans += (N - 1) * (N - 2) % MOD * v[id[i]]) %= MOD;
		(ans += (N - 2) * (sum - v[id[i]])) %= MOD;
		if (id[i] ^ fa) (ans += 4ll * in[id[i]] * out[id[i]] % MOD * v[id[i]]) %= MOD;
		(ans += (sum - v[id[i]] * N) % MOD * in[id[i]]) %= MOD;
	}
	i64 fk = 0, cur = 0;
	REP(i, 1, N) (fk += (i - 1 + 3 * (N - i)) * v[id[i]]) %= MOD;
	REP(i, 1, N)
	{
		i64 res = (fk - (i - 1 + 3 * (N - i)) * v[id[i]]) % MOD;
		(res -= 3 * cur + sum - v[id[i]] - cur) %= MOD;
		(ans += res * in[id[i]]) %= MOD;
		(cur += v[id[i]]) %= MOD;
	}
	if (N >= 4) (ans += (N - 2) * (N - 3) / 2 % MOD * fk) %= MOD;
}
int main()
{
#ifdef CraZYali
	file("C");
#endif
	cin >> n;
	REP(i, 2, n)
	{
		int x = read<int>(), y = read<int>(), z = read<int>();
		add(x, y, z);add(y, x, z);
		deg[x]++;deg[y]++;
	}
	dfs0(1);dfs2(1);
	dfs(1);
	cout << (ans + MOD) % MOD << endl;
	return 0;
}
