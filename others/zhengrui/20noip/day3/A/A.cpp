#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <iostream>
#include <cstdio>
#define i64 long long
#define ui64 unsigned i64
using namespace std;
const int maxn = 2.5e5 + 10;

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
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, q;
int a[maxn];

namespace orzhh
{
	int dep[maxn], siz[maxn], hvy[maxn], top[maxn], fa[maxn], dfn[maxn], dfs_clock;
	void dfs1(int x)
	{
		siz[x] = 1;
		hvy[x] = 0;
		for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa[x])
		{
			fa[to[i]] = x;
			dep[to[i]] = dep[x] + 1;
			dfs1(to[i]);
			siz[x] += siz[to[i]];
			if (siz[to[i]] > siz[hvy[x]]) hvy[x] = to[i];
		}
	}
	void dfs2(int x, int y)
	{
		dfn[x] = ++dfs_clock;
		top[x] = y;
		if (!hvy[x]) return;
		dfs2(hvy[x], y);
		for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa[x] && to[i] ^ hvy[x])
			dfs2(to[i], to[i]);
	}

	template <const i64 base, const i64 MOD>
		struct Hash_Table
		{
			inline void inc(int &x, int y) {x += y;if (x >= MOD) x -= MOD;}
			int bin[maxn], p[maxn];
			Hash_Table()
			{
				bin[0] = 1;
				p[0] = 0;
				REP(i, 1, maxn - 1)
				{
					bin[i] = bin[i - 1] * base % MOD;
					p[i] = (p[i - 1] + bin[i]) % MOD;
				}
			}
			int s[maxn];
			void clear()
			{
				REP(i, 1, n) s[i] = 0;
			}
			void add(int x, int y)
			{
				while (x <= n)
				{
					inc(s[x], y);
					x += x & -x;
				}
			}
			inline int sum(int l, int r)
			{
				l--;
				i64 res = 0;
				while (r > l) res += s[r], r &= (r - 1);
				while (l > r) res -= s[l], l &= (l - 1);
				res %= MOD;
				if (res < 0) res += MOD;
				return res;
			}
			void modify(int x, int flag)
			{
				add(dfn[x], flag == 1 ? bin[a[x]] : MOD - bin[a[x]]);
			}
		};
	const int MOD1 = 998244353, MOD2 = 1e9 + 7;
	Hash_Table <3, MOD1> h1;
	Hash_Table <5, MOD2> h2;
	
	void clear()
	{
		e = 0;
		REP(i, 1, n) bg[i] = fa[i] = 0;
	}
	void work()
	{
		n = read<int>();q = read<int>();
		clear();h1.clear();h2.clear();
		REP(i, 1, n) a[i] = read<int>();
		REP(i, 2, n)
		{
			int x = read<int>(), y = read<int>();
			add(x, y);add(y, x);
		}
		dfs_clock = 0;
		dfs1(1);dfs2(1, 1);
		REP(i, 1, n)
			h1.modify(i, 1), h2.modify(i, 1);
		while (q--)
		{
			int opt = read<int>(), x = read<int>(), y = read<int>();
			if (opt == 2)
			{
				h1.modify(x, -1),	h2.modify(x, -1);
				a[x] = y;
				h1.modify(x, 1),	h2.modify(x, 1);
			}
			else
			{
				int dis = dep[x] + dep[y];
				i64 s1 = 0, s2 = 0;
				while (top[x] ^ top[y])
				{
					if (dep[top[x]] < dep[top[y]]) swap(x, y);
					s1 += h1.sum(dfn[top[x]], dfn[x]);
					s2 += h2.sum(dfn[top[x]], dfn[x]);
					x = fa[top[x]];
				}
				if (dep[x] > dep[y]) swap(x, y);
				(s1 += h1.sum(dfn[x], dfn[y])) %= MOD1;
				(s2 += h2.sum(dfn[x], dfn[y])) %= MOD2;
				dis -= 2 * dep[x];
				int N = dis + 1;
				if (s1 == h1.p[N] && s2 == h2.p[N]) puts("Yes");
				else puts("No");
			}
		}
	}
}

int main()
{
#ifdef CraZYali
	file("A");
#endif
	register int T = read<int>();
	while (T--) orzhh :: work();
	return 0;
}
