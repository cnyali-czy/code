/*
 * File Name:	table.cpp
 * Author	:	CraZYali
 * Year		:	2019.10.20 10:02
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))
int back[233333];
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

template <typename T> inline T read()
{
	T ans(0), flag(1);
	char c(getchar());
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout), freopen(FILE_NAME".err", "w", stderr);

int a[3][3], b[3][3], c[3][3];
int id[1000], cnt;

inline void suan()
{
	c[0][2] = b[0][0];
	c[1][2] = b[0][1];
	c[2][2] = b[0][2];
	c[0][1] = b[1][0];
	c[1][1] = b[1][1];
	c[2][1] = b[1][2];
	c[0][0] = b[2][0];
	c[1][0] = b[2][1];
	c[2][0] = b[2][2];
	REP(i, 0, 2)
		REP(j, 0, 2) b[i][j] = c[i][j];
}
inline void zy()
{
	REP(i, 0, 2) swap(b[i][0], b[i][2]);
}
inline void sx()
{
	REP(i, 0, 2) swap(b[0][i], b[2][i]);
}
inline void spy()
{
	REP(i, 0, 2) if (b[0][i]) return;
	REP(i, 1, 2)
		REP(j, 0, 2) b[i-1][j] = b[i][j];
	REP(i, 0, 2) b[2][i] = 0;
}
inline void zpy()
{
	REP(i, 0, 2) if (b[i][0]) return;
	REP(i, 0, 2)
		REP(j, 1, 2) b[i][j-1] = b[i][j];
	REP(i, 0, 2) b[i][2] = 0;
}

int qaqaq;
bool vis[3][3];

void dfs(int x, int y)
{
	if (x < 0 || x > 2 || y < 0 || y > 2 || !a[x][y] || vis[x][y]) return;
	vis[x][y] = 1;
	qaqaq++;
	dfs(x - 1, y);
	dfs(x, y - 1);
	dfs(x + 1, y);
	dfs(x, y + 1);
}

int get_ccc()
{
	int ccc(0);
	REP(i, 0, 2)
		REP(j, 0, 2)
		ccc |= (b[i][j] << (i * 3 + j));
	return ccc;
}
int main()
{
	file("table");
	srand(time(0));
	REP(status, 1, 511)
	{
		REP(i, 0, 2)
			REP(j, 0, 2)
			b[i][j] = a[i][j] = !!(status & (1 << (i * 3 + j))), vis[i][j] = 0;
		qaqaq = 0;
		REP(i, 0, 2)
			REP(j, 0, 2) if (a[i][j])
			{
				dfs(i, j);
				goto ne;
			}
ne:		if (qaqaq != __builtin_popcount(status)) continue;
		int &I = id[status];
		REP(times, 1, 10000)
		{
			switch (rand() % 5)
			{
				case 0:
					suan();
					break;
				case 1:
					zy();
					break;
				case 2:
					sx();
					break;
				case 3:
					zpy();
					break;
				case 4:
					spy();
					break;
			}
			int ccc = get_ccc();
			if (id[ccc])
			{
				I = id[ccc];
				break;
			}
		}
		if (!I)
		{
			I = ++cnt;
			cout << cnt << endl;
			REP(i, 0, 2)
				REP(j, 0, 2) printf("%d%c", a[i][j], j == 2 ? '\n' : ' ');
			puts("-------");
			back[cnt] = status;
		}
	}
	cout << cnt << endl;
	REP(i, 0, 511) fprintf(stderr,"%d,",id[i]);cerr<<endl;
	REP(i, 0, cnt) fprintf(stderr,"%d,",back[i]);cerr<<endl;
	return 0;
}
