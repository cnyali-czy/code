#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 2e5 + 10;

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

int n, m, q, a[maxn], b[maxn];
int Sum[maxn << 5], L[maxn << 5], R[maxn << 5], T[maxn], cur;

#define mid (l + r >> 1)
#define ls p << 1
#define rs p << 1 | 1
#define lson l, mid
#define rson mid + 1, r

int build(int l, int r)
{
	int rt = ++cur;
	if (l < r)
	{
		L[rt] = build(lson);
		R[rt] = build(rson);
	}
	return rt;
}
int update(int pre, int l, int r, int x)
{
	int rt = ++cur;
	L[rt] = L[pre];R[rt] = R[pre];Sum[rt] = Sum[pre] + 1;
	if (l < r)
		if (x <= mid) L[rt] = update(L[pre], lson, x);
		else R[rt] = update(R[pre], rson, x);
	return rt;
}
int query(int u, int v, int l, int r, int k)
{
	if (l >= r) return l;
	int x = Sum[L[v]] - Sum[L[u]];
	if (x >= k) return query(L[u], L[v], lson, k);
	else return query(R[u], R[v], rson, k - x);
}

int main()
{
#ifdef CraZYali
	freopen("3834-new-new.in", "r", stdin);
	freopen("std.out", "w", stdout);
#endif
	cin >> n >> q;
	REP(i, 1, n) a[i] = b[i] = read<int>();
	sort(b + 1, b + 1 + n);
	m = unique(b + 1, b + 1 + n) - b - 1;
	T[0] = build(1, m);
	REP(i, 1, n) T[i] = update(T[i-1], 1, m, lower_bound(b + 1, b + 1 + m, a[i]) - b);
	while (q --> 0)
	{
		int x(read<int>()), y(read<int>()), z(read<int>());
		printf("%d\n", b[query(T[x-1],T[y],1,m,z)]);
	}
	return 0;
}
