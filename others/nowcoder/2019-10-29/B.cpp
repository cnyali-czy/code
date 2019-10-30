/*
 * File Name:	B.cpp
 * Author	:	CraZYali
 * Year		:	2019.10.29 19:30
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <iostream>
#include <cstdio>
using namespace std;
const int maxn = 1e5 + 10, maxk = 11;

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

namespace seg
{
	const int maxN = 3e7;
	int rt[maxn], ls[maxN], rs[maxN], sum[maxN], cur;
#define mid (l + r >> 1)
#define lson ls[p], l, mid
#define rson rs[p], mid + 1, r
	void update(int &p, int l, int r, int pos, int val = 1)
	{	
		if (!p) p = ++cur;
		sum[p] += val;
		if (l == r) return;
		else if (pos <= mid) update(lson, pos, val);
		else update(rson, pos, val);
	}
	int query(int p, int l, int r, int pos)
	{
		if (!(l <= pos && pos <= r)) return 0;
		if (!p) return 0;
		if (l == r) return sum[p];
		else if (pos <= mid) return query(lson, pos);
		else return query(rson, pos);
	}
	int merge(int x, int y)
	{
		int p = ++cur;
		if (!x || !y)
		{
			int qaq = x + y;
			ls[p] = ls[qaq];
			rs[p] = rs[qaq];
			sum[p] = sum[qaq];
		}
		else
		{
			sum[p] = sum[x] + sum[y];
			ls[p] = merge(ls[x], ls[y]);
			rs[p] = merge(rs[x], rs[y]);
		}
		return p;
	}
}
using seg::rt;
int n, k, dep[maxn];

int ans1[maxn][maxk], f[maxn][maxk], g[maxn][maxk], j;
const int MOD = 1e9 + 7;
void init(int x, int fa = -1)
{
	REP(i, 0, k) f[x][i] = g[x][i] = 1;
	seg::update(rt[x], 0, n, dep[x]);
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
	{
		dep[to[i]] = dep[x] + 1;
		init(to[i], x);
		rt[x] = seg::merge(rt[x], rt[to[i]]);
		REP(j, 1, k)
		{
			f[x][j] += f[to[i]][j-1];
			g[x][j] = 1ll * g[x][j] * g[to[i]][j-1] % MOD * f[to[i]][j-1] % MOD;
		}
	}
}
void solve1(int x, int fa = -1)
{
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
	{
		ans1[to[i]][j] = ans1[x][j-1] + seg::query(rt[to[i]], 0, n, dep[to[i]] + j) + seg::query(rt[to[i]], 0, n, dep[to[i]] + j - 1);
		solve1(to[i], x);
	}
}

int power_pow(long long base, int b)
{
	long long ans(1);
	while (b)
	{
		if (b & 1) (ans *= base) %= MOD;
		(base *= base) %= MOD;
		b >>= 1;
	}
	return ans;
}
#define inv(x) power_pow(x, MOD - 2)

int h[maxn][maxk];
int tmp[maxk];
void dfs(int x, int fa = -1)
{
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
	{
		REP(j, 1, k) h[to[i]][j] = 1ll * g[x][j] * inv(g[to[i]][j-1]) % MOD * inv(f[to[i]][j-1]) % MOD;
		REP(j, 1, k) tmp[j] = ans1[x][j] - f[to[i]][j-1];
		tmp[0] = h[to[i]][0] = 1;
		REP(j, 1, k) g[to[i]][j] = 1ll * g[to[i]][j] * h[to[i]][j-1] % MOD * tmp[j-1] % MOD;
		dfs(to[i], x);
	}
}

signed main()
{
#ifdef CraZYali
	file("B");
#endif
	cin >> n >> k;
	REP(i, 2, n)
	{
		int x(read<int>()), y(read<int>());
		add(x, y);add(y, x);
	}
	init(1);
	//	REP(i, 1, n) printf("%d%c", dep[i], i == n ? '\n' :' ');
	REP(i, 1, n) if (dep[i] <= k) ans1[1][dep[i]]++;
	REP(i, 1, k) ans1[1][i] += ans1[1][i-1];
	REP(i, 1, n) ans1[i][0] = 1;
	for (j = 1; j <= k; j++) solve1(1);
	dfs(1);
	/*
	   REP(i, 1, n)
	   REP(j, 0, k) printf("%d%c", ans1[i][j], j == end_j ? '\n' : ' ');
	   puts("------");
	   REP(x, 1, n)
	   {
	   printf("%d :\n",x);
	   REP(i, 0, n) printf("%d%c", seg::query(rt[x], 0, n, i), i == n ? '\n' : ' ');
	   }
	   puts("------");
	   */
	REP(i, 1, n) printf("%d%c", ans1[i][k], i == n ? '\n' : ' ');
	REP(i, 1, n) printf("%d%c", (1ll * g[i][k] * ans1[i][k] % MOD + MOD) % MOD, i == n ? '\n' : ' ');
	return 0;
}
