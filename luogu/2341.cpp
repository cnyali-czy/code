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
const int maxn = 10000 + 10, maxm = 50000 + 10;

int belong[maxn];

struct Graph
{
	int bg[maxn], ne[maxm], to[maxm], e;
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
		for (register int i = bg[x]; i ;i = ne[i])
			if (!vis[to[i]] && !belong[to[i]]) mark(to[i]);
	}
}G1, G2;

template <typename T> T read()
{
	T ans(0), p(1);
	char c = getchar();
	while (!isdigit(c)) {
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c)) {
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}
int m, n, k;

int out[maxn];
set <int> G[maxn];

int main()
{
#ifdef CraZYali
	freopen("2341.in", "r", stdin);
	freopen("2341.out", "w", stdout);
#endif
	n = read<int>();
	m = read<int>();
	while (m--)
	{
		int x(read<int>()), y(read<int>());
		G1.add(x, y);
		G2.add(y, x);
	}
	
	REP(i, 1, n)
		if (!belong[i])
		{
			++k;
			memset(G1.vis, 0, sizeof(G1.vis));
			memset(G2.vis, 0, sizeof(G2.vis));
			G1.mark(i);
			G2.mark(i);
			REP(j, 1, n)
				if (G1.vis[j] && G2.vis[j])
					belong[j] = k;
		}
#define bg G1.bg
#define ne G1.ne
#define to G1.to
	REP(x, 1, n)
		for (register int i = bg[x]; i ; i = ne[i])
			if (belong[x] ^ belong[to[i]] && G[belong[x]].find(belong[to[i]]) == G[belong[x]].end())
			{
				G[belong[x]].insert(belong[to[i]]);
				out[belong[x]]++;
			}
	int ans = 0, cnt = 0;
	REP(i, 1, k)
		if (!out[i])
		{
			REP(j, 1, n) ans += belong[j] == i;
			cnt++;
		}
	if (cnt == 1) cout << ans;
	else cout << 0;
	return 0;
}
