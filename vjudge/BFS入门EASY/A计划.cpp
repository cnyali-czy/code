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
const int maxn = 10 + 5, maxm = 10 + 5;

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
int m, n, t;

char s[2][maxn][maxm];
int d[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#define node pair <pair <int, int> , pair<int, int> >

queue <node> q;

bool vis[maxn][maxn][2];

int main()
{
#ifdef CraZYali
	freopen("A计划.in", "r", stdin);
	freopen("A计划.out", "w", stdout);
#endif
	register int T = read<int>();
	while (T --> 0)
	{
		memset(vis, 0, sizeof(vis));
		n = read<int>();
		m = read<int>();
		t = read<int>();
		REP(i, 0, 1)
			REP(j, 1, n)
				scanf("%s", s[i][j] + 1);
		while (!q.empty()) q.pop();
		REP(i, 0, 1)
			REP(j, 1, n)
				REP(k, 1, m)
					if (s[i][j][k] == 'S')
					{
						q.push(make_pair(make_pair(j, k), make_pair(i, 0)));
						s[i][j][k] = '*';
						goto no;
					}
no:;
		bool flag = 0;
		while (!q.empty())
		{
			node x = q.front();
			if (x.second.second > t)
			{
				printf("NO\n");
				flag = 1;
				break;
			}
			if (s[x.second.first][x.first.first][x.first.second] == 'P')
			{
				printf("YES\n");
				flag = 1;
				break;
			}
			q.pop();
			REP(i, 0, 3)
			{
				int tx = x.first.first + d[i][0];
				int ty = x.first.second + d[i][1];
				int tz = x.second.first;
				if (tx < 1 || tx > n || ty < 1 || ty > m) continue;
				if (vis[tx][ty][tz] || s[tz][tx][ty] == '*') continue;
				if (s[tz][tx][ty] == '#')
				{
					tz ^= 1;
					if (vis[tx][ty][tz] || s[tz][tx][ty] == '*' || s[tz][tx][ty] == '#') continue;
				}
				vis[tx][ty][tz] = 1;
				q.push(make_pair(make_pair(tx, ty), make_pair(tz, x.second.second + 1)));
			}
		}
		if (!flag) printf("NO\n");
	}

	return 0;
}
