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
const int maxn = 100, maxm = 300;

int bg[maxn], ne[maxm << 1], to[maxm << 1], w[maxm << 1], e = 1;
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
int m, n, k, S, T;

queue <int> q;
int dis[maxn];
inline bool bfs()
{
	memset(dis, -1, sizeof(dis));
	dis[S] = 0;
	q.push(S);
	while (!q.empty())
	{
		register int x = q.front();
		q.pop();
		for (register int i = bg[x]; i ; i = ne[i])
			if (w[i] > 0 && dis[to[i]] == -1)
			{
				dis[to[i]] = dis[x] + 1;
				q.push(to[i]);
			}
	}
	return dis[T] != -1;
}

int dfs(int x, int y)
{
	if (x == T || !y) return y;
	for (register int i = bg[x]; i ; i = ne[i])
		if (w[i] > 0 && dis[to[i]] == dis[x] + 1)
		{
			int temp = dfs(to[i], min(w[i], y));
			if (temp > 0)
			{
				w[i] -= temp;
				w[i ^ 1] += temp;
				return temp;
			}
		}
	return 0;
}

int cnt[maxn][maxm];

int main()
{
#ifdef CraZYali
	freopen("10779.in", "r", stdin);
	freopen("10779.out", "w", stdout);
#endif
	register int C = read<int>();
	REP(Case, 1, C)
	{
		e = 1;
		memset(bg, 0, sizeof(bg));

		n = read<int>();
		m = read<int>();
		memset(cnt, 0, sizeof(cnt));
		REP(i, 1, n)
		{
			k = read<int>();
			while (k --> 0) cnt[i][read<int>()]++;
		}

		S = n + m + 1;
		T = n + m + 2;
		REP(i, 1, m) {add(S, n + i, cnt[1][i]);add(n + i, S, 0);}
		REP(i, 2, n)
			REP(j, 1, m)
				if (cnt[i][j] > 1)
				{
					add(i, n + j, cnt[i][j] - 1);
					add(n + j, i, 0);
				}
				else if (!cnt[i][j])
				{
					add(n + j, i, 1);
					add(i, n + j, 0);
				}
		REP(i, 1, m) {add(n + i, T, 1);add(T, n + i, 0);}
		int ans = 0;
		while (bfs()) ans += dfs(S, 1e9);
		printf("Case #%d: %d\n", Case, ans);
	}

	return 0;
}
