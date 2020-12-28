/*
	Problem:	A.cpp
	Time:		2020-12-28 09:22
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

inline void chkmin(int &x, int y) {if (x > y) x = y;}

#include <ctime>
#include <cstring>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 2000 + 10;

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
int lg[maxn];

namespace bf
{
	const int maxn = 600 + 5;
	char f[maxn][maxn][maxn];
	int dfs(int x, int y, int z)
	{
		if (x > z) swap(x, z);
		if (~f[x][y][z]) return f[x][y][z];
		if (x + y + z <= 1) return 0;
		if (!y) return lg[x + z];
		int res = 1e9;
		REP(i, 1, x)
			chkmin(res, max(dfs(i + y, 0, 0), dfs(x - i, y, z)));
		REP(i, 1, y - 1)
			chkmin(res, max(dfs(i, y - i, z), dfs(x, i, y - i)));
		REP(i, 1, z)
			chkmin(res, max(dfs(i + y, 0, 0), dfs(x, y, z - i)));
		return f[x][y][z] = res + 1;
	}
	void work()
	{
		memset(f, -1, sizeof f);
		REP(i, 0, n - 1) printf("%d%c", dfs(i, n - i, 0), i == end_i ? '\n' : ' ' );
	}
}

int main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();
	REP(i, 2, n) lg[i] = lg[i + 1 >> 1] + 1;
	bf :: work();
	cerr << clock() * 1. / CLOCKS_PER_SEC << endl;
	return 0;
}
