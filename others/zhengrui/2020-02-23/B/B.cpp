/*
	Problem:	B.cpp
	Time:		2020-02-23 11:16
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 100 + 5, maxN = maxn * maxn, maxm = maxn;

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

int n, m, Free, id[maxn][maxm], N;
char s[maxn][maxm];

long long c2(long long x) {return x * (x - 1) / 2;}
int d[][2] = {{1, 0}, {0, 1}};
vector <int> G[maxN];

bool iscut[maxN];
int low[maxn], dfn[maxn], dfs_clock;
void tarjan(int u, int fa = -1)
{
	low[u] = dfn[u] = ++dfs_clock;
	int siz = 0;
	for (auto v : G[u]) if (v ^ fa)
		if (!dfn[v])
		{
			tarjan(v, u);
			chkmin(low[u], low[v]);
			siz++;
			if (low[v] >= dfn[u]) iscut[u] = 1;
		}
		else chkmin(low[u], dfn[v]);
	if (siz == 1 && fa == -1) iscut[u] = 0;
}
bool vis[maxN];
void dfs(int x, int y)
{
	if (x < 1 || x > n || y < 1 || y > m || s[x][y] == '*') return;
	if (vis[id[x][y]]) return;
	vis[id[x][y]] = 1;
	REP(i, 0, 1) dfs(x + d[i][0], y + d[i][1]);
}
int main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read<int>();m = read<int>();
	REP(i, 1, n)
	{
		scanf("%s", s[i] + 1);
		REP(j, 1, m) if (s[i][j] == '.') Free++;
	}
	if (s[1][1] == '*' || s[n][m] == '*')
	{
		cout << c2(Free) << endl;
		return 0;
	}
	REP(i, 1, n) REP(j, 1, m) id[i][j] = ++N;
	long long ans = 0;
	REP(i, 1, n) REP(j, 1, m) if (s[i][j] == '.')
	{
		s[i][j] = '*';
		REP(x, 1, n)
			REP(y, 1, m) if (s[x][y] == '.')
			{
				s[x][y] = '*';
				REP(I, 1, N) vis[I] = 0;
				dfs(1, 1);
				if (!vis[N]) ans++;
				s[x][y] = '.';
			}
		s[i][j] = '.';
	}
	cout << ans / 2 << endl;
	return 0;
}
