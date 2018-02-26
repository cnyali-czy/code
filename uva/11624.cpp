#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 1000 + 10, maxm = 1000 + 10;

int DFS;

template <typename T> T read()
{
	T ans(0), p(1);
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}

int m, n, k, sx, sy;
char s[maxn][maxm];

struct node
{
	int x, y, t;
	node(int _x, int _y, int _t = 0) : x(_x), y(_y), t(_t) {}
};

bool vis[maxn][maxm];
int fire[maxn][maxm], d[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
#define inside(x, y) (1 <= x && x <= n && 1 <= y && y <= m)

int main()
{
#ifdef CraZYali
	freopen("11624.in", "r", stdin);
	freopen("11624.out", "w", stdout);
#endif
	register int T = read<int>();
	while (T--)
	{
		queue <node> q;
		n = read<int>();
		m = read<int>();
		REP(i, 1, n)
			scanf("%s", s[i] + 1);
		REP(i, 1, n)
			REP(j, 1, m)
				if (s[i][j] == 'J') {sx = i;sy = j;}
				else if (s[i][j] == 'F') {q.push(node(i, j));}
		memset(vis, 0, sizeof(vis));
		REP(i, 1, n)
			REP(j, 1, m)
				if (s[i][j] == '#') fire[i][j] = 1e9;
				else fire[i][j] = 0;
		while (!q.empty())
		{
			register node f = q.front();
			q.pop();
			register int x(f.x), y(f.y), t(f.t);
			fire[x][y] = t;
			REP(i, 0, 3)
			{
				int tx = x + d[i][0];
				int ty = y + d[i][1];
				if (inside(tx, ty) && s[tx][ty] ^ '#' && !fire[tx][ty])
					q.push(node(tx, ty, t + 1));
			}
		}
		bool flag = 0;
		q.push(node(sx, sy, 0));
		while (!q.empty())
		{
			register node f = q.front();
			q.pop();
			register int x(f.x), y(f.y), t(f.t);
			if (x == 1 || x == n || y == 1 || y == m)
			{
				printf("%d\n", t + 1);
				flag = 1;
				break;
			}
			if (fire[x][y] - 1<= t) continue;
			REP(i, 0, 3)
			{
				int tx = x + d[i][0];
				int ty = y + d[i][1];
				if (inside(tx, ty) && s[tx][ty] ^ '#' && !vis[tx][ty] && fire[tx][ty] > t + 1)
				{
					vis[tx][ty] = 1;
					q.push(node(tx, ty, t + 1));
				}
			}
		}
		if (!flag) printf("IMPOSSIBLE\n");
		fprintf(stderr, "%d\n", ++DFS);
	}

	return 0;
}
