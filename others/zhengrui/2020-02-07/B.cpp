/*
 * File Name:	B.cpp
 * Author	:	CraZYali
 * Time		:	2020.02.07 10:14
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <algorithm>
#include <vector>
#include <cstring>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 5e5 + 10, base = 1e9 + 7, MOD = 1e9 + 9;

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

int n, q, p[4], more[4], pos[maxn][4];
char s[maxn];

const int maxN = 5e5 + 10;
vector <int> id[maxN];
struct Trie_
{
	int rt, ch[maxN][26], cur, dfn[maxN], siz[maxN], fa[maxN], dfs_clock, back[maxN];
	bool End[maxN];
	vector <int> G[maxN];
	Trie_()
	{
		dfs_clock = 0;
		G[cur = rt = 1].clear();;
		memset(ch, 0, sizeof ch);
		memset(fa, 0, sizeof fa);
	}
	int insert(int i, bool flag)
	{
		int u = rt;
		REP(j, 1, strlen(s + 1))
		{
			if (flag) id[u].emplace_back(i);
			int c = s[j] - 'a';
			if (!ch[u][c])
			{
				G[u].emplace_back(ch[u][c] = ++cur);
				G[ch[u][c]].clear();
				fa[ch[u][c]] = u;
			}
			u = ch[u][c];
		}
		End[u] = 1;
		if (flag) id[u].emplace_back(i);
		return u;
	}
	void dfs(int u)
	{
		siz[u]++;
		back[dfn[u] = ++dfs_clock] = u;
		for (int v : G[u]) dfs(v), siz[u] += siz[v];
	}
	void get_dfn()
	{
		dfs(1);
	}
}Trie[4];

int ans[maxn];
struct Query
{
	int id, l2, r2, l3, r3;
	Query(int id = 0, int l2 = 0, int r2 = 0, int l3 = 0, int r3 = 0) : id(id), l2(l2), r2(r2), l3(l3), r3(r3) {}
};
vector <Query> Q[maxN];

const int maxnode = 2e7;
int rt[maxN], ls[maxnode], rs[maxnode], sum[maxnode], cur;
#define lson ls[p], l, mid
#define rson rs[p], mid + 1, r
#define mid (l + r >> 1)

void insert(int pre, int &p, int l, int r, int pos)
{
	p = ++cur;
	ls[p] = ls[pre];
	rs[p] = rs[pre];
	sum[p] = sum[pre] + 1;
	if (l == r) return;
	else if (pos <= mid)	insert(ls[pre], lson, pos);
	else					insert(rs[pre], rson, pos);
}
int query(int p, int l, int r, int L, int R)
{
	if (!sum[p]) return 0;
	if (L <= l && r <= R) return sum[p];
	else
	{
		if (R <= mid) return query(lson, L, R);
		if (L >  mid) return query(rson, L, R);
		return query(lson, L, R) + query(rson, L, R);
	}
}
void clear(int &p)
{
	if (!p) return;
	clear(ls[p]);
	clear(rs[p]);
	sum[p] = 0;
	p = 0;
}
int show[maxN], top;

int main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read<int>();
	REP(i, 1, n)
		REP(k, 1, 3)
		{
			scanf("%s", s + 1);
			pos[i][k] = Trie[k].insert(i, k == 1);
		}
	Trie[2].get_dfn();Trie[3].get_dfn();
	q = read<int>();
	REP(i, 1, 3) p[i] = 1;
	REP(i, 1, q)
	{
		char c = getchar();
		while (c ^ '+' && c ^ '-') c = getchar();
		int k = read<int>();
		if (c == '+')
		{
			while (!isalpha(c)) c = getchar();
			c -= 'a';
			if (more[k]) more[k]++;
			else if (Trie[k].ch[p[k]][c]) p[k] = Trie[k].ch[p[k]][c];
			else more[k]++;
		}
		else
			if (more[k]) more[k]--;
			else p[k] = Trie[k].fa[p[k]];
		int flag = 1;
		REP(k, 1, 3) if (more[k]) {flag = 0;break;}
		if (flag)
		{
			int l2 = Trie[2].dfn[p[2]], r2 = Trie[2].dfn[p[2]] + Trie[2].siz[p[2]] - 1;
			int l3 = Trie[3].dfn[p[3]], r3 = Trie[3].dfn[p[3]] + Trie[3].siz[p[3]] - 1;
			Q[p[1]].emplace_back(i, l2, r2, l3, r3);
		}
	}
	REP(i, 1, Trie[1].cur) if (Q[i].size())
	{
		sort(id[i].begin(), id[i].end(), [&](int x, int y) {return Trie[2].dfn[pos[x][2]] < Trie[2].dfn[pos[y][2]];});
		cur = 0;
		REP(j, 1, top) clear(rt[j]);
		top = 0;
		for (auto k : id[i]) show[++top] = Trie[2].dfn[pos[k][2]];
		top = unique(show + 1, show + 1 + top) - show - 1;
		int now = 0, SIZ = id[i].size();
		REP(j, 1, top)
		{
			bool first = 1;
#define k id[i][now]
			while (now < SIZ && Trie[2].dfn[pos[k][2]] == show[j])
			{
				if (first)
				{
					first = 0;
					insert(rt[j - 1], rt[j], 1, Trie[3].cur, Trie[3].dfn[pos[k][3]]);
				}
				else insert(rt[j], rt[j], 1, Trie[3].cur, Trie[3].dfn[pos[k][3]]);
				now++;
			}
#undef k
		}
		for (auto j : Q[i])
		{
			int l = j.l2, r = j.r2, L = j.l3, R = j.r3;
			l = lower_bound(show + 1, show + 1 + top, l) - show;
			r = upper_bound(show + 1, show + 1 + top, r) - show - 1;
			if (l > r) continue;
			ans[j.id] = query(rt[r], 1, Trie[3].cur, L, R) - query(rt[l-1], 1, Trie[3].cur, L, R);
		}
	}
	REP(i, 1, q) printf("%d\n", ans[i]);
	return 0;
}
