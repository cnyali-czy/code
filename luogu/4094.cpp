#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 2e5 + 10;

int n, q, pre[maxn];
char str[maxn];

namespace SMT
{
	const int maxN = 8e6;
	int ls[maxN], rs[maxN], s[maxN], cur;
#define lson ls[p], l, mid
#define rson rs[p], mid + 1, r
#define mid (l + r >> 1)
	void ins(int &p, int l, int r, int pos)
	{
		s[p = ++cur] = 1;
		if (l == r) return;
		if (pos <= mid) ins(lson, pos);
		else ins(rson, pos);
	}
	int merge(int x, int y)
	{
		int p = ++cur;
		if (!x || !y)
		{
			ls[p] = ls[x | y];
			rs[p] = rs[x | y];
		}
		else
		{
			ls[p] = merge(ls[x], ls[y]);
			rs[p] = merge(rs[x], rs[y]);
		}
		s[p] = s[x] + s[y];
		return p;
	}
	int query(int p, int l, int r, int L, int R)
	{
		if (!p) return 0;
		if (L <= l && r <= R) return s[p];
		else
		{
			if (R <= mid) return query(lson, L, R);
			if (L >  mid) return query(rson, L, R);
			return query(lson, L, R) + query(rson, L, R);
		}
	}
#undef mid
}
int ch[maxn][26], len[maxn], fail[maxn], lst = 1, cur = 1, rt[maxn];
void extend(int c, int i)
{
	int u = ++cur, v = lst;
	lst = u;
	len[u] = len[v] + 1;
	SMT :: ins(rt[u], 1, n, i);
	for (; v && !ch[v][c]; v = fail[v]) ch[v][c] = u;
	if (!v) fail[u] = 1;
	else if (len[ch[v][c]] == len[v] + 1) fail[u] = ch[v][c];
	else
	{
		int New(++cur), Old(ch[v][c]);
		copy(ch[Old], ch[Old] + 26, ch[New]);
		len[New] = len[v] + 1;
		fail[New] = fail[Old];
		fail[Old] = fail[u] = New;
		for (; v && ch[v][c] == Old; v = fail[v]) ch[v][c] = New;
	}
}
#define anc ch
void buildanc()
{
	REP(i, 1, cur) anc[i][0] = fail[i];
	REP(j, 1, 17) REP(i, 1, cur) anc[i][j] = anc[anc[i][j - 1]][j - 1];
}
int get(int l, int r)
{
	int p = pre[r];
	DEP(i, 17, 0) if (len[anc[p][i]] >= r - l + 1) p = anc[p][i];
	return p;
}
int bg[maxn], ne[maxn], to[maxn], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}
void dfs(int x)
{
	for (int i = bg[x]; i; i = ne[i])
	{
		dfs(to[i]);
		rt[x] = SMT :: merge(rt[x], rt[to[i]]);
	}
}
void buildSMT()
{
	REP(i, 2, cur) add(fail[i], i);
	dfs(1);
}

int main()
{
#ifdef CraZYali
	freopen("4094.in", "r", stdin);
	freopen("4094.out", "w", stdout);
#endif
	scanf("%d %d\n%s", &n, &q, str + 1);
	REP(i, 1, n) extend(str[i] - 'a', i);
	pre[0] = 1;
	REP(i, 1, n) pre[i] = ch[pre[i - 1]][str[i] - 'a'];
	buildanc();buildSMT();
	while (q--)
	{
		int a, b, c, d;
		scanf("%d%d%d%d", &a, &b, &c, &d);
		int ans = 0, l = 1, r = min(b - a + 1, d - c + 1);
		while (l <= r)
		{
			int mid = l + r >> 1, p = get(c, c + mid - 1);
			if (SMT :: query(rt[p], 1, n, a + mid - 1, b))
			{
				ans = mid;
				l = mid + 1;
			}
			else r = mid - 1;
		}
		printf("%d\n", ans);
	}
	cerr << SMT :: cur << endl;
	return 0;
}
