#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#include <cstring>
#include <cmath>
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;
const int maxn = 1000 + 10;

int n, m, G[maxn][maxn];

inline void chkmax(int &x, int y)
{
	if (x < y) x = y;
}

int bg[maxn], ne[maxn << 1], to[maxn << 1], w[maxn << 1], e;
inline void add(int x, int y, int z)
{
	e++;
	w[e] = z;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

int main()
{
#ifdef CraZYali
	freopen("vector.in", "r", stdin);
	freopen("vector.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 2, n)
	{
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		add(x, y, z);
		add(y, x, z);
	}
	return 0;
}
