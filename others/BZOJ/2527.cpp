/*
 * File Name:	2527.cpp
 * Author	:	CraZYali
 * Year		:	2019.09.15 09:08
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 3e5 + 10;

int bg[maxn], ne[maxn], to[maxn], e;
inline void add_edge(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

template <typename T> inline T read()
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

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout);

int n, m, k;
int o[maxn];

pair <int, int> a[maxn], b1[maxn], b2[maxn];
int lft[maxn], rit[maxn], val[maxn];

long long s[maxn];
int vis[maxn], dfn;
inline void add(int x, int val)
{
	while (x <= m)
	{
		if (vis[x] ^ dfn) s[x] = 0, vis[x] = dfn;
		s[x] += val;
		x += x & -x;
	}
}
long long sum(int x)
{
	long long res(0);
	while (x > 0)
	{
		res += (vis[x] == dfn) * s[x];
		x -= x & -x;
	}
	return res;
}

inline void add(int l, int r, int val)
{
	add(l, val);
	add(r + 1, -val);
}
long long cnt[maxn];
int ans[maxn];

int lst;

void solve(int l, int r, int L, int R)
{
	if (l > r || L > R) return;
	if (L == R)
	{
		REP(i, l, r) ans[a[i].first] = L;
		return;
	}
	int mid(L + R >> 1);
	++dfn;
	REP(i, L, mid)
		if (lft[i] <= rit[i]) add(lft[i], rit[i], val[i]);
		else add(lft[i], m, val[i]), add(1, rit[i], val[i]);
	int hh1(l-1), hh2(l-1);
	REP(i, l, r)
	{
		long long res(0);
		for (int I = bg[a[i].first], j = to[I]; res < a[i].second && I; I = ne[I]) res += sum(to[I]);
		if (a[i].second <= res) b1[++hh1] = a[i];
		else a[i].second -= res, b2[++hh2] = a[i];
	}
	int p(l-1);
	REP(i, l, hh1) a[++p] = b1[i];
	REP(i, l, hh2) a[++p] = b2[i];
	solve(l, hh1, L, mid);
	solve(hh1 + 1, r, mid + 1, R);
}

int main()
{
#ifdef CraZYali
	file("2527");
#endif
	cin >> n >> m;
	REP(i, 1, m) add_edge(read<int>(), i);
	REP(i, 1, n) a[i] = make_pair(i, read<int>());
	cin >> k;
	REP(i, 1, k)
	{
		lft[i] = read<int>();
		rit[i] = read<int>();
		val[i] = read<int>();
	}
	solve(1, n, 1, k + 1);
	REP(i, 1, n)
		if (ans[i] == k + 1) puts("NIE");
		else printf("%d\n", ans[i]);
	return 0;
}
