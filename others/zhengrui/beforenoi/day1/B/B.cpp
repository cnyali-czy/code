/*
	Problem:	B.cpp
	Time:		2021-07-13 17:09
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
#define i64 long long

using namespace std;
const int maxn = 2e5 + 10, maxN = 2e7;

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

struct
{
	int ls, rs, siz, sum;
}t[maxN];int cur;
#define ls(p) t[p].ls
#define rs(p) t[p].rs
#define siz(p) t[p].siz
#define sum(p) t[p].sum
inline int clone(int x)
{
	t[++cur] = t[x];
	return cur;
}
void ins(int &p, i64 l, i64 r, i64 pos)
{
	p = (p ? ++cur : clone(p));
	if (l == r)
	{
		siz(p)++;
		sum(p)++;
	}
}

int main()
{
#ifdef CraZYali
	file("B");
#endif
	return 0;
}
