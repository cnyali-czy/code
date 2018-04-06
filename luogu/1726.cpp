#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <queue>
#include <map>
#include <set>

using namespace std;
const int maxn = 5000 + 10, maxm = 50000 + 10;


int m, n, k;

int belong[maxn];

struct Graph
{
	int bg[maxn], ne[maxm << 1], to[maxm << 1], e;
	inline void add(int x, int y)
	{
		e++;
		to[e] = y;
		ne[e] = bg[x];
		bg[x] = e;
	}
	bool vis[maxn];
	void mark(int x)
	{
		vis[x] = 1;
		for (register int i = bg[x]; i ; i = ne[i])
			if (!vis[to[i]] && !belong[to[i]]) mark(to[i]);
	}
}G1, G2;

int siz[maxn];

int main()
{
#ifdef CraZYali
	freopen("1726.in", "r", stdin);
	freopen("1726.out", "w", stdout);
#endif
	cin >> n >> m;
	while (m --> 0)
	{
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		G1.add(x, y);
		G2.add(y, x);
		if (z == 2)
		{
			G1.add(y, x);
			G2.add(x, y);
		}
	}
	REP(i, 1, n)
		if (!belong[i])
		{
			memset(G1.vis, 0, sizeof(G1.vis));
			memset(G2.vis, 0, sizeof(G2.vis));
			G1.mark(i);
			G2.mark(i);
			++k;
			REP(j, 1, n)
				if (G1.vis[j] && G2.vis[j]) belong[j] = k;
		}
	REP(i, 1, n)
		siz[belong[i]]++;
	int Max = siz[1], cho = 1;
	REP(i, 2, k)
		if (siz[i] > Max) Max = siz[cho = i];
	cout << Max << endl;
	REP(i, 1, n)
		if (belong[i] == cho)
			printf("%d ", i);
	return 0;
}

