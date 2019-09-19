/*
 * File Name:	3224.cpp
 * Author	:	CraZYali
 * Year		:	2019.09.18 21:48
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;
const int maxn = 1e5 + 10;

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

int ch[maxn][2], s[maxn], order[maxn], val[maxn], root, cur;

#define ls(x) ch[x][0]
#define rs(x) ch[x][1]

inline void pushup(int x)
{
	s[x] = s[ls(x)] + s[rs(x)] + 1;
}
void merge(int &x, int a, int b)
{
	if (!a || !b) x = a + b;
	else
	{
		if (order[a] > order[b]) merge(ls(x = b), a, ls(b));
		else merge(rs(x = a), rs(a), b);
		pushup(x);
	}
}
void split(int x, int &a, int &b, int v)
{
	if (!x) a = b = 0;
	else
	{
		if (val[x] > v) split(ls(b = x), a, ls(x), v);
		else split(rs(a = x), rs(x), b, v);
		pushup(x);
	}
}
inline int newnode(int v)
{
	++cur;
	order[cur] = rand();
	s[cur] = 1;
	val[cur] = v;
	return cur;
}
inline void insert(int v)
{
	int x(0), y(0);
	split(root, x, y, v);
	merge(x, x, newnode(v));
	merge(root, x, y);
}
inline void del(int v)
{
	int x(0), y(0), z(0);
	split(root, x, y, v - 1);
	split(y, y, z, v);
	merge(y, ls(y), rs(y));
	merge(y, y, z);
	merge(root, x, y);
}
inline int _rank(int v)
{
	int x(0), y(0);
	split(root, x, y, v - 1);
	int ans(s[x] + 1);
	merge(root, x, y);
	return ans;
}
inline int kth(int k, int x = root)
{
	while (s[ls(x)] + 1 != k)
		if (s[ls(x)] + 1 > k) x = ls(x);
		else k -= s[ls(x)] + 1, x = rs(x);
	return val[x];
}
inline int pre(int v)
{
	int x(0), y(0);
	split(root, x, y, v-1);
	int ans(kth(s[x], x));
	merge(root, x, y);
	return ans;
}
inline int nxt(int v)
{
	int x(0), y(0);
	split(root, x, y, v);
	int ans(kth(1, y));
	merge(root, x, y);
	return ans;
}

int main()
{
#ifdef CraZYali
	file("3224");
#endif
	int n(read<int>());
	while (n--)
	{
		int opt(read<int>()), x(read<int>());
		if (opt == 1) insert(x);
		else if (opt == 2) del(x);
		else if (opt == 3) printf("%d\n", _rank(x));
		else if (opt == 4) printf("%d\n", kth(x));
		else if (opt == 5) printf("%d\n", pre(x));
		else if (opt == 6) printf("%d\n", nxt(x));
	}
	return 0;
}
