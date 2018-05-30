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
const int maxn = 20, maxm = 2000 + 10, inf = (((1 << 30) - 1) << 1) + 1;

int bg[maxn], ne[maxm], to[maxm], w[maxm], e = 1;

inline void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
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
int m, n, k;

queue <int> q;
int dis[maxn];
inline bool BFS()
{
	memset(dis, -1, sizeof(dis));
	dis[1] = 0;
	q.push(1);
	while (!q.empty())
	{
		register int x = q.front();
		q.pop();
		for (register int i = bg[x]; i; i = ne[i])
			if (dis[to[i]] == -1 && w[i] > 0)
			{
				dis[to[i]] = dis[x] + 1;
				q.push(to[i]);
			}
	}
	return dis[n] != -1;
}

int dfs(int x, int y)
{
	if (x == n || !y) return y;
	for (register int i = bg[x]; i; i = ne[i])
		if (dis[to[i]] == dis[x] + 1 && w[i] > 0)
		{
			register int temp = dfs(to[i], min(y, w[i]));
			if (temp > 0)
			{
				w[i] -= temp;
				w[i ^ 1] += temp;
				return temp;
			}
		}
	return 0;
}

int main()
{
#ifdef CraZYali
	freopen("FlowProblem.in", "r", stdin);
	freopen("FlowProblem.out", "w", stdout);
#endif
	register int T = read<int>();
	REP(Case, 1, T)
	{
		memset(bg, 0, sizeof(bg));
		e = 1;

		n = read<int>();
		m = read<int>();
		while (m --> 0)
		{
			register int x, y, z;
			x = read<int>();y = read<int>(); z = read<int>();
			add(x, y, z);
			add(y, x, 0);
		}
		register int ans = 0;
		while (BFS()) ans += dfs(1, inf);
		printf("Case %d: %d\n", Case, ans);
	}
	return 0;
}
