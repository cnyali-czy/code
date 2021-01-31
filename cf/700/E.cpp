/*
	Problem:	E.cpp
	Time:		2021-01-31 21:29
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <map>
#include <vector>
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
const int maxn = 4e5 + 10;

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
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n;
char str[maxn];

map <int, int> ch[maxn];
int len[maxn], fail[maxn], pos[maxn], cur = 1, lst = 1;
void extend(int c, int i)
{
	int u = ++cur, v = lst;lst = u;
	len[u] = len[v] + 1;
	pos[u] = i;
	for (; v && !ch[v][c]; v = fail[v]) ch[v][c] = u;
	if (!v) fail[u] = 1;
	else if (len[ch[v][c]] == len[v] + 1) fail[u] = ch[v][c];
	else
	{
		int New(++cur), Old(ch[v][c]);
		ch[New] = ch[Old];
		len[New] = len[v] + 1;
		fail[New] = fail[Old];
		pos[New] = pos[Old];
		fail[Old] = fail[u] = New;
		for (; v && ch[v][c] == Old; v = fail[v]) ch[v][c] = New;
	}
}
vector <int> G[maxn];
int rt[maxn];

namespace SMT
{
	const int maxN = 3e7;
	int ls[maxN], rs[maxN], s[maxN], cur;
#define lson ls[p], l, mid
#define rson rs[p], mid + 1, r
#define mid (l + r >> 1)
	void insert(int &p, int l, int r, int pos)
	{
		s[p = ++cur] = 1;
		if (l == r) return;
		if (pos <= mid) insert(lson, pos);
		else insert(rson, pos);
	}
	int merge(int x, int y)
	{
		int p = ++cur;
		if (!x || !y) ls[p] = ls[x | y], rs[p] = rs[x | y];
		else
		{
			ls[p] = merge(ls[x], ls[y]);
			rs[p] = merge(rs[x], rs[y]);
		}
		s[p] = s[x] + s[y];
		return p;
	}
	bool query(int p, int l, int r, int L, int R)
	{
		if (!s[p]) return 0;
		if (L <= l && r <= R) return 1;
		else
		{
			if (R <= mid) return query(lson, L, R);
			if (L >  mid) return query(rson, L, R);
			return query(lson, L, R) || query(rson, L, R);
		}
	}
}
void dfs(int x)
{
	for (int y : G[x])
	{
		dfs(y);
		rt[x] = SMT :: merge(rt[x], rt[y]);
	}
}
int f[maxn], g[maxn], ans = 1;

void dp(int x)
{
	if (x > 1)
		if (fail[x] == 1) {f[x] = 1;g[x] = x;}
		else
		{
			f[x] = f[fail[x]];
			if (len[x] - len[g[fail[x]]] && SMT :: query(rt[g[fail[x]]], 1, n, pos[x] - len[x] + len[g[fail[x]]], pos[x] - 1))
			{
				f[x]++;
				g[x] = x;
			}
			else g[x] = g[fail[x]];
		}
	ans = max(ans, f[x]);
	for (int y : G[x]) dp(y);
}

int main()
{
#ifdef CraZYali
	file("E");
#endif
	scanf("%d\n%s", &n, str + 1);
	REP(i, 1, n) extend(str[i] - 'a', i);
	REP(i, 2, cur)
	{
		G[fail[i]].emplace_back(i);
		SMT :: insert(rt[i], 1, n, pos[i]);
	}
//	DEP(i, cur, 2) rt[fail[i]] = SMT :: merge(rt[fail[i]], rt[i]);
	dfs(1);
	f[1] = g[1] = 1;
	dp(1);
	//	REP(i, 1, cur) printf("%d%c", fail[i], i == end_i ? '\n' : ' ');
	//	REP(i, 1, cur) printf("%d%c", pos[i], i == end_i ? '\n' : ' ');
	//	REP(i, 1, cur) printf("%d%c", f[i], i == end_i ? '\n' : ' ');
	cout << ans << endl;
	return 0;
}
