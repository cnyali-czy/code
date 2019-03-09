#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/extc++.h>

using namespace std;
using namespace __gnu_pbds;
const int maxn = 500000 + 10;

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

int n, m, k;
tree <int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> T[maxn];
void insert(int x, int y) {T[x].insert(y);}
void del(int x, int y) {T[x].erase(y);}
int query(int x, int y) {return T[x].order_of_key(y);}

int a[maxn];

int Max[maxn << 2], rt[maxn], L[maxn << 2], R[maxn << 2];
#define ls p << 1
#define rs p << 1 | 1
#define mid (l + r >> 1)
#define lson ls, l, mid
#define rson rs, mid + 1, r

int count(int x, int l, int r)
{
	if (r - l <= 30)
	{
		int res = 0;
		REP(i, l, r) res += a[i] == x;
		return res;
	}
	else return query(x, r + 1) - query(x, l);
}
void maintain(int p, int l, int r)
{
	if (Max[ls] && count(Max[ls], l, r) * 2 >= r - l + 1) Max[p] = Max[ls];
	else if (Max[rs] && count(Max[rs], l, r) * 2 >= r - l + 1) Max[p] = Max[rs];
	else Max[p] = 0;
}
void build(int p, int l, int r)
{
	L[p] = l;R[p] = r;
	if (l == r) insert(Max[rt[l] = p] = a[l], l);
	else
	{
		build(lson);
		build(rson);
		maintain(p, l, r);
	}
}

int ql, qr, ans;
void modify(int x)
{
	if (a[x] == ans) return;
	del(a[x], x);
	insert(a[x] = ans, x);
	Max[rt[x]] = ans;
	int now = rt[x];
	while (now >>= 1) maintain(now, L[now], R[now]);
}
bool check(int p, int l, int r)
{
	if (ql <= l && r <= qr)
	{
		if (Max[p] && count(Max[p], ql, qr) * 2 > qr - ql + 1) {ans = Max[p];return 1;}
		return 0;
	}
	if (ql <= mid && check(lson)) return 1;
	if (qr >  mid && check(rson)) return 1;
	return 0;

}

int main()
{
#ifdef CraZYali
	freopen("3765.in", "r", stdin);
	freopen("3765.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, n) a[i] = read<int>();
	build(1, 1, n);
	while (m --> 0)
	{
		ql = read<int>();qr = read<int>();
		if (!check(1, 1, n)) ans = read<int>();
		else read<int>();
		printf("%d\n", ans);
		int ret = read<int>();
		while (ret --> 0) modify(read<int>());
	}
	printf("%d", Max[1] ? Max[1] : -1);
	return 0;
}
