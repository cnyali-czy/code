/*
 * File name:	C.cpp
 * Author	:	CraZYali
 * Year		:	2019.11.10 11:42
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUnCTIOn__, __LInE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <iostream>
#include <cstdio>

using namespace std;

template <typename T> inline T read()
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

#define file(FILE_nAME) freopen(FILE_nAME".in", "r", stdin), freopen(FILE_nAME".out", "w", stdout);

namespace run
{
	const int maxn = 3000000 + 10, MOD = 998244353;

	int power_pow(long long base, int b)
	{
		long long ans(1);
		while (b)
		{
			if (b & 1) (ans *= base) %= MOD;
			(base *= base) %= MOD;
			b >>= 1;
		}
	}
#define inv(x) power_pow(x, MOD - 2)

	int bg[maxn], to[maxn * 2], ne[maxn * 2], e;

	inline void add(int x, int y)
	{
		e++;
		to[e] = y;
		ne[e] = bg[x];
		bg[x] = e;
	}

	int n, rt, rt2;
	int DivPoint, Ans;
	int siz[maxn], Maxs[maxn], Max[maxn], Sons[maxn];
	int F[maxn];

	int fac[maxn], Inv[maxn];

	struct __InIT__
	{
		__InIT__(const int n = 3e6)
		{
			fac[0] = 1;
			REP(i, 1, n) fac[i] = 1ll * fac[i-1] * i % MOD;
			Inv[n] = inv(fac[n]);
			DREP(i, n - 1, 0) Inv[i] = 1ll * Inv[i+1] * (i + 1) % MOD;
		}
	}__init__;

	inline int C(int n, int m) {return 1ll * fac[n] * Inv[m] % MOD * Inv[n - m] % MOD;}

	void dfs1(int x, int fa = 0)
	{
		siz[x] = 1;
		for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
		{
			dfs1(to[i], x);
			siz[x] += siz[to[i]];
			chkmax(Max[x], siz[to[i]]);
		}
		chkmax(Max[x], n - siz[x]);
		if (Max[x] < Max[rt] || !rt) rt = x;
	}

	int dfs2(int u, int f) {
		F[u] = siz[u] = 1;
		int s = u;
		for (int i = G.bg[u]; i; i = G.ne[i]) {
			int v = G.to[i];
			if (v == f) continue;
			Sons[u]++;
			s = dfs2(v, u);
			siz[u] += siz[v];
			F[u] = mul(F[u], F[v]);
			F[u] = mul(F[u], C(siz[u] - 1, siz[v]));
		}
		if (Sons[u] > 1) return u;
		else return s;
	}


	int main()
	{
		n = read<int>();
		REP(i, 2, n)
		{
			int x(read<int>()), y(read<int>());
			add(x, y);add(y, x);
		}
		dfs1(1);
		rt2 = Maxs[rt];

		int u = dfs2(rt, rt2), v = dfs2(rt2, rt);
		Ans = mul(mul(F[u], F[v]), 2);
		if (siz[u] > siz[v]) DivPoint = siz[u];
		else DivPoint = siz[v];
		if (DivPoint < 2) DivPoint = 2;

		for (int i = 2; i < DivPoint && i <= n / 2; ++i) printf("%d\n", 0);
		for (int i = DivPoint; i <= n / 2; ++i) printf("%d\n", Ans);
		return 0;
	}
}

int main()
{
#ifdef CraZYali
	file("C");
#endif
	return run::main();
}
