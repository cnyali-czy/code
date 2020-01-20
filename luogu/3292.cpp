/*
 * File Name:	3292.cpp
 * Author	:	CraZYali
 * Time		:	2020.01.18 21:52
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 20000 + 10;

int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

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

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout);

struct basis
{
	long long p[61];
	basis() {REP(i, 0, 60) p[i] = 0;}
	inline void insert(long long x)
	{
		DEP(i, 60, 0) if (x & (1ll << i))
			if (!p[i]) return void(p[i] = x);
			else x ^= p[i];
	}
	inline long long query()
	{
		long long ans = 0;
		DEP(i, 60, 0) chkmax(ans, ans ^ p[i]);
		return ans;
	}
	inline basis operator + (const basis &B)
	{
		basis res = *this;
		REP(i, 0, 60) if (B.p[i]) res.insert(B.p[i]);
		return res;
	}
	inline basis& operator +=(const basis &B)
	{
		REP(i, 0, 60) if (B.p[i]) insert(B.p[i]);
		return *this;
	}
}b[maxn][16];

int n, q;
int dep[maxn], fa[maxn][16];

void dfs(int x)
{
	dep[x] = dep[fa[x][0]] + 1;
	REP(i, 1, 15)
	{
		fa[x][i] = fa[fa[x][i-1]][i-1];
		b[x][i] = b[x][i-1] + b[fa[x][i-1]][i-1];
	}
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa[x][0])
	{
		fa[to[i]][0] = x;
		dfs(to[i]);
	}
}

inline int lca(int x, int y)
{
	if (dep[x] < dep[y]) swap(x, y);
	DEP(i, 15, 0) if (dep[fa[x][i]] >= dep[y]) x = fa[x][i];
	if (x == y) return x;
	DEP(i, 15, 0) if (fa[x][i] ^ fa[y][i]) x = fa[x][i], y = fa[y][i];
	return fa[x][0];
}
int anc(int x, int k)
{
	DEP(i, 15, 0) if ((1 << i) <= k)
	{
		k -= (1 << i);
		x = fa[x][i];
	}
	return x;
}
int LG[maxn];

int main()
{
#ifdef CraZYali
	file("3292");
#endif
	cin >> n >> q;
	REP(i, 2, n) LG[i] = LG[i >> 1] + 1;
	REP(i, 1, n) b[i][0].insert(read<long long>());
	REP(i, 2, n)
	{
		int x(read<int>()), y(read<int>());
		add(x, y);add(y, x);
	}
	dfs(1);
	while (q--)
	{
		int x(read<int>()), y(read<int>()), l(lca(x, y));
		int lx = dep[x] - dep[l] + 1, kx = LG[lx];
		basis A = b[x][kx] + b[anc(x, lx - (1 << kx))][kx];
		int ly = dep[y] - dep[l] + 1, ky = LG[ly];
		basis B = b[y][ky] + b[anc(y, ly - (1 << ky))][ky];
		printf("%lld\n", (A + B).query());
	}
	return 0;
}
