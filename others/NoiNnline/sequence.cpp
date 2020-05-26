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
i64 query(int p, int l, int r, int L, int R)
{
	if (L <= l && r <= R)
	{
		i64 res = sum[p];
		maintain(p, l, r, 1);
		return res;
	}
	else
	{
		if (tag[p]) pushdown(p, l, r);
		i64 res;
		if (R <= mid) res = query(lson, L, R);
		else if (L >  mid) res = query(rson, L, R);
		else res = query(lson, L, R) + query(rson, L, R);
		sum[p] = sum[ls] + sum[rs];
		return res;
	}
}
#undef mid
int Lower_bound(int x)
{
	int l = 1, r = m;
	while (l <= r)
	{
		int mid = l + r >> 1;
		if (b[mid] == x) return mid;
		else if (b[mid] < x) l = mid + 1;
		else r = mid - 1;
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
		a[i] = Lower_bound(a[i]);
		i64 v = query(1, 1, n, lst[a[i]] + 1, i) % MOD;
		(res += i - lst[a[i]] + 2 * v) %= MOD;
		ans += res;
		lst[a[i]] = i;
	}
	cout << (ans % MOD + MOD) % MOD << '\n';
	return 0;
}
