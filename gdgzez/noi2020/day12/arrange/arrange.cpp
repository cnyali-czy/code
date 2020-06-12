/*
	Problem:	arrange.cpp
	Time:		2020-06-12 08:43
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cassert>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 2e5 + 10;

int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

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

int n, k, a[maxn];

int M, siz[maxn], cnt[maxn], m1[maxn], m2[maxn];

int dfs_clock, qaq, back[maxn], fa[maxn];
pair <int, int> dfn[maxn];

void dfs0(int x)
{
	back[++qaq] = x;
	siz[x] = 1;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa[x])
	{
		fa[to[i]] = x;
		dfn[++dfs_clock] = make_pair(x, to[i]);
		dfs0(to[i]);
		siz[x] += siz[to[i]];
	}
}
bool flag;

bool judge(int mid)
{
	M = mid;
	REP(i, 1, n) cnt[i] = 1, m1[i] = m2[i] = 0;
	DEP(i, n, 2)
	{
		int x = back[i];
		cnt[x] += m1[x];
		cnt[x] *= (a[x] >= M);
		if (cnt[x] == siz[x]) cnt[fa[x]] += cnt[x];
		else if (cnt[x] >= m1[fa[x]]) m2[fa[x]] = m1[fa[x]], m1[fa[x]] = cnt[x];
		else chkmax(m2[fa[x]], cnt[x]);
	}
	cnt[1] += m1[1];
	cnt[1] *= (a[1] >= M);
	if (cnt[1] >= k) return 1;
	REP(i, 1, dfs_clock)
	{
		int x = dfn[i].first, y = dfn[i].second;
		if (cnt[x] >= k) return 1;
		int cx = cnt[x];
		if (a[x] >= M)
			if (cnt[y] == siz[y]) cx -= cnt[y];
			else if (cnt[y] == m1[x]) cx -= m1[x] - m2[x];
		if (a[y] >= M)
			if (cx == n - siz[y]) cnt[y] += cx;
			else 
			{
				cnt[y] -= m1[y];
				if (cx >= m1[y]) m2[y] = m1[y], m1[y] = cx;
				else chkmax(m2[y], cx);
				cnt[y] += m1[y];
			}
		if (cnt[y] >= k) return 1;
	}
	return 0;
}

int main()
{
#ifdef CraZYali
	file("arrange");
#endif
	n = read<int>();k = read<int>();
	REP(i, 1, n) a[i] = read<int>();
	REP(i, 2, n)
	{
		int x(read<int>()), y(read<int>());
		add(x, y);add(y, x);
	}
	dfs0(1);
	int l = 1, r = 0, good = 1;
	REP(i, 1, n) chkmax(r, a[i]);
	while (l <= r)
	{
		int mid = l + r >> 1;
		if (judge(mid)) {good = mid;l = mid + 1;}
		else r = mid - 1;
	}
	cout << good << endl;
	return 0;
}
