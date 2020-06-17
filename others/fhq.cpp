/*
	Problem:	fhq.cpp
	Time:		2020-06-17 16:19
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
#include <cstdlib>

using namespace std;
const int maxn = 1e5 + 10;

struct
{
	int ls, rs, v, s, order;
}t[maxn];
#define v(x) t[x].v
#define s(x) t[x].s
#define ls(x) t[x].ls
#define rs(x) t[x].rs
#define order(x) t[x].order

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

int n, cur, rt;
inline int newnode(int val)
{
	++cur;
	ls(cur) = rs(cur) = 0;
	v(cur) = val;
	s(cur) = 1;
	order(cur) = rand();
	return cur;
}
void pushup(int x) {s(x) = s(ls(x)) + s(rs(x)) + 1;}
void merge(int &x, int a, int b)
{
	if (!a || !b) x = a | b;
	else
	{
		if (order(a) > order(b)) merge(ls(x = b), a, ls(b));
		else merge(rs(x = a), rs(a), b);
		pushup(x);
	}
}
void split(int x, int &a, int &b, int val)
{
	if (!x) a = b = 0;
	else
	{
		if (v(x) > val) split(ls(b = x), a, ls(x), val);
		else split(rs(a = x), rs(x), b, val);
		pushup(x);
	}
}
void ins(int val)
{
	int x(0), y(0);
	split(rt, x, y, val);
	merge(x, x, newnode(val));
	merge(rt, x, y);
}
void del(int val)
{
	int x(0), y(0), z(0);
	split(rt, x, y, val);
	split(x, x, z, val - 1);
	merge(z, ls(z), rs(z));
	merge(x, x, z);
	merge(rt, x, y);
}
int getrank(int val)
{
	int x = rt, ans = 0;
	while (x)
	{
		if (val > v(x))
		{
			ans += s(ls(x)) + 1;
			x = rs(x);
		}
		else x = ls(x);
	}
	return ans + 1;
}
int getkth(int x, int k)
{
	while (1)
	{
		int le = s(ls(x)) + 1;
		if (k == le) return v(x);
		else if (k < le) x = ls(x);
		else
		{
			k -= le;
			x = rs(x);
		}
	}
}
int getkth(int k) {return getkth(rt, k);}
int pre(int val)
{
	int x = rt, ans = -1e7;
	while (x)
	{
		if (v(x) < val)
		{
			chkmax(ans, v(x));
			x = rs(x);
		}
		else x = ls(x);
	}
	return ans;
}
int suf(int val)
{
	int x = rt, ans = 1e7;
	while (x)
	{
		if (v(x) > val)
		{
			chkmin(ans, v(x));
			x = ls(x);
		}
		else x = rs(x);
	}
	return ans;
}
void dfs(int x)
{
	if (ls(x)) dfs(ls(x));
	printf("%d ", v(x));
	if (rs(x)) dfs(rs(x));
}

int main()
{
#ifdef CraZYali
	file("fhq");
#endif
	s(0) = 0;
	REP(Case, 1, read<int>())
	{
		int opt = read<int>(), x = read<int>();
		if (opt == 1)		ins(x);
		else if (opt == 2)	del(x);
		else if (opt == 3)	printf("%d\n", getrank(x));
		else if (opt == 4)	printf("%d\n", getkth(x));
		else if (opt == 5)	printf("%d\n", pre(x));
		else				printf("%d\n", suf(x));
	}
	return 0;
}

