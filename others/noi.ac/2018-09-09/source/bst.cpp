#define REP(i, s, e) for(register int i = s; i <= e ; i++)

#include <bits/stdc++.h>

using namespace std;

#define mid (l + r >> 1)
#define ls p << 1
#define rs p << 1 | 1
#define lson ls, l, mid
#define rson rs, mid + 1, r

const int Max = 8000000 + 10;

int lazy[Max];
bool mark[Max];

inline void doit(int p, int depth, int mask)
{
	lazy[p] ^= mask;
	if (mask & (1 << depth)) mark[p] ^= 1;
}
inline void push_down(int p, int depth)
{
	doit(ls, depth + 1, lazy[p]);
	doit(rs, depth + 1, lazy[p]);
	lazy[p] = 0;
}
void update(int p, int l, int r, int L, int R, int d, int depth)
{
	if (L <= l && r <= R)
	{
		doit(p, depth, 1 << d);
		return;
	}
	if (lazy[p]) push_down(p, depth);
	if (!mark[p])
	{
		if (L <= mid)
			update(lson, L, R, d, depth + 1);
		if (R >  mid)
			update(rson, L, R, d, depth + 1);
	}
	else
	{
		if (L <= mid)
			update(rson, L - l + mid + 1, R - l + mid + 1, d, depth + 1);
		if (R >  mid)
			update(lson, L - mid - 1 + l, R - mid - 1 + l, d, depth + 1);
	}
}
int query(int p, int l, int r, int pos, int depth)
{
	if (l == r) return l;
	if (lazy[p]) push_down(p, depth);
	if (!mark[p]) return pos <= mid ? query(lson, pos, depth + 1) : query(rson, pos, depth + 1);
	else return pos <= mid ? query(rson, pos - l + mid + 1, depth + 1) : query(lson, pos - mid - 1 + l, depth + 1);
}

int n, m, k;

int main()
{
#ifdef CraZYali
	freopen("bst.in", "r", stdin);
	freopen("bst.out", "w", stdout);
#endif
	cin >> n >> m;
	while (m --> 0)
	{
		register int opt;
		scanf("%d", &opt);
		if (opt == 2)
		{
			register int x;
			scanf("%d", &x);
			printf("%d\n", query(1, 0, (1 << n) - 1, x - 1, 0) + 1);
		}
		else
		{
			register int l, r;
			scanf("%d%d", &l, &r);
			REP(i, 0, n - 1)
			{
				register int x = max(l, 1 << i) - (1 << i), y = min(r, (1 << i + 1) - 1) - (1 << i);
				if (x <= y) update(1, 0, (1 << i) - 1, x, y, i, 0);
			}
		}
	}
	return 0;
}
