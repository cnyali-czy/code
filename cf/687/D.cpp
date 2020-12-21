/*
	Problem:	D.cpp
	Time:		2020-12-03 19:45
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1000 + 10, maxm = maxn * maxn / 2;

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

int n, m, q;
struct Edge
{
	int x, y, z, id;
	inline bool operator < (const Edge &B) const {return z > B.z;}
}E[maxm], t[maxm];

int fa[maxn << 1];
int find(int x) {return fa[x] == x ? x : fa[x] = find(fa[x]);}
void uni(int x, int y) {fa[find(x)] = find(y);}
bool Try(int x, int y)
{
	if (find(x) == find(y)) return 0;
	if (find(x + n) == find(y + n)) return 0;
	uni(x, y + n);uni(x + n, y);
	return 1;
}

int main()
{
#ifdef CraZYali
	file("D");
#endif
	n = read<int>();m = read<int>();q = read<int>();
	REP(i, 1, m)
	{
		E[i].x = read<int>();
		E[i].y = read<int>();
		E[i].z = read<int>();
		E[i].id = i;
	}
	sort(E + 1, E + 1 + m);
	while (q--)
	{
		int l = read<int>(), r = read<int>(), ans = -1;
		REP(i, 1, n + n) fa[i] = i;
		REP(i, 1, m) if (l <= E[i].id && E[i].id <= r)
		{
			if (!Try(E[i].x, E[i].y)) {ans = E[i].z;break;}
		}
		printf("%d\n", ans);
	}
	return 0;
}
