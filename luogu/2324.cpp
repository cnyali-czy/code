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
const int maxn = 10;

int fina[][6] = {
				{0, 0, 0, 0, 0, 0},
				{0, 1, 1, 1, 1, 1},
				{0, 0, 1, 1, 1, 1},
				{0, 0, 0, -1, 1, 1},
				{0, 0, 0, 0, 0, 1},
				{0, 0, 0, 0, 0, 0}
				};

int T, least;
int ex, ey;

char s[maxn][maxn];
int a[maxn][maxn];

//int d[][2] = {{1, 2}, {1, -2}, {2, 1}, {2, -1}, {-1, 2}, {-1, -2}, {-2, 1}, {-2, -1}};

int d[][2] = {{-2, -1}, {-2, 1}, {-1, 2}, {1, 2}, {-1, -2}, {1, -2}, {2, -1}, {2, 1}};

bool dfs(int cost, int x, int y, int rest, int Max, int last = -1)
{
	if (cost + rest > Max) return 0 ;
	if (!rest) return 1;

	cost++;
	REP(i, 0, 7)
		if (i != (7 - last) )
		{
			int tx = x + d[i][0];
			int ty = y + d[i][1];
			if (tx < 1 || tx > 5 || ty < 1 || ty > 5) continue;
			else
			{
				int temp = rest;
				if (a[tx][ty] == fina[tx][ty] && a[tx][ty] != fina[x][y]) ++temp;
				if (a[tx][ty] != fina[tx][ty] && a[tx][ty] == fina[x][y]) --temp;
				if (fina[tx][ty] == -1) --temp;
				if (fina[x][y] == -1) ++temp;
				swap(a[tx][ty], a[x][y]);
				bool flag = dfs(cost, tx, ty, temp, Max, i);
				swap(a[tx][ty], a[x][y]);
				if (flag) return 1;
			}
		}
	return 0;
}

int main()
{
#ifdef CraZYali
	freopen("2324.in", "r", stdin);
	freopen("2324.out", "w", stdout);
	freopen("2324.err", "w", stderr);
#endif
	cin >> T;
	while (T --> 0)
	{
		least = 0;
		REP(i, 1, 5)
			scanf("%s", s[i] + 1);
		REP(i, 1, 5)
			REP(j, 1, 5)
			{
				if (s[i][j] == '*') a[ex = i][ey = j] = -1;
				else a[i][j] = s[i][j] - '0';
				least += a[i][j] != fina[i][j];
			}
		
		bool suc = 0;
		REP(i, least, 16)
			if (dfs(0, ex, ey, least, i))
			{
				printf("%d\n", i - 1);
				suc = 1;
				break;
			}
		if (!suc) printf("-1\n");
	}
	return 0;
}
