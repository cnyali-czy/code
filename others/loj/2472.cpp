/*
	Problem:	2472.cpp
	Time:		2020-03-02 22:48
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 5e5 + 10, maxN = maxn << 2, inf = 1e9;

template <typename T>
inline T read()
{
	T ans = 0, flag = 1;
	char c = getchar();
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

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n;double k;
int a[maxn], fa[maxn];

int ls[maxN], rs[maxN], Min[maxN], tag[maxN], rt;
#define ls p << 1
#define rs p << 1 | 1
#define lson ls, l, mid
#define rson rs, mid + 1, r
#define mid (l + r >> 1)

inline void maintain(int p, int val)
{
	Min[p] += val;
	tag[p] += val;
}

inline void pushdown(int p)
{
	maintain(ls, tag[p]);
	maintain(rs, tag[p]);
	tag[p] = 0;
}

void update(int p, int l, int r, int L, int R, int val)
{
	if (L <= l && r <= R) maintain(p, val);
	else
	{
		if (tag[p]) pushdown(p);
		if (L <= mid)	update(lson, L, R, val);
		if (R >  mid)   update(rson, L, R, val);
		Min[p] = min(Min[ls], Min[rs]);
	}
}
int query(int p, int l, int r, int k)
{
	if (!p) return 0;
	if (l == r) return l + (Min[p] < k);
	else
	{
		if (tag[p]) pushdown(p);
		if (k <= Min[rs])	return query(lson, k);
		else				return query(rson, k);
	}
}
void build(int p, int l, int r)
{
	if (l == r) Min[p] = l;
	else
	{
		build(lson);
		build(rson);
		Min[p] = min(Min[ls], Min[rs]);
	}
}
int cnt[maxn], siz[maxn], ans[maxn];

int main()
{
#ifdef CraZYali
	file("2472");
#endif
	cin >> n >> k;
	REP(i, 1, n)	
	{
		a[i] = read<int>();
		fa[i] = (int)(i / k);
	}
	sort(a + 1, a + 1 + n, greater <int> ());
	DEP(i, n - 1, 1)
		if (a[i] == a[i + 1]) cnt[i] = cnt[i + 1] + 1;
		else cnt[i] = 0;
	DEP(i, n, 1)
	{
		siz[i]++;
		siz[fa[i]] += siz[i];
	}
	build(1, 1, n);
	REP(i, 1, n)
	{
		if (fa[i] && fa[i] ^ fa[i-1]) update(1, 1, n, ans[fa[i]], n, siz[fa[i]] - 1);
		int x = query(1, 1, n, siz[i]);
		x += cnt[x];cnt[x]++;
		x -= (cnt[x] - 1);
		ans[i] = x;
		update(1, 1, n, x, n, - siz[i]);
	}
	REP(i, 1, n) cout << a[ans[i]] << (i == n ? '\n' : ' ');
	return 0;
}
