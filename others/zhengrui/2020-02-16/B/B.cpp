/*
	Problem:	B.cpp
	Time:		2020-02-16 16:56
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
const int maxn = 3e5 + 10, MOD = 998244353;

inline int add(int x, int y) {register int res = x + y;return res >= MOD ? res - MOD : res;}
inline int sub(int x, int y) {register int res = x - y;return res <  0   ? res + MOD : res;}
inline i64 mul(i64 x, int y) {register i64 res = x * y;return res >= MOD ? res % MOD : res;}
inline void inc(int &x, int y) {x += y;if (x >= MOD) x -= MOD;}

int power_pow(i64 base, int b)
{
	i64 ans = 1;
	while (b)
	{
		if (b & 1) ans = mul(ans, base);
		base = mul(base, base);
		b >>= 1;
	}
	return ans;
}
#define inv(x) power_pow(x, MOD - 2)

int n, lim;

int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
void add_edge(int x, int y)
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

int fac[maxn], Inv[maxn];
struct __init__
{
	__init__(const int N = maxn - 10)
	{
		fac[0] = 1;
		REP(i, 1, N) fac[i] = mul(i, fac[i-1]);
		Inv[N] = inv(fac[N]);
		DEP(i, N - 1, 0) Inv[i] = mul(i + 1, Inv[i + 1]);
	}
}__INIT__;
inline int C(int n, int m) {return n < m ? 0 : mul(fac[n], mul(Inv[m], Inv[n - m]));}

int ord[maxn], a[maxn];

namespace Copy
{
	const int maxN = 3.5e7;
	int ls[maxN], rs[maxN], s[maxN], cur;
#define lson ls[p], l, mid
#define rson rs[p], mid + 1, r
#define mid (l + r >> 1)

	void insert(int &p, int l, int r, int pos)
	{
		if (!p) p = ++cur;
		s[p]++;
		if (l == r) return;
		if (pos <= mid) insert(lson, pos);
		else			insert(rson, pos);
	}
	int query(int p, int l, int r, int L, int R)
	{
		if (!p) return 0;
		if (L <= l && r <= R) return s[p];
		else
		{
			if (R <= mid) return query(lson, L, R);
			if (L >  mid) return query(rson, L, R);
			return query(lson, L, R) + query(rson, L, R);
		}
	}
	namespace lca
	{
		int lg[maxn << 1];
		int dfs_clock, dep[maxn], fir[maxn], Min[maxn << 1][19], Pos[maxn << 1][19];
		void dfs(int x, int fa = 0)
		{
			fir[x] = ++dfs_clock;
			dep[x] = dep[fa] + 1;
			Min[dfs_clock][0] = dep[x];Pos[dfs_clock][0] = x;
			for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
			{
				dfs(to[i], x);
				++dfs_clock;
				Min[dfs_clock][0] = dep[x];Pos[dfs_clock][0] = x;
			}
		}
		void init()
		{
			REP(i, 2, n + n) lg[i] = lg[i >> 1] + 1;
			dfs(1);
			DEP(i, n + n, 1)
				for (int j = 1; i + (1 << j) - 1 <= n + n; j++)
					if (dep[Pos[i][j-1]] < dep[Pos[i + (1 << j - 1)][j-1]])
						Pos[i][j] = Pos[i][j - 1];
					else
						Pos[i][j] = Pos[i + (1 << j - 1)][j - 1];
		}
		inline int lca(int x, int y)
		{
			int l = fir[x], r = fir[y];if (l > r) swap(l, r);
			int k = lg[r - l + 1];
			int pos1 = Pos[l][k], pos2 = Pos[r - (1 << k) + 1][k];
			return dep[pos1] < dep[pos2] ? pos1 : pos2;
		}
		inline int dist(int x, int y) {return dep[x] + dep[y] - 2 * dep[lca(x, y)];}
	}
	int dep[maxn];

	namespace cd
	{
		int siz[maxn], Max[maxn], allnode, rt;
		bool vis[maxn];

		void findrt(int x, int fa = 0)
		{
			siz[x] = 1;Max[x] = 0;
			for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa && !vis[to[i]])
			{
				findrt(to[i], x);
				siz[x] += siz[to[i]];
				chkmax(Max[x], siz[to[i]]);
			}
			chkmax(Max[x], allnode - siz[x]);
			if (Max[x] < Max[rt] || !rt) rt = x;
		}

		int tfa[maxn], drt[maxn], crt[maxn];
		void dfs(int x)
		{
			vis[x] = 1;
			for (int i = bg[x]; i; i = ne[i]) if (!vis[to[i]])
			{
				allnode = siz[to[i]];
				rt = 0;
				dep[to[i]] = dep[x] + 1;
				findrt(to[i]);
				tfa[rt] = x;
				dfs(rt);
			}
		}

		void init()
		{
			allnode = 0;
			findrt(1);
			dfs(rt);
		}

		int query(int x, int y)
		{
			int res = Copy::query(drt[x], 0, n, 0, y);
			int nww = 0;
			for (int i = x; tfa[i]; i = tfa[i])
			{
				nww = lca::dist(x, tfa[i]);
				res += Copy::query(drt[tfa[i]], 0, n, 0, y - nww);
				res -= Copy::query(crt[i], 0, n, 0, y - nww);
			}
			return res;
		}
		void update(int x)
		{
			int nww = 0;
			insert(drt[x], 0, n, 0);
			for (int i = x; tfa[i]; i = tfa[i])
			{
				nww = lca::dist(x, tfa[i]);
				Copy::insert(drt[tfa[i]], 0, n, nww);
				Copy::insert(crt[i], 0, n, nww);
			}
		}
	}
}
namespace Poly
{
	const int N = 1 << 22, invn = inv(N);
	int R[maxn];
	void NTT(int a[], int n, int flag)
	{
		REP(i, 1, n - 1)
		{
			R[i] = (R[i >> 1] >> 1) | (i & 1 ? n >> 1 : 0);
			if (i < R[i]) swap(a[i], a[R[i]]);
		}
		for (int i = 1; i < n; i <<= 1)
		{
			int wn = power_pow(3, (MOD - 1) / (i << 1));
			if (flag < 0) wn = inv(wn);
			for (int k = 0; k < n; k += i << 1)
				for (int l = 0, w = 1, x, y; l < i; l++, w = mul(w, wn))
				{
					x = a[k + l], y = mul(w, a[k + l + i]);
					a[k + l] = add(x, y);
					a[k + l + i] = sub(x, y);
				}
		}
		if (flag < 0)
		{
			const int invn = inv(n);
			REP(i, 0, n - 1) a[i] = mul(a[i], invn);
		}
	}
	int res[N], T[N], b[N];
	void work()
	{
		REP(i, 1, n) T[a[i]]++;
		REP(i, 0, n) T[i] = mul(T[i], fac[i]);
		REP(i, 0, n) b[n - i] = Inv[i];
		NTT(T, N, 1);NTT(b, N, 1);
		REP(i, 0, N - 1) res[i] = mul(T[i], b[i]);
		NTT(res, N, -1);
	}
}
using Copy::lca::lca;
using Copy::lca::dist;

int main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read<int>();lim = read<int>();
	REP(i, 2, n) {int x(read<int>()), y(read<int>());add_edge(x, y);add_edge(y, x);}
	Copy::lca::init();
	Copy::cd::init();
	REP(i, 1, n) ord[i] = i;
	sort(ord + 1, ord + 1 + n, [&](int x, int y) {return Copy::lca::dep[x] < Copy::lca::dep[y];});
	REP(i, 1, n)
	{
		a[ord[i]] = Copy::cd::query(ord[i], lim);
		Copy::cd::update(ord[i]);
	}
	Poly::work();
	REP(k, 0, n - 1) printf("%d%c", mul(Inv[k], Poly::res[k + n]), k == end_k ? '\n' : ' ');
	return 0;
}
