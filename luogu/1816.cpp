#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 1e5 + 10, inf = 1e9;

template <typename T> T read()
{
	T ans(0), p(1);
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}

int m, n, k;

#define ls p << 1
#define rs p << 1 | 1
#define mid (l + r >> 1)
#define lson ls, l, mid
#define rson rs, mid + 1, r

struct seg_tree
{
	int Min[maxn << 2];
	seg_tree() {memset(Min, 127/3, sizeof(Min));}
	inline void build(int p, int l, int r)
	{
		if (l == r) Min[p] = read<int>();
		else
		{
			build(lson);
			build(rson);
			Min[p] = min(Min[ls], Min[rs]);
		}
	}
	inline int query(int p, int l, int r, int L, int R)
	{
		if (L <= l && r <= R) return Min[p];
		else
		{
			int lans, rans;
			lans = rans = inf;
			if (L <= mid) lans = query(lson, L, R);
			if (R >  mid) rans = query(rson, L, R);
			return min(lans, rans);
		}
	}
}T;

int main()
{
#ifdef CraZYali
	freopen("1816.in", "r", stdin);
	freopen("1816.out", "w", stdout);
#endif
	n = read<int>();
	m = read<int>();
	T.build(1, 1, n);
	while (m--)
	{
		register int l(read<int>()), r(read<int>());
		printf("%d ", T.query(1, 1, n, l, r));
	}

	return 0;
}
