/*
	Problem:	F.cpp
	Time:		2021-05-26 20:18
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <set>
#include <queue>
#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 5e5 + 10;

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

int n, k, a[maxn], p[maxn], m;

vector <int> G[maxn];int in[maxn];
priority_queue <int, vector <int>, greater <int> > que;
inline void add(int x, int y) {G[x].emplace_back(y);in[y]++;}

struct node
{
	int v, mx, s, l, r, order;
	node() {v = mx = s = l = r = 0;}
	node(int v) : v(v), mx(v), s(1), l(0), r(0), order(rand()) {}
}t[maxn];int cur;
#define v(x) t[x].v
#define mx(x) t[x].mx
#define s(x) t[x].s
#define ls(x) t[x].l
#define rs(x) t[x].r
inline int newnode(int val)
{
	t[++cur] = node(val);
	return cur;
}
inline void pushup(int x)
{
	s(x) = s(ls(x)) + s(rs(x)) + 1;
	mx(x) = max(v(x), max(mx(ls(x)), mx(rs(x))));
}
void split(int x, int &a, int &b, int siz)
{
	if (!x) a = b = 0;
	else
	{
		if (s(ls(x)) >= siz) split(ls(b = x), a, ls(x), siz);
		else split(rs(a = x), rs(x), b, siz - s(ls(x)) - 1);
		pushup(x);
	}
}
void merge(int &x, int a, int b)
{
	if (!a || !b) x = a | b;
	else
	{
		if (t[a].order > t[b].order) merge(ls(x = b), a, ls(b));
		else merge(rs(x = a), rs(a), b);
		pushup(x);
	}
}
void dfs(int x)
{
	if (ls(x)) dfs(ls(x));
	p[++m] = v(x);
	if (rs(x)) dfs(rs(x));
}
int main()
{
#ifdef CraZYali
	file("F");
#endif
	n = read<int>();k = read<int>();
	REP(i, 1, n) p[a[i] = read<int>()] = i;
	int rt = newnode(1e9);
	DEP(i, n, 1)
	{
	/*
		REP(j, i, n - 1)
			if (p[j] - p[j + 1] >= k) swap(p[j], p[j + 1]);
			else break;*/
		int x = rt, y = 0, res = 0;
		while (x)
		{
			if (p[i] - mx(ls(x)) < k) x = ls(x);
			else if (p[i] - v(x) < k)
			{
				res += s(ls(x));
				break;
			}
			else res += s(ls(x)) + 1, x = rs(x);
		}

		split(rt, x, y, res);
		merge(x, x, newnode(p[i]));
		merge(rt, x, y);

	}
	dfs(rt);

	REP(i, 1, n) a[p[i]] = i;
	REP(i, 1, n) printf("%d\n", a[i]);
	return 0;
}
