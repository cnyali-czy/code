#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;
const int maxn = 1e5 + 10, maxm = 1e5 + 10, maxq = 1e5 + 10;

int n, m, q;

namespace SMT
{
	const int maxN = 1e7 + 10;
	int ls[maxN], rs[maxN], v[maxN], cur;
#define lson ls[p], l, mid
#define rson rs[p], mid + 1, r
#define mid (l + r >> 1)
	void modify(int pre, int &p, int l, int r, int pos, int val)
	{
		p = ++cur;
		ls[p] = ls[pre];
		rs[p] = rs[pre];
		if (l == r)
		{
			v[p] = val;
			return;
		}
		if (pos <= mid) modify(ls[pre], lson, pos, val);
		else modify(rs[pre], rson, pos, val);
	}
	int query(int p, int l, int r, int pos)
	{
		if (l == r) return v[p];
		return pos <= mid ? query(lson, pos) : query(rson, pos);
	}
}
using SMT :: modify;
using SMT :: query;

int k, id[maxn], fa[maxn], sz[maxn];
int find(int ver, int x)
{
	int f = query(fa[ver], 1, n, x);
	if (f == x) return x;
	return find(ver, f);
	modify(fa[ver], fa[ver], 1, n, x, f = find(ver, f));
	return f;
}
int x[maxq], y[maxq], z[maxq], ans[maxq];
#undef mid

int QAQ[maxq];
void solve(int l, int r, int ql, int qr)
{
	if (ql > qr) return;
	if (l == r)
	{
		REP(i, ql, qr) ans[QAQ[i]] = id[l];
		return;
	}
	int mid = l + r >> 1;

	static int tmp[maxq];
	int L = ql - 1, R = qr + 1;
	REP(I, ql, qr)
	{
		int i = QAQ[I];
		int fx = find(mid, x[i]), res = query(sz[mid], 1, n, fx);
		if (res < z[i]) {int fy = find(mid, y[i]);if (fx ^ fy) res += query(sz[mid], 1, n, fy);}
		if (res >= z[i]) tmp[++L] = i;
		else tmp[--R] = i;
	}
	REP(i, ql, qr) QAQ[i] = tmp[i];
	solve(l, mid, ql, L);
	solve(mid + 1, r, R, qr);
}
int Fa[maxn], Sz[maxn];
int Find(int x) {return Fa[x] == x ? Fa[x] : Fa[x] = Find(Fa[x]);}

int main()
{
#ifdef CraZYali
	freopen("1998.in", "r", stdin);
	freopen("1998.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, n)
	{
		modify(fa[0], fa[0], 1, n, i, i);
		modify(sz[0], sz[0], 1, n, i, 1);
		Fa[i] = i;Sz[i] = 1;
	}
	REP(i, 1, m)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		x = Find(x);y = Find(y);
		if (x != y)
		{
			int sx = Sz[x], sy = Sz[y];
			if (sx > sy) swap(x, y), swap(sx, sy);
			Fa[x] = y;Sz[y] += Sz[x];
			id[++k] = i;
			modify(fa[k - 1], fa[k], 1, n, x, y);//fa[x] = y;
			modify(sz[k - 1], sz[k], 1, n, y, sx + sy);//sz[y] += sz[x];
		}
	}
	cin >> q;
	REP(i, 1, q) scanf("%d%d%d", x + i, y + i, z + i);
	REP(i, 1, q) QAQ[i] = i;
	solve(1, k, 1, q);
	REP(i, 1, q) printf("%d\n", ans[i]);
	return 0;
}
