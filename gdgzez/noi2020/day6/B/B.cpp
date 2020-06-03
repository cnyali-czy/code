/*
	Problem:	B.cpp
	Time:		2020-06-03 23:08
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
const int maxn = 4e5 + 10, MOD = 1e9 + 7;

inline int add(int x, int y) {return (x += y) >= MOD ? x - MOD : x;}
inline int sub(int x, int y) {return (x -= y) <    0 ? x + MOD : x;}
inline void inc(int &x, int y) {x += y;if (x >= MOD) x -= MOD;}
inline void dec(int &x, int y) {x -= y;if (x <    0) x += MOD;}

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
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n;
char s[maxn];
namespace SAM
{
	int ch[maxn][26], fail[maxn], len[maxn], last = 1, cur = 1, pos[maxn];
	void extend(int c, int id)
	{
		int p = last, np = ++cur;
		pos[id] = np;
		len[np] = len[p] + 1;
		for (; p && !ch[p][c]; p = fail[p]) ch[p][c] = np;
		if (!p) fail[np] = 1;
		else
		{
			int q = ch[p][c];
			if (len[q] == len[p] + 1) fail[np] = q;
			else
			{
				int nq = ++cur;
				fail[nq] = fail[q];
				copy(ch[q], ch[q] + 26, ch[nq]);
				len[nq] = len[p] + 1;
				fail[np] = fail[q] = nq;
				for (; p && ch[p][c] == q; p = fail[p]) ch[p][c] = nq;
			}
		}
		last = np;
	}
	void Debug()
	{
		REP(i, 1, cur)
		{
			printf("node:%d  len:%d  par:%d\n", i, len[i], fail[i]);
			REP(j, 0, 25)
				if (ch[i][j])
					printf("%c:%d\n", char('a' + j), ch[i][j]);
		}
	}
}

namespace lct
{
	int fa[maxn], ch[maxn][2], v[maxn], sv[maxn], xs[maxn], sum[maxn], lazy[maxn];
#define ls(p) ch[p][0]
#define rs(p) ch[p][1]
#define get(p) (rs(fa[p]) == p)
#define notroot(p) (ls(fa[p]) == p || rs(fa[p]) == p)
	void pushup(int x)
	{
		sv[x] = v[x];
		sum[x] = 1ll * xs[x] * v[x] % MOD;
		if (ls(x)) inc(sv[x], sv[ls(x)]), inc(sum[x], sum[ls(x)]);
		if (rs(x)) inc(sv[x], sv[rs(x)]), inc(sum[x], sum[rs(x)]);
	}
	void rotate(int x)
	{
		int y(fa[x]), z(fa[y]), k(get(x));
		ch[y][k] = ch[x][!k];
		if (ch[x][!k]) fa[ch[x][!k]] = y;
		fa[x] = z;
		if (notroot(y)) ch[z][get(y)] = x;
		ch[x][!k] = y;
		fa[y] = x;
		pushup(y);pushup(x);
	}
	void maintain(int x, int k)
	{
		inc(xs[x], k);
		inc(sum[x], 1ll * k * sv[x]);
		inc(lazy[x], k);
	}
	void pushdown(int x)
	{
		if (lazy[x])
		{
			if (ls(x)) maintain(ls(x), lazy[x]);
			if (rs(x)) maintain(rs(x), lazy[x]);
			lazy[x] = 0;
		}
	}
	void pushall(int x)
	{
		if (notroot(x)) pushall(fa[x]);
		pushdown(x);
	}
	void splay(int x)
	{
		pushall(x);
		while (notroot(x))
		{
			int y(fa[x]);
			if (notroot(y)) rotate(get(x) == get(y) ? y : x);
			rotate(x);
		}
	}
	void access(int x)
	{
		for (int y = 0; x; x = fa[y = x])
		{
			splay(x);
			rs(x) = y;
			pushup(x);
		}
	}
	void makeroot(int x)
	{
		access(x);
		splay(x);
		pushdown(x);
	}
	int find(int x)
	{
		access(x);
		splay(x);
		while (ls(x)) pushdown(x = ls(x));
		return x;
	}
	void cut(int x, int y)
	{
		makeroot(x);
		if (find(x) != find(y)) return;
		splay(y);
		if (ls(y) == x && !rs(x))
			ls(y) = fa[x] = 0;
	}
	void link(int x, int y)	
	{
		makeroot(x);
		if (find(x) == find(y)) return;
		fa[x] = y;
	}
}
int ans[maxn];

int main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read<int>();
	scanf("%s", s + 1);
	REP(i, 1, n) SAM :: extend(s[i] - 'a', i);
//	SAM :: Debug();
	REP(i, 1, SAM :: cur)
	{
		if (SAM :: fail[i]) lct :: fa[i] = SAM :: fail[i];
		lct :: v[i] =  SAM :: len[i] - SAM :: len[SAM :: fail[i]];
		lct :: pushup(i);
	}
	int now = 0;
	REP(i, 1, n)
	{
		int u = SAM :: pos[i];
//		printf("%d\n", u);
		lct :: access(u);
		lct :: splay(u);
		inc(now, lct :: sum[u]);
		lct :: maintain(u, 1);
		ans[i] = add(ans[i - 1], now);
	}
	REP(i, 1, n) printf("%d\n", ans[i]);
	return 0;
}
