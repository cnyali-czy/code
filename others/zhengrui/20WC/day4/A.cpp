/*
 * File Name:	A.cpp
 * Author	:	CraZYali
 * Time		:	2020.02.08 23:38
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <unordered_map>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e5 + 10, maxN = 1e7 + 5;

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

//unordered_map <bool, int> ch[maxN];
int ch[maxN][2], s[maxN], cur;

inline int newnode()
{
	return ++cur;
}

int n, m, a[maxn], fa[maxn];

int bg[maxn], ne[maxn], to[maxn], e;
void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}
int dfn[maxn], siz[maxn], dfs_clock;

int rt[maxn];
void Insert(int p, int dep, int val)
{
	s[p]++;
	if (dep == -1) return;
	bool flag = !!(val & (1 << dep));
	if (!ch[p][flag]) ch[p][flag] = newnode();
	Insert(ch[p][flag], dep - 1, val);
}
void Delete(int p, int dep, int val)
{
	s[p]--;
	if (dep == -1) return;
	bool flag = !!(val & (1 << dep));
	if (!ch[p][flag]) ch[p][flag] = newnode();
	Delete(ch[p][flag], dep - 1, val);
	if (!s[ch[p][flag]])
	{
//		stack[++top] = ch[p][flag];
//		ch[p].erase(flag);
	}
}

void ins(int x, int y)
{
	while (x <= n)
	{
		Insert(rt[x], 30, y);
		x += x & -x;
	}
}
void del(int x, int y)
{
	while (x <= n)
	{
		Delete(rt[x], 30, y);
		x += x & -x;
	}
}

void dfs(int x)
{
	siz[x] = 1;
	dfn[x] = ++dfs_clock;
	for (int i = bg[x]; i; i = ne[i])
	{
		dfs(to[i]);
		siz[x] += siz[to[i]];
	}
	ins(dfn[x], a[x]);
	del(dfn[x] + siz[x], a[x]);
}

int rts[114], N;

int main()
{
#ifdef CraZYali
	file("A");
#endif
//	REP(i, 1, maxN - 5) stack[++top] = i;
	n = read<int>();
	m = read<int>();
	REP(i, 1, n)
	{
		rt[i] = newnode();
		Insert(rt[i], 30, 0);
		a[i] = read<int>();
	}
	REP(i, 2, n) add(fa[i] = read<int>(), i);
	dfs(1);
	while (m--)
	{
		int opt(read<int>()), x(read<int>());
		if (!opt)
		{
			int y = read<int>();
			del(dfn[x], a[x]);
			ins(dfn[x] + siz[x], a[x]);
			a[x] = y;
			ins(dfn[x], a[x]);
			del(dfn[x] + siz[x], a[x]);
		}
		else
		{
			int p = dfn[x];
			N = 0;
			while (p > 0)
			{
				rts[++N] = rt[p];
				p &= (p - 1);
			}
			int ans = 0;
			DEP(dep, 30, 0)
			{
				int flag = !!(a[x] & (1 << dep));
				int cnt = 0;
				REP(i, 1, N)
/*					if (ch[rts[i]].find(!flag) != ch[rts[i]].end()) */cnt += s[ch[rts[i]][!flag]];
				if (cnt > 0)
				{
					ans |= (1 << dep);
					REP(i, 1, N)
						/*if (ch[rts[i]].find(!flag) != ch[rts[i]].end()) */rts[i] = ch[rts[i]][!flag];
						//else rts[i] = 0;
				}
				else
					REP(i, 1, N)
						/*if (ch[rts[i]].find(flag) != ch[rts[i]].end()) */rts[i] = ch[rts[i]][flag];
						//else rts[i] = 0;
			}
			printf("%d\n", ans);
		}
	}
	return 0;
}
