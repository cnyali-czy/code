/*
	Problem:	C.cpp
	Time:		2021-02-18 09:12
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUa fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <deque>
#include <queue>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 100 + 5;

template <typename T>
inline T read()
{
	T ans = 0, flag = 1;
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, m;
char a[maxn][maxn];
bool ban[maxn][maxn];
inline bool isc(char c) {return c == 'L' || c == 'R' || c == 'D' || c == 'U';}

struct node
{
	int x, y, d;
	node() {}
	node(int x, int y, int d) : x(x), y(y), d(d) {}
};
deque <node> que;
const int inf = 1e8;
int dis[maxn][maxn];
int D[][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

int main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();m = read<int>();
	REP(i, 1, n) scanf("%s", a[i] + 1);
	REP(i, 1, n) REP(j, 1, m) if (a[i][j] == 'C')
	{
		for (int x = i, y = j; a[x][y] != 'W'; x--) ban[x][y] = 1;
		for (int x = i, y = j; a[x][y] != 'W'; x++) ban[x][y] = 1;
		for (int x = i, y = j; a[x][y] != 'W'; y--) ban[x][y] = 1;
		for (int x = i, y = j; a[x][y] != 'W'; y++) ban[x][y] = 1;
	}
	REP(i, 1, n) REP(j, 1, m) if (isc(a[i][j])) ban[i][j] = 0;
	REP(i, 1, n) REP(j, 1, m) dis[i][j] = inf;
	REP(i, 1, n) REP(j, 1, m) if (a[i][j] == 'S' && !ban[i][j]) que.emplace_back(i, j, dis[i][j] = 0);
	while (que.size())
	{
		auto Node = que.front();que.pop_front();
		int x = Node.x, y = Node.y, d = Node.d;
		if (d > dis[x][y]) continue;
		if (isc(a[x][y]))
		{
			int tx = x + (a[x][y] == 'U') * (-1) + (a[x][y] == 'D');
			int ty = y + (a[x][y] == 'L') * (-1) + (a[x][y] == 'R');
			if (a[tx][ty] != 'W' && dis[tx][ty] > d && !ban[tx][ty])
				que.emplace_front(tx, ty, dis[tx][ty] = d);
		}
		else
		{
			REP(i, 0, 3)
			{
				int tx = x + D[i][0], ty = y + D[i][1];
				if (a[tx][ty] != 'W' && dis[tx][ty] > d + 1 && !ban[tx][ty])
					que.emplace_back(tx, ty, dis[tx][ty] = d + 1);
			}
		}
	}
	REP(i, 1, n) REP(j, 1, m) if (a[i][j] == '.') printf("%d\n", dis[i][j] < inf ? dis[i][j] : -1);
	return 0;
}
