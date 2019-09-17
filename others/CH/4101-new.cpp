/*
 * File Name:	4101-new.cpp
 * Author	:	CraZYali
 * Year		:	2019.09.16 19:34
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
const int N = 30000, maxn = N + 10;

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

int fa[maxn], siz[maxn], dep[maxn];
int find(int x)
{
	if (fa[x] == x) return x;
	int root = find(fa[x]);
	dep[x] += dep[fa[x]];
	return fa[x] = root;
}
inline void uni(int y, int x)
{
	x = find(x);y = find(y);
	if (x == y) return;
	dep[x] += siz[y];
	siz[y] += siz[x];
	fa[x] = y;
}
inline void init()
{
	REP(i, 1, N) siz[fa[i] = i] = 1;
}
#define abs(x) (max((x), -(x)))
inline int query(int x, int y)
{
	return find(x) == find(y) ? abs(dep[x] - dep[y]) : 0;
}

int main()
{
#ifdef CraZYali
	file("4101-new");
#endif
	init();
	int T;cin >> T;
	while (T--)
	{
		char c(getchar());
		while (!isalpha(c)) c = getchar();
		if (c == 'M') uni(read<int>(), read<int>());
		else printf("%d\n", -1 + query(read<int>(), read<int>()));
	}
	return 0;
}
