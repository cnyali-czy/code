/*
 * File Name:	H.cpp
 * Author	:	CraZYali
 * Time		:	2020.02.04 20:54
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <cassert>
#include <vector>
#include <cstring>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 4e5 + 10, maxN = 3e7;

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

namespace SMT
{
	int rt[maxn], ls[maxN], rs[maxN], s[maxN], cur;
#define lson ls[p], l, mid
#define rson rs[p], mid + 1, r
#define mid (l + r >> 1)
	void insert(int &p, int l, int r, int pos)
	{
		p = ++cur;
		s[p]++;
		if (l == r) return;
		if (pos <= mid) insert(lson, pos);
		else			insert(rson, pos);
	}
	int merge(int x, int y)
	{
		if (!x || !y) return x + y;
		int p = ++cur;
		s[p] = s[x] + s[y];
		ls[p] = merge(ls[x], ls[y]);
		rs[p] = merge(rs[x], rs[y]);
		return p;
	}
	int query(int p, int l, int r, int L, int R)
	{
		if (L > R) return 0;
		if (!s[p]) return 0;
		if (L <= l && r <= R) return s[p];
		else
		{
			if (R <= mid) return query(lson, L, R);
			if (L >  mid) return query(rson, L, R);
			return query(lson, L, R) + query(rson, L, R);
		}
	}
}

int n, q;
char s[maxn];

const int sig = 26;
int ch[maxn][sig], fail[maxn], len[maxn], lst = 1, cur = 1;
vector <int> G[maxn];
inline void extend(int c)
{
	int v(lst), u = ++cur;
	len[u] = len[v] + 1;
	SMT::insert(SMT::rt[u], 1, n, len[u]);
	for (; v && !ch[v][c]; v = fail[v]) ch[v][c] = u;
	if (!v) fail[u] = 1;
	else if (len[v] + 1 == len[ch[v][c]]) fail[u] = ch[v][c];
	else
	{
		int Old(ch[v][c]), New(++cur);
		len[New] = len[v] + 1;
		REP(i, 0, sig - 1) ch[New][i] = ch[Old][i];
		fail[New] = fail[Old];
		SMT::rt[New] = SMT::rt[fail[New]];
		fail[u] = fail[Old] = New;
		for (; v && ch[v][c] == Old;v = fail[v]) ch[v][c] = New;
	}
	lst = u;
}
void dfs(int u)
{
	for (auto v : G[u])
	{
		dfs(v);
		SMT::rt[u] = SMT::merge(SMT::rt[u], SMT::rt[v]);
	}
}
vector <int> suf;
int main()
{
#ifdef CraZYali
	file("H");
#endif
	scanf("%s", s + 1);
	n = strlen(s + 1);
	REP(i, 1, n) extend(s[i] - 'a');
	REP(i, 2, cur) G[fail[i]].emplace_back(i);
	dfs(1);
	q = read<int>();
	while (q--)
	{
		int l, r;
		scanf("%d %d %s", &l, &r, s + 1);
		int N = strlen(s + 1);
		s[++N] = 'a' - 1;
		int p = 1;
		suf.clear();
		suf.emplace_back(-1);
		REP(i, 1, N)
		{
			suf.emplace_back(-1);
			s[i] -= 'a';
			REP(j, s[i] + 1, 25) if (ch[p][j] && SMT::query(SMT::rt[ch[p][j]], 1, n, l + i - 1, r))
			{
				suf[i] = j;
				break;
			}
			if (i == N) break;
			p = ch[p][s[i]];
			if (!p || !SMT::query(SMT::rt[p], 1, n, l + i - 1, r)) break;
		}
		while (!suf.empty() && suf.back() == -1) suf.pop_back();
		if (suf.empty()) puts("-1");
		else
		{
			REP(i, 1, (int)suf.size() - 2) putchar(s[i] + 'a');
			putchar(suf.back() + 'a');putchar(10);
		}
	}
	return 0;
}
