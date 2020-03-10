#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < b ? a = b : a)
#define chkmin(a, b) (a > b ? a = b : a)

#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;
const int lim = (1 << 30) - 1, maxN = 2e7, maxn = 1e5 + 10;

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

int k, n, m;

int rt, ls[maxN], rs[maxN], cur, s[maxN], tag[maxN], ans[maxN];

#define lson ls[p], l, mid
#define rson rs[p], mid + 1, r
#define mid (l + r >> 1)

struct Query
{
	int l, r, opt;
	Query(int l = 0, int r = 0, int opt = 0) : l(l), r(r), opt(opt) {}
};
vector <Query> vec[maxn << 1];

inline int lowbit(int x) {return x & -x;}
inline int calc(int l, int r) {return lowbit(l) ^ (r - l + 1 >> 1);}

inline void pushup(int p, int l, int r)
{
	s[p] = (tag[p] ? r - l + 1: s[ls[p]] + s[rs[p]]);
	ans[p] = (tag[p] ? calc(l, r) : ans[ls[p]] ^ ans[rs[p]]);
}

void update(int &p, int l, int r, int L, int R, int val)
{
	if (!p) p = ++cur;
	if (L <= l && r <= R) tag[p] += val;
	else
	{
		if (L <= mid) update(lson, L, R, val);
		if (R >  mid) update(rson, L, R, val);
	}
	pushup(p, l, r);
}
int query(int p, int l, int r, int L, int R)
{
	if (!p) return 0;
	if (tag[p]) return R - l + 1;
	if (L <= l && r <= R) return s[p];
	else
	{
		if (R <= mid) return query(lson, L, R);
		if (L >  mid) return query(rson, L, R);
		return query(lson, L, mid) + query(rson, mid + 1, R);
	}
}
int query(int p, int l, int r, int L, int R, bool flag)
{
	if (tag[p]) flag = 1;
	if (L <= l && r <= R) return flag ? calc(l, r) : ans[p];
	else
	{
		if (R <= mid) return query(lson, L, R, flag);
		if (L >  mid) return query(rson, L, R, flag);
		return query(lson, L, R, flag) ^ query(rson, L, R, flag);
	}
}

int main()
{
#ifdef CraZYali
	file("B");
#endif
	k = read<int>();n = read<int>();m = read<int>();
	REP(i, 1, k)
	{
		int x1(read<int>()), y1(read<int>()), x2(read<int>()), y2(read<int>());
		vec[x1].emplace_back(y1, y2, 1);
		vec[x2 + 1].emplace_back(y1, y2, -1);
	}
	int ans = 0;
	REP(i, 1, n)
	{
		for (auto j : vec[i]) update(rt, 0, lim, j.l, j.r, j.opt);
		if (query(rt, 0, lim, 1, min(i, m)) & 1) ans ^= lowbit(i);
		if (i < m) ans ^= query(rt, 0, lim, i + 1, m, 0);
	}
	cout << ans << '\n';
	return 0;
}
