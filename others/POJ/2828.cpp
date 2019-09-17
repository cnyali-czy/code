/*
 * File Name:	2828.cpp
 * Author	:	CraZYali
 * Year		:	2019.09.14 20:06
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 200000 + 10;

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

int ch[maxn][2], s[maxn], val[maxn], root, cur;
inline int newnode(int _val)
{
	++cur;
	ch[cur][0] = ch[cur][1] = 0;
	s[cur] = 1;
	val[cur] = _val;
	return cur;
}
#define ls(x) ch[x][0]
#define rs(x) ch[x][1]
inline void pushup(int x) {s[x] = s[ls(x)] + s[rs(x)] + 1;}
void split(int x, int &a, int &b, int siz)
{
	if (!x) a = b = 0;
	else
	{
		if (s[ls(x)] + 1 > siz) split(ls(b = x), a, ls(x), siz);
		else split(rs(a = x), rs(x), b, siz - s[ls(x)] - 1);
		pushup(x);
	}
}
void merge(int &x, int a, int b)
{
	if (!a || !b) x = a + b;
	else
	{
		if (s[a] < s[b]) merge(ls(x = b), a, ls(b));
		else merge(rs(x = a), rs(a), b);
		pushup(x);
	}
}
inline void insert(int pos, int _val)
{
	int x(0), y(0);
	split(root, x, y, pos);
	merge(x, x, newnode(_val));
	merge(root, x, y);
}
void output(int x = root)
{
	if (!x) return;
	output(ls(x));
	printf("%d ", val[x]);
	output(rs(x));
}

int main()
{
#ifdef CraZYali
	file("2828");
#endif
	int m;
	while (scanf("%d", &m) != EOF)
	{
		root = cur = 0;
		while (m--)
		{
			int pos(read<int>()), _val(read<int>());
			insert(pos, _val);
		}
		output();putchar(10);
	}	
	return 0;
}
