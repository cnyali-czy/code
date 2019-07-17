#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 2e5 + 10, maxN = 18 * maxn;

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

int n, q, m, a[maxn], b[maxn];

int rt[maxN], ls[maxN], rs[maxN], sum[maxN], cur;
#define mid (l + r >> 1)
#define lson ls[p], l, mid
#define rson rs[p], mid + 1, r
void update(int pre, int &p, int l, int r, int pos)
{
	p = ++cur;
	ls[p] = ls[pre];
	rs[p] = rs[pre];
	sum[p] = sum[pre] + 1;
	if (l < r)
		if (pos <= mid) update(ls[pre], lson, pos);
		else update(rs[pre], rson, pos);
}
int query(int u, int v, int l, int r, int k)
{
	if (l >= r) return l;
	int s = sum[ls[v]] - sum[ls[u]];
	if (s >= k) return query(ls[u], ls[v], l, mid, k);
	else return query(rs[u], rs[v], mid + 1, r, k - s);
}

int main()
{
#ifdef CraZYali
	freopen("2104.in", "r", stdin);
	freopen("2104.out", "w", stdout);
#endif
	cin >> n >> q;
	REP(i, 1, n) a[i] = b[i] = read<int>();
	sort(b + 1, b + 1 + n);
	m = unique(b + 1, b + 1 + n) - b - 1;
	REP(i, 1, n) update(rt[i-1], rt[i], 1, m, lower_bound(b + 1, b + 1 + m, a[i]) - b);
	while (q --> 0)
	{
		int l(read<int>()), r(read<int>()), k(read<int>());
		printf("%d\n", b[query(rt[l-1], rt[r], 1, m, k)]);
	}
	return 0;
}
