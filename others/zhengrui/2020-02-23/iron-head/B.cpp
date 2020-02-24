/*
 * test
	Problem:	B.cpp
	Time:		2020-02-24 15:42
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cstring>
#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;
const int maxn = 3000 + 10, maxm = 3000 + 10;

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
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, m;
char s[maxn][maxm];

int d[][2] = {{1, 0}, {0, 1}};
int id[][2] = {{-1, 0}, {0, -1}};
bool p[maxn][maxm];

inline long long c2(int x) {return x * (x - 1ll) / 2;}
inline int getfree()
{
	int res = 0;
	REP(i, 1, n) REP(j, 1, m) res += (s[i][j] == '.');
	return res;
}

void get_p(int x, int y)
{
	if (x < 1 || x > n || y < 1 || y > m || s[x][y] == '*') return;
	p[x][y] = 1;
	REP(i, 0, 1) get_p(x + id[i][0], y + id[i][1]);
}

void get_lmost(int x, int y, vector <pair <int, int> > &lmost)
{
	lmost.emplace_back(x, y);
	if (p[x + 1][y])	get_lmost(x + 1, y, lmost);
	else				get_lmost(x, y + 1, lmost);
}
void get_rmost(int x, int y, vector <pair <int, int> > &rmost)
{
	rmost.emplace_back(x, y);
	if (p[x][y + 1])	get_rmost(x, y + 1, rmost);
	else				get_rmost(x + 1, y, rmost);
}
vector <pair <int, int> > lmost, rmost;

namespace run
{
	const int N = 3010;
	int c;
	bool fs[N][N], ft[N][N], U[N][N], D[N][N];
	int main()
	{
		c = getfree();
		REP(i, 1, n)
			REP(j, 1, m) if (s[i][j] == '.' && (make_pair(i, j) == make_pair(1, 1) || fs[i-1][j] || fs[i][j-1]))
			fs[i][j] = 1;
		DEP(i, n, 1)
			DEP(j, m, 1) if (s[i][j] == '.' && (make_pair(i, j) == make_pair(n, m) || ft[i+1][j] || ft[i][j+1]))
			ft[i][j] = 1;

		if (!ft[1][1])
		{
			cout << c2(c) << endl;
			return 0;
		}
		int x = 1, y = 1;
		REP(t, 1, n + m - 1)
		{
			U[x][y] = 1;
			if(ft[x][y + 1]) y ++; else x ++;
		}
		x = 1, y = 1; long long ans = 0;
		REP(t, 1, n + m - 1)
		{
			int nx, ny;
			for(nx = x - 1; nx >= 1; nx --)
			{
				ny = x + y - nx;
				if(ny > m) { nx = 0; break ; }
				if(fs[nx][ny] && ft[nx][ny]) break ;
			}
			D[x][y] = 1;
			if(!nx)
				ans += c - t;
			else {
				for(int tx = nx, ty = ny; ; )
				{
					if(!D[tx][ty] && U[tx][ty])  ans ++;
					if(tx == 1 && ty == 1) break ;
					if(fs[tx][ty - 1]) ty --; else tx --;
				}
				for(int tx = nx, ty = ny; ; )
				{
					if(!(tx == nx && ty == ny) && !D[tx][ty] && U[tx][ty]) ans ++;
					if(tx == n && ty == m) break ;
					if(ft[tx + 1][ty]) tx ++; else ty ++;
				}
			}
			if(ft[x + 1][y]) x ++; else y ++;
		}
		cout << ans << '\n';
		return 0;
	}
}

int main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read<int>();m = read<int>();
	REP(i, 1, n) scanf("%s", s[i] + 1);
	return run::main();
	get_p(n, m);
	if (!p[1][1])
	{
		cout << c2(getfree());
		return 0;
	}
	get_lmost(1, 1, lmost);
	get_rmost(1, 1, rmost);
	for (auto i : lmost)
	{
		s[i.first][i.second] = '*';
	}
	return 0;
}
