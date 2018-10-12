#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <iostream>
#include <cstdio>

#define int long long
using namespace std;
const int maxn = 500000 + 10;

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

#define ls p << 1
#define rs p << 1 | 1
#define mid (l + r >> 1)
#define lson ls, l, mid
#define rson rs, mid + 1, r
#define THIS p, l, r

struct SMT
{
	int s[maxn << 2], lmax[maxn << 2], rmax[maxn << 2], allmax[maxn << 2];

	void pushup(int p, int l, int r)
	{
		s[p] = s[ls] + s[rs];
		lmax[p] = max(lmax[ls], s[ls] + lmax[rs]);
		rmax[p] = max(rmax[rs], s[rs] + rmax[ls]);
		allmax[p] = max(allmax[ls], allmax[rs]);
		chkmax(allmax[p], rmax[ls] + lmax[rs]);
	}

	void build(int p, int l, int r)
	{
		if (l == r) s[p] = allmax[p] = lmax[p] = rmax[p] = read<int>();
		else
		{
			build(lson);
			build(rson);
			pushup(THIS);
		}
	}

	void update(int p, int l, int r, int pos, int val)
	{
		if (l == pos && r == pos) s[p] = allmax[p] = lmax[p] = rmax[p] = val;
		else
		{
			if (pos <= mid) update(lson, pos, val);
			else update(rson, pos, val);
			pushup(THIS);
		}
	}

	int askl(int p, int l, int r, int L, int R)
	{
		if (L == l && r == R) return lmax[p];
		else
		{
			if (L  > mid) return askl(rson, L, R);
			if (R <= mid) return askl(lson, L, R);
			return max(askl(lson, L, mid), s[ls] + askl(rson, mid + 1, R));
		}
	}

	int askr(int p, int l, int r, int L, int R)
	{
		if (L == l && r == R) return rmax[p];
		else
		{
			if (L  > mid) return askr(rson, L, R);
			if (R <= mid) return askr(lson, L, R);
			return max(askr(rson, mid + 1, R), s[rs] + askr(lson, L, mid));
		}
	}
	
	int query(int p, int l, int r, int L, int R)
	{
		if (L == l && r == R) return allmax[p];
		else
		{
			if (R <= mid) return query(lson, L, R);
			if (L >  mid) return query(rson, L, R);
			int res = max(query(lson, L, mid), query(rson, mid + 1, R));
			return max(res, askr(lson, L, mid) + askl(rson, mid + 1, R));
		}
	}
}T;

int m, n, k;

signed main()
{
#ifdef CraZYali
	freopen("4101.in", "r", stdin);
	freopen("4101.out", "w", stdout);
#endif
	cin >> n >> m;
	T.build(1, 1, n);
	while (m --> 0)
	{
		register int opt = read<int>(), l = read<int>(), r = read<int>();
		if (opt == 1)
		{
			if (l > r) swap(l, r);
			printf("%lld\n", T.query(1, 1, n, l, r));
		}
		else T.update(1, 1, n, l, r);
	}
	return 0;
}
