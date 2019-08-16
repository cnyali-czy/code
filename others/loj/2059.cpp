#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;
const int maxn = 200000 + 10, maxN = maxn << 1;

int ls[maxn*50], rs[maxn*50], cur;
#define mid (l + r >> 1)
#define lson ls[p], l, mid
#define rson rs[p], mid + 1, r

void build(int &p, int l, int r, int pos)
{
	p = ++cur;
	if (l == r) return;
	else
		if (pos <= mid) build(lson, pos);
		else			build(rson, pos);
}

int merge(int a, int b)
{
	if (!a || !b) return a + b;
	int now = ++cur;
	ls[now] = merge(ls[a], ls[b]);
	rs[now] = merge(rs[a], rs[b]);
	return now;
}

bool query(int p, int l, int r, int L, int R)
{
	if (!p) return 0;
	if (L == l && r == R) return 1;
	else
	{
		if (R <= mid) return query(lson, L, R);
		if (L >  mid) return query(rson, L, R);
		return query(lson, L, mid) || query(rson, mid+1, R);
	}
}

int n, m;
char str[maxN];
int ch[maxN][26], ne[maxN][21], Max[maxN], sam_cur = 1, start = 1, last = 1;
int rt[maxN], fin[maxN];

inline int newnode(int _Max) {return Max[++sam_cur] = _Max, sam_cur;}
inline void extend(int c, int id)
{
	int v = last, u = newnode(Max[v] + 1);
	build(rt[u], 1, n, id);
	for (; v && !ch[v][c]; v = ne[v][0]) ch[v][c] = u;
	if (!v) ne[u][0] = start;
	else if (Max[v] + 1 == Max[ch[v][c]]) ne[u][0] = ch[v][c];
	else
	{
		int New = newnode(Max[v] + 1), Old = ch[v][c];
		copy(ch[Old], ch[Old] + 26, ch[New]);
		ne[New][0] = ne[Old][0];
		ne[u][0] = ne[Old][0] = New;
		for (; v && ch[v][c] == Old;v = ne[v][0]) ch[v][c] = New;
	}
	fin[id] = last = u;
}

int bg[maxN], nex[maxN], to[maxN], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	nex[e] = bg[x];
	bg[x] = e;
}
void dfs(int x)
{
	for (int i = bg[x]; i ; i = nex[i])
	{
		dfs(to[i]);
		rt[x] = merge(rt[x], rt[to[i]]);
	}
}

inline bool judge(int pos, int Mid, int a, int b)
{
	DREP(i, 19, 0)
		if (Max[ne[pos][i]] >= Mid) pos = ne[pos][i];
	return query(rt[pos], 1, n, a+Mid-1, b);
}

int main()
{
#ifdef CraZYali
	freopen("2059.in", "r", stdin);
	freopen("2059.out", "w", stdout);
#endif
	scanf("%d%d\n%s", &n, &m, str + 1);
	reverse(str+1, str+n+1);
	REP(i, 1, n) extend(str[i]-'a', i);
	REP(j, 1, 19)
		REP(i, 1, sam_cur)
			ne[i][j] = ne[ne[i][j-1]][j-1];
	REP(i, 2, sam_cur) add(ne[i][0], i);
	dfs(start);
	while (m--)
	{
		int a, b, c, d;
		scanf("%d%d%d%d", &b, &a, &d, &c);
		a = n-a+1, b = n-b+1, c = n-c+1, d = n-d+1;
		int pos = fin[d];
		int l(1), r(min(b-a+1, d-c+1));
		while (l <= r)
			if (judge(pos, mid, a, b)) l = mid + 1;
			else r = mid - 1;
		printf("%d\n", l-1);
	}
	return 0;
}
