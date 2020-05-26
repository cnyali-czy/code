#define REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;

template <typename T> T read()
{
	T ans(0), flag(1);
	char c(getchar());
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

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}
const int maxn = 1e6 + 10;
int n, a[maxn], b[maxn], m, lst[maxn];
#define i64 long long
#define ls p << 1
#define rs p << 1 | 1
#define lson ls, l, mid
#define rson rs, mid + 1, r
#define mid (l + r >> 1)
const int MOD = 1e9 + 7;
i64 tag[maxn << 2], sum[maxn << 2];
void maintain(int p, int l, int r, i64 val)
{
	sum[p] += (r - l + 1) * val;
	tag[p] += val;
}
void pushdown(int p, int l, int r)
{
	maintain(lson, tag[p]);
	maintain(rson, tag[p]);
	tag[p] = 0;
}
void update(int p, int l, int r, int L, int R)
{
	if (L <= l && r <= R) maintain(p, l, r, 1);
	else
	{
		if (tag[p]) pushdown(p, l, r);
		if (L <= mid) update(lson, L, R);
		if (R >  mid) update(rson, L, R);
		sum[p] = sum[ls] + sum[rs];
	}
}
i64 query(int p, int l, int r, int L, int R)
{
	if (!sum[p]) return 0;
	if (L <= l && r <= R) return sum[p];
	else
	{
		if (tag[p]) pushdown(p, l, r);
		if (R <= mid) return query(lson, L, R);
		if (L >  mid) return query(rson, L, R);
		return query(lson, L, R) + query(rson, L, R);
	}
}

int main()
{
	file("sequence");
	n = read<int>();
	REP(i, 1, n) a[i] = b[i] = read<int>();
	sort(b + 1, b + 1 + n);
	m = unique(b + 1, b + 1 + n) - b - 1;
	i64 ans(0), res(0);
	REP(i, 1, n)
	{
		a[i] = lower_bound(b + 1, b + 1 + m, a[i]) - b;
		i64 v = query(1, 1, n, lst[a[i]] + 1, i) % MOD;
		(res += i - lst[a[i]] + 2 * v) %= MOD;
		ans += res;
		update(1, 1, n, lst[a[i]] + 1, i);
		lst[a[i]] = i;
	}
	cout << (ans % MOD + MOD) % MOD << '\n';
	return 0;
}
