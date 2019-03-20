#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 2e5 + 10;

template <typename T> inline T read()
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

int a[maxn], b[maxn], n, m, q;

#define mid (l + r >> 1)
#define lson p -> ls, l, mid
#define rson p -> rs, mid + 1, r

struct node *null;

struct node
{
	node *ls, *rs;int sum;
	node() : ls(null), rs(null), sum(0){}
}*rt[maxn];

void build(node *pre, node *&p, int l, int r, int val)
{
	p = new node();
	p -> ls = pre -> ls;
	p -> rs = pre -> rs;
	p -> sum = pre -> sum + 1;
	if (l >= r) return;
	else if (val <= mid)
		build(pre -> ls, lson, val);
	else
		build(pre -> rs, rson, val);
}


int query(node *u, node *v, int l, int r, int k)
{
	if (l >= r) return l;
	int x = v -> ls -> sum - u -> ls -> sum;
	if (x < k) return query(u -> rs, v -> rs, mid + 1, r, k - x);
	else return query(u -> ls, v -> ls, l, mid, k);
}

int main()
{
#ifdef CraZYali
	freopen("3834-new-new.in", "r", stdin);
	freopen("3834-new-new.out", "w", stdout);
#endif
	cin >> n >> q;
	REP(i, 1, n) b[i] = a[i] = read<int>();
	sort(b + 1, b + 1 + n);
	m = unique(b + 1, b + 1 + n) - b - 1;
	rt[0] = null = new node();
	null -> ls = null;null -> rs = null;null -> sum = 0;
	REP(i, 1, n)
	{
		rt[i] = null;
		build(rt[i-1], rt[i], 1, m, lower_bound(b + 1, b + 1 + m, a[i]) - b);
	}
	while (q --> 0)
	{
		int L = read<int>(), R = read<int>(), k = read<int>();
		printf("%d\n", b[query(rt[L-1], rt[R], 1, m, k)]);
	}
	return 0;
}
