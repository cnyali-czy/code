/*
	Problem:	B.cpp
	Time:		2020-12-21 22:46
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
const int maxn = 1000 + 10, maxm = 1000 + 10, N = 1e6;

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

int n, m, a[maxn][maxm];
bool vis[maxn][maxm], went[N + 5];
vector <int> Div[N + 5];
pair <short, short> q[maxn * maxm];
int head, tail;

int main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read<int>();m = read<int>();
	int A = 0;
	REP(i, 1, n) REP(j, 1, m) A = max(A, a[i][j] = read<int>());
	REP(i, 1, n) REP(j, 1, A / i) Div[i * j].emplace_back(i);
	q[0] = make_pair(1, 1);vis[1][1] = 1;
	while (head <= tail)
	{
		int x = q[head].first, y = q[head].second;head++;
		if (x == n && y == m)
		{
			puts("yes");
			return 0;
		}
		if (went[a[x][y]]) continue;
		went[a[x][y]] = 1;
		for (int dx : Div[a[x][y]])
		{
			int dy = a[x][y] / dx;
			if (dy <= m && !vis[dx][dy])
			{
				vis[dx][dy] = 1;
				q[++tail] = make_pair(dx, dy);
			}
		}
	}
	puts("no");
	return 0;
}
