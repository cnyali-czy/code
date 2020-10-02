/*
	Problem:	A.cpp
	Time:		2020-10-02 19:37
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
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, a[maxn][3];

int p[maxn];
bool flag;
int pre(int x) {return x == 1 ? n : x + 1;}
bool vis[maxn][3];
void dfs(int x, int y)
{
	if (vis[x][y]) return;
	vis[x][y] = 1;
	if (x == n)
	{
		flag = 1;
		REP(i, 1, n) printf("%d%c", p[i], i == end_i ? '\n' : ' ');
		return;
	}
	else
	{
		x++;
		REP(i, 0, 2)
		{
			p[x] = a[x][i];
			if (p[x] == p[x - 1]) continue;
			if (x == n && p[x] == p[1]) continue;
			dfs(x, i);
			if (flag) return;
		}
	}
}

int main()
{
#ifdef CraZYali
	file("A");
#endif
	register int T = read<int>();
	while (T--)
	{
		n = read<int>();
		REP(i, 1, n) a[i][0] = read<int>();
		REP(i, 1, n) a[i][1] = read<int>();
		REP(i, 1, n) a[i][2] = read<int>();
		flag = 0;
		REP(i, 0, 2)
		{
			memset(vis, 0, sizeof vis);
			p[1] = a[1][i];
			dfs(1, i);
			if (flag) break;
		}
	}
	return 0;
}
