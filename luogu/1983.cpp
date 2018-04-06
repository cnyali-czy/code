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
const int maxn = 1000 + 10, maxm = 1000 + 10;

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
int size[maxm], in[maxn];
set <int> s[maxm];

queue <int> q;
int dis[maxn];

bool G[maxn][maxn];

inline void BFS()
{
	memset(dis, -1, sizeof(dis));
	int ans = 1;
	REP(i, 1, n)
		if (!in[i])
		{
			q.push(i);
			dis[i] = 1;
		}
	while (!q.empty())
	{
		register int x = q.front();
		q.pop();
		REP(to, 1, n)
			if (G[x][to] && in[to])
			{
				in[to]--;
				if (!in[to] && dis[to] == -1)
				{
					q.push(to);
					dis[to] = dis[x] + 1;
					chkmax(ans, dis[to]);
				}
			}
	}
	cout << ans;
}

int a[maxn][maxn];
bool has[maxn][maxn];

int main()
{
#ifdef CraZYali
	freopen("1983.in", "r", stdin);
	freopen("1983.out", "w", stdout);
#endif
	n = read<int>();
	m = read<int>();
	REP(i, 1, m)
	{
		size[i] = read<int>();
		REP(j, 1, size[i])
			has[i][a[i][j] = read<int>()] = 1;

	}
	REP(i, 1, m)
		REP(j, a[i][1], a[i][size[i]])
			if (!has[i][j])
				REP(k, 1, size[i])
					if (!G[a[i][k]][j])
					{
						G[a[i][k]][j] = 1;
						in[j]++;
					}

	BFS();
	return 0;
}
