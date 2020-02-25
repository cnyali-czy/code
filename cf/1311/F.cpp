/*
	Problem:	E.cpp
	Time:		2020-02-24 23:21
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
const int maxn = 2e5 + 10, maxN = 2e7, inf = 1e8;

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
/*
#define lson ls[p], l, mid
#define rson rs[p], mid + 1, r
#define mid (l + r >> 1)

int ls[maxN], rs[maxN], s[maxN], rt, cur;
long long val[maxN];
void update(int &p, int l, int r, int pos, int val)
{
	if (!p) p = ++cur;
	s[p]++;::val[p] += val;
	if (l == r) return;
	else if (pos <= mid)	update(lson, pos, val);
	else					update(rson, pos, val);
}
int qs(int p, int l, int r, int L, int R)
{
	if (!p) return 0;
	if (L <= l && r <= R) return s[p];
	else
	{
		if (R <= mid) return qs(lson, L, R);
		if (L >  mid) return qs(rson, L, R);
		return qs(lson, L, R) + qs(rson, L, R);
	}
}
long long qv(int p, int l, int r, int L, int R)
{
	if (!p) return 0;
	if (L <= l && r <= R) return val[p];
	else
	{
		if (R <= mid) return qv(lson, L, R);
		if (L >  mid) return qv(rson, L, R);
		return qv(lson, L, R) + qv(rson, L, R);
	}
}
*/
int n, m, x[maxn], v[maxn], id[maxn], b[maxn];

long long cv[maxn];
int cs[maxn];
long long qv(int x)
{
	long long res = 0;
	while (x <= m) res += cv[x], x += x & -x;
	return res;
}
int qs(int x)
{
	int res = 0;
	while (x <= m) res += cs[x], x += x & -x;
	return res;
}
void update(int x, int v)
{
	while (x > 0)
	{
		cs[x]++;
		cv[x] += v;
		x &= (x - 1);
	}
}

int main()
{
#ifdef CraZYali
	file("F");
#endif
	n = read<int>();
	REP(i, 1, n) x[id[i] = i] = read<int>();
	REP(i, 1, n) b[i] = v[i] = read<int>();
	sort(id + 1, id + 1 + n, [&](int x, int y) {return ::x[x] > ::x[y];});
	m = n;
	sort(b + 1, b + 1 + n);
	m = unique(b + 1, b + 1 + n) - b - 1;
	long long ans = 0;
	REP(I, 1, n)
	{
		int i = id[I];
		v[i] = lower_bound(b + 1, b + 1 + m, v[i]) - b;
		ans += qv(v[i]) - 1ll * qs(v[i]) * x[i];
		update(v[i], x[i]);
	}
	cout << ans << '\n';
	return 0;
}
