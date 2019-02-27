#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 1e6 + 10, maxm = 1e6 + 10;

template <typename T> T read()
{
	T ans = 0, p = 1;
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

struct node
{
	node *ls, *rs;
	int val;
}*T[maxn];

#define mid (l + r >> 1)
int a[maxn];
void build(node *&p, int l, int r)
{
	if (l > r) return;
	p = new node();
	if (l == r) {p -> val = a[l];return;}
	build(p -> ls, l, mid);
	build(p -> rs, mid + 1, r);
}

void update(node *pre, node *&p, int l, int r, int pos, int val)
{
	if (l > r) return;
	p = new node();p -> ls = pre -> ls;p -> rs = pre -> rs;
	if (l == r) {p -> val = val;return;}
	if (pos <= mid) update(pre -> ls, p -> ls, l, mid, pos, val);
	else update(pre -> rs, p -> rs, mid + 1, r, pos, val);
}

int query(node *p, int l, int r, int pos)
{
	if (l > r) return 0;
	if (l == r) return p -> val;
	if (pos <= mid)	return query(p -> ls, l, mid, pos);
	else			return query(p -> rs, mid + 1, r, pos);
}

int n, m, cur;

int main()
{
#ifdef CraZYali
	freopen("3919.in", "r", stdin);
	freopen("3919.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, n) a[i] = read<int>();
	build(T[0], 1, n);
	while (m --> 0)
	{
		int x(read<int>()), opt(read<int>()), loc(read<int>());
		if (opt == 1) update(T[x], T[++cur], 1, n, loc, read<int>());
		else {T[++cur] = T[x];printf("%d\n", query(T[x], 1, n, loc));}
	}
	return 0;
}
