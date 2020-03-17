/*
	Problem:	C.cpp
	Time:		2020-03-10 10:11
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vectoR>
#include <iostream>
#include <cstdio>
using namespace std;
const int maxn = 500 + 5;
#define MOD 1000000007
#define i64 long long
vector <int> G[maxn];
inline void Add(int x, int y)
{
	G[x].emplace_back(y);
}

inline int add(int x, int y) {x += y;return x >= MOD ? x - MOD : x;}
inline int sub(int x, int y) {x -= y;return x <    0 ? x + MOD : x;}
inline i64 mul(i64 x, int y) {x *= y;return x >= MOD ? x % MOD : x;}
inline void inc(int &x, int y) {x += y;if (x >= MOD) x -= MOD;}

int power_pow(int base, int b)
{
	int ans = 1;
	while (b)
	{
		if (b & 1) ans = mul(ans, base);
		base = mul(base, base);
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
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n;

int fac[maxn << 1], Inv[maxn << 1];
struct __init__
{
	__init__(const int n = maxn * 2 - 1)
	{
		fac[0] = 1;
		REP(i, 1, n) fac[i] = mul(fac[i - 1], i);
		Inv[n] = inv(fac[n]);
		DEP(i, n - 1, 0) Inv[i] = mul(Inv[i + 1], i + 1);
	}
}__INIT__;

int dep[maxn], siz[maxn], fa[maxn], dfn[maxn], dfs_clock, back[maxn], dp[maxn];
int grand[maxn][20];
void init(int u)
{
	grand[u][0] = fa[u];
	REP(i, 1, 19) grand[u][i] = grand[grand[u][i-1]][i-1]; 
	dep[u] = dep[fa[u]] + 1;
	back[dfn[u] = ++dfs_clock] = u;
	siz[u] = dp[u] = 1;
	for (int v : G[u]) if (v ^ fa[u])
	{
		fa[v] = u;
		init(v);
		siz[u] += siz[v];
		dp[u] = mul(dp[u], mul(dp[v], Inv[siz[v]]));
	}
	dp[u] = mul(dp[u], fac[siz[u] - 1]);
}
int u[maxn], v[maxn];

inline bool inside(int x, int y) {return dfn[y] <= dfn[x] && dfn[x] <= dfn[y] + siz[y] - 1;}
int gg[maxn], top;

int mem[maxn][maxn];
inline int lca(int x, int y)
{
	if (dep[x] < dep[y]) swap(x, y);
	DEP(i, 10, 0) if (dep[grand[x][i]]>=dep[y])x=grand[x][i];
	if(x==y)return x;
	DEP(i,10,0)if(grand[x][i]^grand[y][i])x=grand[x][i],y=grand[y][i];
	return fa[x];
}

inline int goo(int x, int y)
{
	DEP(i, 10, 0) if (dep[grand[x][i]] > dep[y]) x = grand[x][i];
	return x;
}
inline int go(int x, int y)
{
	int res;
	if (x == y) res = 0;
	if (inside(x, y)) res = fa[x];
	else res = goo(y, x);
	cout << x << ' ' << y << ' ' << res << endl;
	return res;
}

int qry(int x, int y)
{
	return mul(siz[y], inv(siz[x] + siz[y]));
}
int uu, vv;
int good(int x, int y)
{
	if (!x || inside(x, uu)) return 0;
	if (!y || inside(y, vv)) return 1;
	int p = qry(x, y);
	return add(mul(p, good(x, go(y, vv))), mul(MOD + 1 - p, good(go(x, uu), y)));
}

int calc(int u, int v)
{
	::uu = u;::vv = v;
	int l = lca(u, v);
	return good(go(l, u), go(l, v));
}

int work(int x, int y)
{
	if (mem[x][y]) return mem[x][y];
	int &res = mem[x][y];
	if (fa[x] == fa[y])
	{
		DEBUG;
		if (dep[x] < dep[y]) swap(x, y);
		int grd = x;
		top = 0;
		while (dep[grd] > dep[y])
		{
			gg[++top] = grd;
			grd = fa[grd];
		}
		int fir = 1;
		while (1)
		{
//			int x = grd;
			int X = min(grd, y), Y = max(grd, y);
#define x X
#define y Y
			int tmp1 = dp[y];
			tmp1 = mul(tmp1, Inv[siz[y] - 1]);
			tmp1 = mul(tmp1, mul(dp[x], Inv[siz[x]]));
			tmp1 = mul(tmp1, fac[siz[x] + siz[y] - 1]);
			int tmp2 = 1;
			tmp2 = mul(tmp2, mul(dp[x], Inv[siz[x]]));
			tmp2 = mul(tmp2, mul(dp[y], Inv[siz[y]]));
			tmp2 = mul(tmp2, fac[siz[x] + siz[y]]);
			int p = mul(tmp1, inv(tmp2));
			p = MOD + 1 - p;
//			cout << x << ' ' << y << ' ' << tmp1 << ' ' << tmp2 << ' ' << fir << ' ' << p << '\n';
			inc(res, mul(fir, p));
			fir = mul(fir, MOD + 1 - p);
#undef x
#undef y
			if (top) grd = gg[top--];
			else break;
		}
		DEBUG;
		return MOD + 1 - res;
	}
	DEBUG;
	int l = lca(x, y);
	cerr<<x<<' '<<y<<' '<<l<<endl;
	int tx = x, ty = y;
	while (fa[tx] ^ l) tx = fa[tx];
	while (fa[ty] ^ l) ty = fa[ty];
	return work(tx, ty);//x, ty);
}

signed main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();
	REP(i, 2, n)
	{
		int x(read<int>()), y(read<int>());
		Add(y, x);Add(x, y);
	}
	init(1);
	int tot = dp[1];
	REP(i, 1, n) G[i].clear();
	REP(i, 1, n) printf("%d%c", dp[i], i == n ? '\n' : ' ');
	int ans = 0, ans2 = 0;
	REP(i, 1, n) REP(j, i + 1, n) if (!inside(i, j) && !inside(j, i))
	{
		int x = i, y = j;
		/*
		if (dep[x] < dep[y]) swap(x, y);
		int grd = x;
		top = 0;
		while (dep[grd] > dep[y])
		{
			gg[++top] = grd;
			grd = fa[grd];
		}
		int fir = 1;
		int res = 0;
		while (1)
		{
//			int x = grd;
			int X = min(grd, y), Y = max(grd, y);
#define x X
#define y Y
			int tmp1 = dp[y];
			tmp1 = mul(tmp1, Inv[siz[y] - 1]);
			tmp1 = mul(tmp1, mul(dp[x], Inv[siz[x]]));
			tmp1 = mul(tmp1, fac[siz[x] + siz[y] - 1]);
			int tmp2 = 1;
			tmp2 = mul(tmp2, mul(dp[x], Inv[siz[x]]));
			tmp2 = mul(tmp2, mul(dp[y], Inv[siz[y]]));
			tmp2 = mul(tmp2, fac[siz[x] + siz[y]]);
			int p = mul(tmp1, inv(tmp2));
			p = MOD + 1 - p;
			cout << x << ' ' << y << ' ' << tmp1 << ' ' << tmp2 << ' ' << fir << ' ' << p << '\n';
			inc(res, mul(fir, p));
			fir = mul(fir, MOD + 1 - p);
#undef x
#undef y
			if (top) grd = gg[top--];
			else break;
		}
		cout << i << ' ' << j << ' ' << res << endl;
		puts("");
		inc(ans, MOD + 1 - res);
		/*
		REP(k, 0, n) G[k].clear();
		Add(0, i);
		REP(k, 1, n) if (k != i && k != j && ((inside(k, i) && inside(fa[k], i)) || (inside(k, j) && inside(fa[k], j)))) Add(fa[k] == j ? 0 : fa[k], k);
		solve(0);
		printf("Graph of (%d, |%d|):\n", i, j);
		REP(x, 0, n) for (int y : G[x]) printf("%d %d\n", x, y);
		puts("--------------");
		int tmp1 = dp[0];
		REP(k, 0, n) G[k].clear();
		G[0].clear();
		Add(0, i);Add(0, j);
//		for (int v : G[j]) Add(j, v);
		REP(k, 1, n) if (k != i && k != j && ((inside(k, i) && inside(fa[k], i)) || (inside(k, j) && inside(fa[k], j)))) Add(fa[k], k);
		printf("Graph of (%d, %d):\n", i, j);
		REP(x, 0, n) for (int y : G[x]) printf("%d %d\n", x, y);
		puts("--------------");
		solve(0);
		int tmp2 = dp[0];
		cout << i << ' ' << j << ' ' << tmp1 << '/' << tmp2 << endl;
		inc(ans, mul(tmp1, inv(tmp2)));
		*/
		int ccc = 0;
		inc(ans, calc(i, j));
		cout<<"????:"<<i<<' '<<j<<' '<<mul(tot,calc(i,j))<<'\n';
		inc(ans2, calc(j, i));
	}
	else if (inside(j, i)) ans++, ans2++;
	cerr << "tot = " << tot << '\n';
	cout << mul(ans, tot) << '\n';
	cout << mul(ans2, tot) << '\n';
	return 0;
}
