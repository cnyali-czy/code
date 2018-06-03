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

int m, n, k;

bool vis[maxn];
int belong[maxn], size[maxn], cnt;

struct Graph
{
	int bg[maxn], ne[maxm], to[maxm], e;
	Graph() {memset(bg, 0, sizeof(bg));e = 0;}
	inline void add(int x, int y)
	{
		e++;
		to[e] = y;
		ne[e] = bg[x];
		bg[x] = e;
	}
	void dfs(int x, bool mode)
	{
		if (!mode) vis[x] = 1;
		else size[belong[x] = cnt]++;
		for (register int i = bg[x]; i ; i = ne[i])
			if (!mode && !vis[to[i]] && !belong[to[i]]) dfs(to[i], 0);
			else if (mode && vis[to[i]] && !belong[to[i]]) dfs(to[i], 1);
	}
}A, B;

inline void get_belong()
{
	REP(i, 1, n)
		if (!belong[i])
		{
			for (register int j = 1; j <= n ; j += 5) vis[j] = vis[j + 1] = vis[j + 2] = vis[j + 3] = vis[j + 4] = 0;
			cnt++;
			A.dfs(i, 0);
			B.dfs(i, 1);
		
		}
}

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

int out[maxn];

int main()
{
#ifdef CraZYali
	freopen("PopularCows.in", "r", stdin);
	freopen("PopularCows.out", "w", stdout);
#endif
	n = read<int>();
	m = read<int>();
	while (m--)
	{
		register int x, y;
		x = read<int>(); y = read<int>();
		A.add(x, y);B.add(y, x);
	}
	get_belong();
	REP(x, 1, n)
		for (register int i = A.bg[x]; i ; i = A.ne[i])
			if (belong[x] ^ belong[A.to[i]]) out[belong[x]]++;
	register int ans = 0, count = 0;
	REP(i, 1, cnt)
		if (!out[i]) {count++;ans += size[i];}
	if (count ^ 1) cout << 0;
	else cout << ans;
	return 0;
}
