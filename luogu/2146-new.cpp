/*
 * File Name:	2146-new.cpp
 * Author	:	CraZYali
 * Year		:	2019.11.07 20:54
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <iostream>
#include <cstdio>
#include <set>

using namespace std;
const int maxn = 1e5 + 10;

int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
inline void add(int x, int y)
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

int n;

int fa[maxn], siz[maxn], dfn[maxn], dfs_clock, top[maxn], hvy[maxn], dep[maxn];

void dfs1(int x)
{
	hvy[x] = -1;
	siz[x] = 1;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa[x])
	{
		dep[to[i]] = dep[x] + 1;
		dfs1(to[i]);
		siz[x] += siz[to[i]];
		if (hvy[x] == -1 || siz[to[i]] > siz[hvy[x]]) hvy[x] = to[i];
	}
}
void dfs2(int x, int y)
{
	top[x] = y;
	dfn[x] = ++dfn[n];
	if (hvy[x] > 0)
	{
		dfs2(hvy[x], y);
		for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa[x] && to[i] ^ hvy[x])
			dfs2(to[i], to[i]);
	}
}

struct node
{
	int l, r;
	bool v;
	inline node(int l = 0, int r = 0, bool v = 0) : l(l), r(r), v(v) {};
	inline bool operator < (const node &B) const {return l < B.l;}
};
set <node> S;

using IT = set <node> :: iterator;
IT split(int pos)
{
	IT it = S.lower_bound(pos);
	if (it != S.end() && it -> l == pos) return it;
	--it;
	int l(it -> l), r(it -> r);
	bool v(it -> v);
	S.erase(it);
	if (l < pos) S.emplace(l, pos - 1, v);
	return pos <= r ? S.emplace(pos, r, v).first : S.end();
}
int sum(int l, int r, bool v)
{
	IT itr = split(r + 1), itl = split(l);
	int res(0);
	while (itl != itr)
	{
		res += (itl -> r - itl -> l + 1) * (itl -> v == v);
		itl++;
	}
	return res;
}
void assign(int l, int r, bool v)
{
	IT itr = split(r + 1), itl = split(l);
	S.erase(itl, itr);
	S.emplace(l, r, v);
}

int main()
{
#ifdef CraZYali
	file("2146-new");
#endif
	cin >> n;
	REP(i, 1, n - 1) add(fa[i] = read<int>(), i);
	dfs1(0);
	dfs2(0, 0);
	S.emplace(1, n, 0);
	REP(Case, 1, read<int>())
	{
		char s[20];scanf("%s", s);
		int x(read<int>());
		if (s[0] == 'u')
		{
			printf("%d\n", sum(dfn[x], dfn[x] + siz[x] - 1, 1));
			assign(dfn[x], dfn[x] + siz[x] - 1, 0);
		}
		else
		{
			int res(0);
			while (top[x])
			{
				res += sum(dfn[top[x]], dfn[x], 0);
				assign(dfn[top[x]], dfn[x], 1);
				x = fa[top[x]];
			}
			printf("%d\n", res + sum(1, dfn[x], 0));
			assign(1, dfn[x], 1);
		}
	}
	return 0;
}
