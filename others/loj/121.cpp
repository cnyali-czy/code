/*
 * File Name:	121.cpp
 * Author	:	CraZYali
 * Year		:	2019.10.08 17:44
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <iostream>
#include <cstdio>
#include <stack>
#include <vector>

using namespace std;
const int maxn = 5000 + 10, maxm = 5e5 + 10;

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

int n, m;

int fa[maxn], siz[maxn];
inline void init() {REP(i, 1, n) siz[fa[i] = i] = 1;}
int find(const int &x) {return fa[x] == x ? fa[x] : find(fa[x]);}

stack <int> S;

inline void uni(int x, int y)
{
	x = find(x);y = find(y);
	if (siz[x] > siz[y]) swap(x, y);
	S.push(x);
	if (x == y) return;
	fa[x] = y;
	siz[y] += siz[x];
}
inline void undo()
{
	register int x = S.top();S.pop();
	if (x == fa[x]) return;
	siz[fa[x]] -= siz[x];
	fa[x] = x;
}

int type[maxm], x[maxm], y[maxm];
int id[maxn][maxn], cur, st[maxm], ed[maxm], Id[maxm];

#define ls p << 1
#define rs p << 1 | 1
#define mid (l + r >> 1)
#define lson ls, l, mid
#define rson rs, mid + 1, r
vector <int> vec[maxm << 2];

void insert(int p, int l, int r, int L, int R, int id)
{
	if (L <= l && r <= R) vec[p].emplace_back(id);
	else
	{
		if (L <= mid) insert(lson, L, R, id);
		if (R >  mid) insert(rson, L, R, id);
	}
}
vector <bool> ans;

void dfs(int p, int l, int r)
{
	int times = vec[p].size();
	for (int i : vec[p]) uni(x[i], y[i]);
	if (l < r)
	{
		dfs(lson);
		dfs(rson);
	}
	else if (type[l] == 2) ans.emplace_back(find(x[l]) == find(y[l]));
	while (times--) undo();
}
vector <pair <int, pair <int, int> > > qaq;
int back[maxm];

int main()
{
#ifdef CraZYali
	file("121");
#endif
	cin >> n >> m;
	init();
	REP(i, 1, m)
	{
		type[i] = read<int>();
		x[i] = read<int>();
		y[i] = read<int>();
		if (x[i] > y[i]) swap(x[i], y[i]);
		if (type[i] ^ 2)
		{
			if (!id[x[i]][y[i]]) id[x[i]][y[i]] = ++cur;
			Id[i] = id[x[i]][y[i]];
			back[Id[i]] = i;
		}
	}
	REP(i, 1, cur) ed[i] = m;
	REP(i, 1, m)
		if (type[i] == 0) st[Id[i]] = i;
		else if (type[i] == 1)
		{
			ed[Id[i]] = i;
			qaq.emplace_back(make_pair(i, make_pair(st[Id[i]], ed[Id[i]])));
			st[Id[i]] = 0;
		}
	REP(i, 1, cur)
		if (st[i]) insert(1, 1, m, st[i], m, back[i]);

	for (auto i : qaq)
		insert(1, 1, m, i.second.first, i.second.second, i.first);
	dfs(1, 1, m);
	for (bool i : ans) printf("%c\n", i ? 'Y' : 'N');
	return 0;
}
