#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 1000 + 10, maxm = 1000 + 10;

int n, m, T, sx, sy;

struct node
{
	int x, y, t;
	node(int _x, int _y, int _t = 0):x(_x), y(_y), t(_t) {};
};

int fire[maxn][maxm];
bool a[maxn][maxm], vis[maxn][maxn];
int d[][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

queue <node> q;

int main()
{
#ifdef CraZYali
	freopen("11624.in", "r", stdin);
	freopen("11624.out", "w", stdout);
#endif
	cin >> T;
	
	while (T--)
	{
		while (!q.empty()) q.pop();	
		scanf("%d %d\n", &n, &m);
		REP(i, 1, n)
		{
			REP(j, 1, m)
			{
				register char c = getchar();
				if (c == '#') a[i][j] == 1;
				if (c == 'J') {sx = i;sy = j;}
				if (c == 'F') {q.push(node(i, j, 0));}
			}
			if (i ^ n) getchar();
		}
		memset(fire, 127 / 3, sizeof(fire));
		while (!q.empty())
		{
			node f = q.front();
			int x(f.x), y(f.y), t(f.t);
			q.pop();
			REP(i, 0, 3)
			{
				int tx = x + d[i][0];
				int ty = y + d[i][1];
				if (tx < 1 || tx > n || ty < 1 || ty > m) continue;
				if (!a[tx][ty] && t + 1 < fire[tx][ty]) q.push(node(tx, ty, fire[tx][ty] = t + 1));
			}
		}
		q.push(node(sx, sy, 0));
		memset(vis, 0, sizeof(vis));
		bool flag = 0;
		while (!q.empty())
		{
			node f = q.front();
			int x(f.x), y(f.y), t(f.t);
			if (x == 1 || x == n || y == 1 || y == n)
			{
				flag = 1;
				printf("%d\n", t);
				break;
			}
			q.pop();
			REP(i, 0, 3)
			{
				int tx = x + d[i][0];
				int ty = y + d[i][1];
				if (tx < 1 || tx > n || ty < 1 || ty > m) continue;
				if (!a[tx][ty] && !vis[tx][ty] && fire[tx][ty] >= t + 1)
				{
					vis[tx][ty] = 1;
					q.push(node(tx, ty, t + 1));
				}
			}
		}
		if (!flag) printf("IMPOSSIBLE\n");
	}
	return 0;
}
