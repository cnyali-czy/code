#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <cmath>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e5 + 10 ;
const double eps = 1e-8, pi = acos(-1);
int bg[maxn], ne[maxn], to[maxn], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

struct cp
{
	double x, y;
	cp() {}
	cp(double x, double y) : x(x), y(y) {}
	inline cp operator + (const cp &B) {return cp(x + B.x, y + B.y);}
	inline cp operator - (const cp &B) {return cp(x - B.x, y - B.y);}
	inline cp operator * (const cp &B) {return cp(x * B.x - y * B.y, x * B.y + y * B.x);}
};
inline double dis(cp x, cp y) {x = x - y;return sqrt(x.x * x.x + x.y * x.y);}

int n, q;
cp p[maxn];

int fa[maxn], dfn[maxn], dfs_clock, back[maxn], siz[maxn];
void dfs(int x)
{
	back[dfn[x] = ++dfs_clock] = x;siz[x] = 1;
	for (int i = bg[x]; i; i = ne[i]) dfs(to[i]), siz[x] += siz[to[i]];
}

cp s[maxn << 2], tmin[maxn << 2], tmul[maxn << 2];
#define lson ls, l, mid
#define rson rs, mid + 1, r
#define mid (l + r >> 1)
#define ls p << 1
#define rs p << 1 | 1
bool need_minus[maxn << 2], need_mul[maxn << 2];
void build(int p, int l, int r)
{
	if (l == r) s[p] = ::p[back[l]];
	else
	{
		build(lson);
		build(rson);
//		s[p] = s[ls] + s[rs];
		tmul[p] = cp(1, 0);
	}
}
void maintain_mul(int p, int l, int r, cp val)
{
	need_mul[p] = 1;
	if (l == r) s[p] = s[p] * val;
	tmin[p] = tmin[p] * val;
	tmul[p] = tmul[p] * val;
}
void maintain_minus(int p, int l, int r, cp val)
{
	if (l < r && need_mul[p])
	{
		maintain_mul(lson, tmul[p]);
		maintain_mul(rson, tmul[p]);
		tmul[p] = cp(1, 0);
		need_mul[p] = 0;
	}
	need_minus[p] = 1;
	if (l == r) s[p] = s[p] - val * cp(r - l + 1, 0);
	tmin[p] = tmin[p] + val;
}
void pushdown(int p, int l, int r)
{
	if (need_minus[p])
	{
		maintain_minus(lson, tmin[p]);
		maintain_minus(rson, tmin[p]);
		tmin[p] = cp(0, 0);
		need_minus[p] = 0;
	}
	if (need_mul[p])
	{
		need_mul[p] = 0;
		maintain_mul(lson, tmul[p]);
		maintain_mul(rson, tmul[p]);
		tmul[p] = cp(1, 0);
	}
}
void update_minus(int p, int l, int r, int L, int R, cp val)
{
	if (L <= l && r <= R) maintain_minus(p, l, r, val);
	else
	{
		if (need_minus[p] || need_mul[p]) pushdown(p, l, r);
		if (L <= mid) update_minus(lson, L, R, val);
		if (R >  mid) update_minus(rson, L, R, val);
	}
}
void update_mul(int p, int l, int r, int L, int R, cp val)
{
	if (L <= l && r <= R) maintain_mul(p, l, r, val);
	else
	{
		if (need_minus[p] || need_mul[p]) pushdown(p, l, r);
		if (L <= mid) update_mul(lson, L, R, val);
		if (R >  mid) update_mul(rson, L, R, val);
	}
}
cp query(int p, int l, int r, int pos)
{
	if (l == r) return s[p];
	else
	{
		if (need_minus[p] || need_mul[p]) pushdown(p, l, r);
		return pos <= mid ? query(lson, pos) : query(rson, pos);
	}
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("gear.in", "r", stdin);
	freopen("gear.out", "w", stdout);
#endif
	cin >> n >> q;
	REP(i, 2, n)
	{
		scanf("%d", fa + i);
		add(fa[i], i);
		p[i] = p[fa[i]] + cp(0, 1);
	}
	dfs(1);
	build(1, 1, n);
	while (q--)
	{
		int k;scanf("%d", &k);
		if (k == 1)
		{
			int x, t;scanf("%d%d", &x, &t);
			if (x == 1) continue;
			double arc = t * pi / 180;
			cp R(cos(arc), sin(arc)), pfa = query(1, 1, n, dfn[fa[x]]);
			update_minus(1, 1, n, dfn[x], dfn[x] + siz[x] - 1, pfa);
			update_mul(1, 1, n, dfn[x], dfn[x] + siz[x] - 1, R);
			update_minus(1, 1, n, dfn[x], dfn[x] + siz[x] - 1, cp(-1, 0) * pfa);
			/*
			   REP(i, dfn[x], dfn[x] + siz[x] - 1)
			   {
			   int y = back[i];
			   p[y] = rotate(p[y], p[fa[x]], t);
			   }
			 */
		}
		else
		{
			int x, y;scanf("%d%d", &x, &y);
			cp px = query(1, 1, n, dfn[x]);
			cp py = query(1, 1, n, dfn[y]);
			printf("%.10lf\n", dis(px, py));
		}
	}
	return 0;
}
