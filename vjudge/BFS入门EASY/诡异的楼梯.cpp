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
const int maxn = 21, maxm = 21;

int m, n, k;
char a[maxn][maxm];
int vis[maxn][maxm][2];

struct node
{
	int x, y, t;
	bool operator < (node B) const {return t > B.t;}
}pp, p;
queue <node> q;

int sx, sy, Tx, Ty;
int d[][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

int main()
{
#ifdef CraZYali
	freopen("诡异的楼梯.in", "r", stdin);
	freopen("诡异的楼梯.out", "w", stdout);
#endif
	while (cin >> n >> m)
	{
		REP(i, 1, n) scanf("%s\n", a[i] + 1);
		REP(i, 1, n)
			REP(j, 1, m)
				if (a[i][j] == 'S') {sx = i;sy = j;}
				else if (a[i][j] == 'T') {Tx = i;Ty = j;}
		if (sx == Tx && sy == Ty) {cout << 0 << endl;continue;}
		while (!q.empty()) q.pop();
		memset(vis, 127 / 3, sizeof(vis));
		vis[sx][sy][0] = 0;
		pp.x = sx;pp.y = sy;pp.t = 0;
		q.push(pp);
		while (!q.empty())
		{
			pp = q.front();
			q.pop();
			REP(i, 0, 3)
			{
				p = pp;
				int tx = p.x + d[i][0];
				int ty = p.y + d[i][1];
				if (tx < 1 || tx > n || ty < 1 || ty > m) continue;
				if (a[tx][ty] == '*') continue;
				bool flag = 0 ;
				while (a[tx][ty] == '|' || a[tx][ty] == '-')
				{
					char t = a[tx][ty];
					if (p.t % 2)
						if (t == '|') t = '-';
						else t = '|';
					if (t == '|')
					{
						if (p.x > tx) tx--;
						else tx++;
						if (tx < 1 || tx > n) goto no;
					}
					else
					{
						if (p.y > ty) ty--;
						else ty++;
						if (ty < 1 || ty > m) goto no;
					}
					flag = 1;
					p.t++;
				}
				p.t = p.t + 1 - flag;
				if (p.t >= vis[tx][ty][p.t % 2]) continue;
				else vis[tx][ty][p.t % 2] = p.t;
				if (tx == Tx && ty == Ty)
				{
					printf("%d\n", p.t);
					goto end;
				}
				p.x = tx;p.y = ty;
				q.push(p);
	no:;
			}
		}
end:;
	}
	return 0;
}
