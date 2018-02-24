#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 100010;

#define ls p << 1
#define rs p << 1 | 1
#define mid ((l + r) >> 1)
#define lson ls, l, mid
#define rson rs, mid + 1, r

template <typename T> T read()
{
	T ans(0), p(1);
	char c = getchar();
	while (!isdigit(c)) {
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c)) {
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}
int n, ans;

struct seg_tree
{
	int Max[maxn << 2];
	inline void init() {memset(Max, 0, sizeof(Max));}
	inline void count(int p, int l, int r, int L, int R, int h)
	{
		if (L <= l && r <= R)
			if (Max[p] == -1)
			{
				if (L <= mid) count(lson, L, R, h);
				if (R >  mid) count(rson, L, R, h);
			}
			else {if (Max[p] <= h) ans += r - l + 1;}
		else
		{
			if (L <= mid) count(lson, L, R, h);
			if (R >  mid) count(rson, L, R, h);
		}
		
	}
	inline void update(int p, int l, int r, int L, int R, int h)
	{
		if (L <= l && r <= R)
			if (Max[p] == -1)
			{
				if (L <= mid) update(lson, L, R, h);
				if (R >  mid) update(rson, L, R, h);
			}
			else
			{
				Max[ls] = Max[rs] = max(Max[p], h);
				Max[p] = -1;
			}
		else
		{
			if (L <= mid) update(lson, L, R, h);
			if (R >  mid) update(rson, L, R, h);
			Max[p] = Max[ls] ^ Max[rs] ? -1 : Max[ls];
		}
	}
	inline void PRINT(int p, int l, int r)
	{
		if (Max[p] == -1) PRINT(lson), PRINT(rson);
		else REP(i, l, r) fprintf(stderr, "%d ", Max[p]);
	}
}ST;

int h[maxn], l[maxn], r[maxn];

int main()
{
#ifdef CraZYali
	freopen("4108.in", "r", stdin);
	freopen("4108.out", "w", stdout);
	freopen("stderr", "w", stderr);
#endif
	register int T = read<int>();
	while (T--)
	{
		ans = 0;ST.init();
		int len = -1;
		n = read<int>();
		REP(i, 1, n)
		{
			l[i] = read<int>();
			r[i] = read<int>() - 1;
			h[i] = read<int>();
			chkmax(len, r[i]);
		}
		REP(i, 1, n)
		{
			ST.count(1, 1, len, l[i], r[i], h[i]);
			ST.update(1, 1, len, l[i], r[i], h[i]);
		}
		printf("%d\n", ans);
	}

	return 0;
}
