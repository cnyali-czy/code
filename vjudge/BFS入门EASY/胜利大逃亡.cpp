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
const int maxn = 51;

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
int x, y, z, t;

bool G[maxn][maxn][maxn];

struct node
{
	int tx, ty, tz, t;
	node(int X, int Y, int Z, int T):tx(X), ty(Y), tz(Z), t(T){} 
};


int d[][3] = {{0, 0, 1}, {0, 0, -1}, {0, 1, 0}, {0, -1, 0}, {1, 0, 0}, {-1, 0, 0}};
queue <node> q;
bool vis[maxn][maxn][maxn];

int main()
{
#ifdef CraZYali
	freopen("胜利大逃亡.in", "r", stdin);
	freopen("胜利大逃亡.out", "w", stdout);
#endif
	register int T = read<int>();
	while (T --> 0)
	{
		memset(vis, 0, sizeof(vis));
		vis[1][1][1] = 1;
		x = read<int>();
		y = read<int>();
		z = read<int>();
		t = read<int>();
		REP(i, 1, x)
			REP(j, 1, y)
				REP(k, 1, z) G[i][j][k] = 1 ^ read<int>();
		
		while (!q.empty()) q.pop();
		q.push(node(1, 1, 1, 0));
		bool flag = 0;
		while (!q.empty())
		{
			if (flag) break;
			node X = q.front();
			if (X.t > t) goto over;
			else if (X.tx == x && X.ty == y && X.tz == z) {printf("%d\n", X.t);goto end;}
			q.pop();
			REP(i, 0, 5)
			{
				int tx = X.tx + d[i][0];
				int ty = X.ty + d[i][1];
				int tz = X.tz + d[i][2];
				int tt = X.t + 1;
				if (tx < 1 || tx > x || ty < 1 || ty > y || tz < 1 || tz > z) continue;
				if (vis[tx][ty][tz] || !G[tx][ty][tz]) continue;
				vis[tx][ty][tz] = 1;
				q.push(node(tx, ty, tz, tt));
			}
		}
over:	printf("-1\n");
end:;
	}
	
	return 0;
}
