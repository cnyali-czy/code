#pragma GCC optimize("Ofast", "inline")
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTIONN__, __LINE__)

#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 50000 + 10, base = 131;

int n, a[maxn], id[maxn];

int lst[maxn], app[maxn];

vector <int> op[maxn], pos[maxn];
unsigned long long bin[maxn];

	template <typename T>
inline T read()
{
	register T ans(0), flag(1);
	register char c(getchar());
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

struct Hash
{
	unsigned long long sum;
	int len;
	inline Hash(unsigned long long sum = 0, int len = 0) : sum(sum), len(len) {}
	inline Hash operator +  (const Hash &B) const {return Hash(sum + bin[len] * B.sum, len + B.len);}
	inline bool operator == (const Hash &B) const {return sum == B.sum && len == B.len;}
};

const int maxN = 2e6 + 10;
int ls[maxN], rs[maxN], rt[maxn], cur;
Hash sum[maxN];
#define lson ls[p], l, mid
#define rson rs[p], mid + 1, r
#define mid (l + r >> 1)
void build(int &p, int l, int r)
{
	p = ++cur;
	if (l == r) sum[p] = Hash(lst[l] ? l - lst[l] : 0, 1);
	else
	{
		build(lson);
		build(rson);
		sum[p] = sum[ls[p]] + sum[rs[p]];
	}
}
void update(int pre, int &p, int l, int r, int pos)
{
	p = ++cur;
	ls[p] = ls[pre];
	rs[p] = rs[pre];
	if (l == r) sum[p] = Hash(0, 1);
	else
	{
		if (pos <= mid)	update(ls[pre], lson, pos);
		else			update(rs[pre], rson, pos);
		sum[p] = sum[ls[p]] + sum[rs[p]];
	}
}
Hash query(int p, int l, int r, int L, int R)
{
	if (L <= l && r <= R) return sum[p];
	else
	{
		if (R <= mid) return query(lson, L, R);
		if (L >  mid) return query(rson, L, R);
		return query(lson, L, R) + query(rson, L, R);
	}
}
#undef mid
inline int calc(int x, int y)
{
	int l(1), r(min(n - x + 1, n - y + 1));
	while (l <= r)
	{
		int mid = l + r >> 1;
		if (query(rt[x], 1, n, x, x + mid - 1) == query(rt[y], 1, n, y, y + mid - 1))
			l = mid + 1;
		else
			r = mid - 1;
	}
	return l - 1;
}
inline int askp(int p, int v)
{
	return (*lower_bound(pos[v].begin(), pos[v].end(), p)) - p;
}
inline bool cmp(int x, int y)
{
	int k = calc(x, y);
	return x + k > n ? 1 : y + k > n ? 0 : askp(x, a[x + k]) < askp(y, a[y + k]);
}

inline void init(int n)
{
	bin[0] = 1;
	REP(i, 1, n) bin[i] = bin[i-1] * base;
}
int main()
{
#ifdef CraZYali
	freopen("waterflow-std.in", "r", stdin);
	freopen("waterflow-std.out", "w", stdout);
#endif
	cin >> n;
	init(n);
	REP(i, 1, n)
	{
		a[i] = read<int>();
		op[lst[i] = app[a[i]]].emplace_back(i);
		app[a[i]] = i;
		pos[a[i]].emplace_back(i);
	}
	build(rt[1], 1, n);
	REP(i, 1, n)
	{
		rt[i + 1] = rt[i];
		for (auto j : op[i]) update(rt[i + 1], rt[i + 1], 1, n, j);
	}
	REP(i, 1, n) id[i] = i;
	stable_sort(id + 1, id + 1 + n, cmp);
	long long ans = 1ll * n * (n + 1) >> 1;
	REP(i, 1, n - 1) ans -= calc(id[i], id[i+1]);
	cout << ans << endl;
	return 0;
}
