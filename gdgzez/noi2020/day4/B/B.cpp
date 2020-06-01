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
#include <stack>
#include <vector>
#include <cmath>

using namespace std;
const int maxn = 1e6 + 10, maxN = 2.2e7;

int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

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

int m, n, k, ans = 1;
int siz[maxn];

stack <int> store;
int rt[maxn], ls[maxN], rs[maxN], s[maxN], cur;
inline int newnode()
{
	int p;
	if (store.empty()) p = ++cur;
	else p = store.top(), store.pop();
	ls[p] = rs[p] = s[p] = 0;
	return p;
}
void merge(int &x, int y)
{
	if (!x || !y) return void(x += y);
	s[x] += s[y];
	merge(ls[x], ls[y]);
	merge(rs[x], rs[y]);
	store.emplace(y);
}
#define lson ls[p], l, mid
#define rson rs[p], mid + 1, r
#define mid (l + r >> 1)
int Rt;
void insert(int &p, int l, int r, int pos, int val = 1)
{
	if (!p) p = newnode();
	s[p] += val;
	if (l == r) return;
	if (pos <= mid)	insert(lson, pos, val);
	else			insert(rson, pos, val);
}
int query(int p, int l, int r, int pos)
{
	if (!s[p]) return 0;
	if (l == r) return s[p];
	if (pos <= mid)	return query(lson, pos);
	else			return query(rson, pos);
}
void pre(int x, int fa = 0)
{
	siz[x] = 1;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
	{
		pre(to[i], x);
		siz[x] += siz[to[i]];
	}
}
int q1[maxn];
void dfs(int x, int fa = 0)
{
	insert(rt[x], 0, n, siz[x]);
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
	{
		dfs(to[i], x);
		merge(rt[x], rt[to[i]]);
	}
	q1[x] = (siz[x] + siz[x] < n ? query(rt[x], 0, n, n - siz[x] - siz[x]) : 0);
	int siza = n - siz[x];
	if (siza + siza >= n) return;
	if (!siza) return;
	if (siza + siza < n && siza > ans)
		if (query(rt[x], 0, n, siza)) ans = siza;
		else if (query(rt[x], 0, n, n - siza - siza)) ans = siza;
}
int cnt[maxn];
void output(int p, int l, int r)
{
	if (!p) return;
	if (l == r)
	{
		cnt[l] += s[p];
//		REP(i, 1, s[p]) printf("%d ", l);
		return;
	}
	output(lson);output(rson);
}
void dfs2(int x, int fa = 0)
{
	if (fa)
	{
		cnt[siz[fa]]--;
		cnt[n - siz[x]]++;
	}
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
		dfs2(to[i], x);
	if (fa)
	{
		int siza = siz[x];
//		printf("%d %d %d %d\n", x, siza, query(Rt, 0, n, siza) - 1, query(Rt, 0, n, n - siza - siza) - q1[x]);
		if (siza + siza < n && siza > ans)
		{
			if (cnt[siza] - 1) ans = siza;
			else if (cnt[n - siza - siza] - q1[x]) ans = siza;
		}
		cnt[siz[fa]]++;
		cnt[n - siz[x]]--;
	}
}

int main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read<int>();
	if (n <= 2)
	{
		puts("0");
		return 0;
	}
	if (n == 3)
	{
		cout << 1 << endl;
		return 0;
	}
	REP(i, 2, n)
	{
		int x(read<int>()), y(read<int>());
		add(x, y);add(y, x);
	}
	pre(1);
	dfs(1);
	Rt = rt[1];
	output(Rt, 0, n);
//	output(Rt, 0, n);puts("");
	dfs2(1);
	cout << ans << endl;
	return 0;
}
