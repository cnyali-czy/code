/*
	Problem:	2479.cpp
	Time:		2020-03-03 23:03
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <cstring>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e5 + 10;

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

int n, m;
char s[maxn];

namespace SAM
{
	const int maxN = maxn << 1;
	const int siz = 10;
	int ch[maxN][siz], fail[maxN], len[maxN], pos[maxN], lst = 1, cur = 1;
	inline int newnode(int l, int p = 0)
	{
		pos[++cur] = p;
		len[cur] = l;
		return cur;
	}
	inline void extend(int c, int i)
	{
		int v = lst, u = newnode(len[v] + 1, i);
		for (; !ch[v][c]; v = fail[v]) ch[v][c] = u;
		if (!v) fail[u] = 1;
		else if (len[ch[v][c]] == len[v] + 1) fail[u] = ch[v][c];
		else
		{
			int Old(ch[v][c]), New(newnode(len[v] + 1));
			copy(ch[Old], ch[Old] + siz, ch[New]);
			fail[New] = fail[Old];
			fail[Old] = fail[u] = New;
			for (; ch[v][c] == Old;v = fail[v]) ch[v][c] = New;
		}
		lst = u;
	}
}

namespace SMT
{
#define lson ls[p], l, mid
#define rson rs[p], mid + 1, r
#define mid (l + r >> 1)
#undef mid
}

int main()
{
#ifdef CraZYali
	file("2479");
#endif
	n = read<int>();m = read<int>();
	scanf("%s", s + 1);
	REP(i, 1, n) SAM::extend(s[i] - '0', i);
	return 0;
}
