#define  REP(i, s, e) for (register int i = s; i <= e; i++)
#define DREP(i, s, e) for (register int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 1e5 + 10, maxm = maxn;

int bg[maxn], ne[maxm << 1], to[maxm << 1], e = 1;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

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
int n, m, depth[maxn], fa[maxn], top[maxn], dfn[maxn], dfs_clock, siz[maxn], hson[maxn];

void dfs1(int x)
{
	siz[x] = 1;
	for (register int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ fa[x])
		{
			depth[to[i]] = depth[x] + 1;
			dfs1(to[i]);
			siz[x] += siz[to[i]];
			if (siz[to[i]] >= siz[hson[x]]) hson[x] = to[i];
		}
}
void dfs2(int x, int y)
{
	dfn[x] = ++dfs_clock;
	top[x] = y;
	if (hson[x])
	{
		dfs2(hson[x], y);
		for (register int i = bg[x]; i ;i = ne[i])
			if (to[i] ^ fa[x] && to[i] ^ hson[x]) dfs2(to[i], to[i]);
	}
}

#define ls p << 1
#define rs p << 1 | 1
#define mid (l + r >> 1)
#define lson ls, l, mid
#define rson rs, mid + 1, r

int sum[maxn << 2], tag[maxn << 2];

void pushdown(int p, int l, int r)
{
	if (tag[p])
	{
		tag[p] = 0;
		tag[ls] = tag[rs] = 1;
		if (!sum[p]) sum[ls] = sum[rs] = 0;
		else sum[ls] = (mid - l + 1), sum[rs] = (r - (mid + 1) + 1);
	}
}
void update(int p, int l, int r, int L, int R, bool type)
{
	if (L <= l && r <= R) sum[p] = type * (r - l + 1), tag[p] = 1;
	else
	{
		pushdown(p, l, r);
		if (L <= mid) update(lson, L, R, type);
		if (R >  mid) update(rson, L, R, type);
		sum[p] = sum[ls] + sum[rs];
	}
}
int query(int p, int l, int r, int L, int R)
{
	if (L <= l && r <= R) return sum[p];
	else
	{
		pushdown(p, l, r);
		if (L >  mid) return query(rson, L, R);
		if (R <= mid) return query(lson, L, R);
		return query(lson, L, R) + query(rson, L, R);
	}
}

void install(int x)
{
	while (x)
	{
		update(1, 1, n, dfn[top[x]], dfn[x], 1);
		x = fa[top[x]];
	}
}

void uninstall(int x){update(1, 1, n, dfn[x], dfn[x] + siz[x] - 1, 0);}

int main()
{
#ifdef CraZYali
	freopen("2146.in", "r", stdin);
	freopen("2146.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 2, n)
	{
		fa[i] = read<int>() + 1;
		add(fa[i], i);add(i, fa[i]);
	}
	depth[1] = 1;
	dfs1(1);dfs2(1, 1);
	cin >> m;
	while (m --> 0)
	{
		char s[20];scanf("%s", s + 1);
		int now = query(1, 1, n, 1, n);
		if (s[1] == 'i') install(read<int>() + 1);
		else uninstall(read<int>() + 1);
		printf("%d\n", abs(query(1, 1, n, 1, n) - now));
	}

	return 0;
}
