/*
 * File Name:	3674.cpp
 * Author	:	CraZYali
 * Year		:	2019.09.15 21:33
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 2e5 + 10, LOG = 19, maxm = 2e5 + 10, maxnode = maxn + maxn + maxm + LOG * maxn;

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

#define mid (l + r >> 1)
#define lson ls[p], l, mid
#define rson rs[p], mid + 1, r

int nowbuild[maxn];

int n, m, tim;

struct array
{
	int rt[maxm], clock, cur;
	int ls[maxnode], rs[maxnode], val[maxnode];
	inline void clear()
	{
		rt[0] = cur = clock = 0;
		ls[0] = rs[0] = 0;
	}
	array() {clear();}
	void insert(int pre, int &p, int l, int r, int pos, int v)
	{
		p = ++cur;
		ls[p] = ls[pre];
		rs[p] = rs[pre];
		if (l == r) val[p] = v;
		else if (pos <= mid) insert(ls[pre], lson, pos, v);
		else insert(rs[pre], rson, pos, v);
	}
	void build(int &p, int l, int r)
	{
		p = ++cur;
		if (l == r) val[p] = nowbuild[l];
		else
		{
			build(lson);
			build(rson);
		}
	}
	inline void init()
	{
		clear();
		build(rt[0], 1, n);
	}
	int query(int p, int l, int r, int pos)
	{
		return l == r ? val[p] : pos <= mid ? query(lson, pos) : query(rson, pos);
	}
	inline int query(int pos) {return query(rt[tim], 1, n, pos);}
	inline int operator [] (int x) {return query(x);}
	inline void extend(int pos, int val)
	{
		clock++;
		insert(rt[clock-1], rt[clock], 1, n, pos, val);
	}
	inline void back(int x)
	{
		rt[++clock] = ++cur;
		ls[rt[clock]] = ls[rt[x]];
		rs[rt[clock]] = rs[rt[x]];
		val[rt[clock]] = val[rt[x]];
	}
}fa, siz;

inline void init()
{
	REP(i, 1, n) nowbuild[i] = i;
	fa.init();
	REP(i, 1, n) nowbuild[i] = 1;
	siz.init();
}

inline int find(int x)
{
	int f = fa[x];
	return f == x ? x : find(f);
}
inline void uni(int x, int y)
{
	x = find(x);y = find(y);
	if (x == y) return;
	int sizx = siz[x], sizy = siz[y];
	if (sizx < sizy) swap(x, y);
	fa.extend(x, y);
	siz.extend(y, sizx + sizy);
}
inline void back(int x)
{
	fa.back(x);
	siz.back(x);
}

int main()
{
#ifdef CraZYali
	file("3674");
#endif
	cin >> n >> m;
	init();
	REP(i, 1, m)
	{
		int opt = read<int>();
		if (opt == 1) uni(read<int>(), read<int>());
		else if (opt == 2) back(read<int>());
		else printf("%d\n", find(read<int>()) == find(read<int>())), back(i-1);
		++tim;
	}
	return 0;
}
