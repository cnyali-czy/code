#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <map>
#include <cstring>
#include <vector>
#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 2e4 + 10, maxq = 2e5 + 10;

inline char nc()
{
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
#define getchar nc
inline i64 read()
{
	i64 res = 0;char c = getchar();
	while (!isdigit(c)) c = getchar();
	while ( isdigit(c)) res = res * 10 + (c - 48), c = getchar();
	return res;
}

int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}
vector <pair <int, int> > qry[maxn];

struct basis
{
	i64 p[61];
	inline void init()
	{
		memset(p, 0, sizeof p);
	}
	inline void ins(i64 x)
	{
		DEP(i, 60, 0) if (x >> i & 1)
			if (!p[i]) {p[i] = x;return;}
			else x ^= p[i];
	}
	inline i64 query()
	{
		i64 res = 0;
		DEP(i, 60, 0) res = max(res, res ^ p[i]);
		return res;
	}
}b[maxn];
inline basis operator + (basis a, const basis &b)
{
	REP(i, 0, 60) if (b.p[i]) a.ins(b.p[i]);
	return a;
}

int n, q;i64 a[maxn];

int allnode, rt, siz[maxn], Max[maxn];
bool vis[maxn];
void findrt(int x, int fa)
{
	siz[x] = 1;Max[x] = 0;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa && !vis[to[i]])
	{
		findrt(to[i], x);
		siz[x] += siz[to[i]];
		Max[x] = max(Max[x], siz[to[i]]);
	}
	Max[x] = max(Max[x], allnode - siz[x]);
	if (!rt || Max[x] < Max[rt]) rt = x;
}
map <i64, int, greater <i64> > mem[maxq];

int stk[maxn], top, clk[maxn], cur, fa[maxn];
void getall(int x)
{
	clk[stk[++top] = x] = cur;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa[x] && !vis[to[i]])
	{
		fa[to[i]] = x;
		getall(to[i]);
	}
}
void calc(int x, i64 ard, int flg)
{
	top = 0;++cur;fa[x] = 0;getall(x);
	REP(i, 1, top)
	{
		int u = stk[i];
		for (auto ccc : qry[u])
		{
			int v = ccc.first, id = ccc.second;
			if (clk[v] == cur) mem[id][(b[u] + b[v]).query()] += flg;
		}
	}
}
void dfs(int x)
{
	vis[x] = 1;
	top = 0;++cur;fa[x] = 0;getall(x);
	bool hav = 0;
	REP(i, 1, top)
	{
		int u = stk[i];
		for (auto ccc : qry[u])
		{
			int v = ccc.first, id = ccc.second;
			if (clk[v] == cur) {hav = 1;goto fk;}
		}
	}
fk:	if (!hav) return;
	b[x].init();b[x].ins(a[x]);
	REP(i, 2, top)
	{
		int u = stk[i];
		b[u] = b[fa[u]];b[u].ins(a[u]);
	}
	REP(i, 1, top)
	{
		int u = stk[i];
		for (auto ccc : qry[u])
		{
			int v = ccc.first, id = ccc.second;
			if (clk[v] == cur) mem[id][(b[u] + b[v]).query()]++;
		}
	}
	for (int i = bg[x]; i; i = ne[i]) if (!vis[to[i]])
	{
		calc(to[i], a[x], -1);
		allnode = siz[to[i]];
		rt = 0;
		findrt(to[i], x);
		dfs(rt);
	}
}

int main()
{
#ifdef CraZYali
	freopen("3292-new.in", "r", stdin);
	freopen("3292-new.out", "w", stdout);
#endif
	n = read();q = read();
	REP(i, 1, n) a[i] = read();
	REP(i, 2, n)
	{
		int x = read(), y = read();
		add(x, y);add(y, x);
	}
	REP(i, 1, q)
	{
		int x = read(), y = read();
		qry[x].emplace_back(y, i);
	}
	allnode = n;
	findrt(1, 0);dfs(rt);
	REP(i, 1, q)
		for (auto j : mem[i]) if (j.second > 0)
		{
			printf("%lld\n", j.first);
			break;
		}
	return 0;
}
