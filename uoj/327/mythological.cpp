#include "mythological.h"
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <map>

using namespace std;
const int maxn = 1e5 + 10;

int n, m, a[maxn], t;

int rt[maxn], cur = 1;
map <int, int> ch[maxn];

int stk[maxn], top;

int bg[maxn], ne[maxn], to[maxn], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

int siz[maxn], hvy[maxn], dep[maxn], fa[maxn], tp[maxn];
void dfs1(int x)
{
	siz[x] = 1;
	for (int i = bg[x]; i; i = ne[i])
	{
		dep[to[i]] = dep[x] + 1;
		dfs1(to[i]);
		siz[x] += siz[to[i]];
		if (siz[to[i]] > siz[hvy[x]]) hvy[x] = to[i];
	}
}
void dfs2(int x, int y)
{
	tp[x] = y;
	if (!hvy[x]) return;
	dfs2(hvy[x], y);
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ hvy[x])
		dfs2(to[i], to[i]);
}
int lca(int x, int y)
{
	while (tp[x] ^ tp[y])
	{
		if (dep[tp[x]] < dep[tp[y]]) swap(x, y);
		x = fa[tp[x]];
	}
	return dep[x] < dep[y] ? x : y;
}
int dis(int x, int y) {return dep[x] + dep[y] - 2 * dep[lca(x, y)];}
void init(int n, int m, int a[], int t)
{
	::n = n;
	::m = m;
	copy(a + 1, a + 1 + n, ::a + 1);
	::t = t;
	int p = 1;
	rt[0] = 1;
	REP(i, 1, n)
	{
		if (top && a[stk[top]] == a[i])
		{
			top--;
			p = fa[p];
			rt[i] = p;
		}
		else
		{
			int c = a[i];
			if (ch[p].find(c) == ch[p].end())
			{
				ch[p][c] = ++cur;
				fa[cur] = p;
				add(p, cur);
			}
			rt[i] = p = ch[p][c];
			stk[++top] = i;
		}
	}
	dfs1(1);dfs2(1, 1);
}

int query(int l, int r)
{
	return r - l + 1 - dis(rt[l - 1], rt[r]);
}
#ifdef CraZYali
#include "mythological.h"
#include <bits/stdc++.h>
namespace Grader
{
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
	using namespace std;
	const int maxn=100005;
	static int c___a[maxn];
	static int c___ans[2000005];
	const int BUF_SIZE = (int)1e5 + 10;
	struct fastIO{
		char buf[BUF_SIZE];
		int cur;
		FILE *in, *out;
		fastIO()
		{
			cur = BUF_SIZE;
			in = stdin;
			out = stdout;
		}
		inline char nextChar()
		{
			if(cur == BUF_SIZE)
			{
				fread(buf, BUF_SIZE, 1, in);
				cur = 0;
			}
			return buf[cur++];
		}
		inline int nextInt()
		{
			int x = 0;
			char c = nextChar();
			while(!('0' <= c && c <= '9')) c = nextChar();
			while('0' <= c && c <= '9')
			{
				x = x * 10 + c - '0';
				c = nextChar();
			}
			return x;
		}
		inline void printChar(char ch)
		{
			buf[cur++] = ch;
			if (cur == BUF_SIZE)
			{
				fwrite(buf, BUF_SIZE, 1, out);
				cur = 0;
			}
		}
		inline void printInt(int x)
		{
			if (x >= 10) printInt(x / 10);
			printChar(x % 10 + '0');
		}
		inline void close()
		{
			if (cur > 0)
			{
				fwrite(buf, cur, 1, out);
			}
			cur = 0;
		}
	} IO;
	inline void read(int &x){
		x=IO.nextInt();
	}
}
using namespace Grader;
int main(){
	freopen("mythological.in", "r", stdin);
	freopen("mythological.out", "w", stdout);
	int n,m,q,t;
	read(n);read(m);read(q);read(t);
	rep(i,1,n)read(c___a[i]);
	init(n,m,c___a,t);
	rep(i,1,q){
		int l,r;
		read(l);read(r);
		c___ans[i]=query(l,r);
	}
	IO.cur=0;
	rep(i,1,q)IO.printInt(c___ans[i]),IO.printChar('\n');
	IO.close();
	return 0;
}
#endif
