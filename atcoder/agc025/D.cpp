/*
	Problem:	3967.cpp
	Time:		2020-12-28 22:08
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <cmath>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 605;

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
int n;

inline int sqr(int x) {return x * x;}
int id(int x, int y)
{
	return (x - 1) * (n + n) + y;
}

vector <int> G[maxn * maxn];
int col[2][maxn * maxn], *C;
void dfs(int u)
{
	for (int v : G[u]) if (!C[v])
	{
		C[v] = 3 - C[u];
		dfs(v);
	}
}
void work(int d)
{
	REP(i, 1, sqr(n + n)) G[i].clear();
	REP(x1, 1, n + n)
		REP(x2, 1, n + n)
		{
			int xx = sqr(x1 - x2);
			if (xx > d) continue;
			int yy = d - xx, dy = sqrt(yy);
			if (dy * dy != yy) continue;
			REP(y1, 1, n + n - dy)
			{
				int y2 = y1 + dy;
				G[id(x1, y1)].emplace_back(id(x2, y2));
				G[id(x2, y2)].emplace_back(id(x1, y1));
			}
		}
	REP(i, 1, sqr(n + n)) if (!C[i])
	{
		C[i] = 1;
		dfs(i);
	}
}

int main()
{
#ifdef CraZYali
	file("3967");
#endif
	n = read<int>();
	C = col[0];work(read<int>());
	C = col[1];work(read<int>());
	REP(c1, 1, 2) REP(c2, 1, 2)
	{
		int tot = 0;
		REP(i, 1, sqr(n + n)) if (col[0][i] == c1 && col[1][i] == c2) tot++;
		if (tot < sqr(n)) continue;
		tot = 0;
		REP(i, 1, n + n) REP(j, 1, n + n)
			if (col[0][id(i, j)] == c1 && col[1][id(i, j)] == c2)
			{
				printf("%d %d\n", i - 1, j - 1);
				if ((++tot) == sqr(n)) return 0;
			}
	}
	return 0;
}
