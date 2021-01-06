/*
	Problem:	A.cpp
<<<<<<< HEAD
	Time:		2020-12-27 08:45
=======
	Time:		2020-12-28 09:22
>>>>>>> c7192327a6a74668e86d9a3a81fdc68e3571f230
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

<<<<<<< HEAD
#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cmath>
=======
inline void chkmin(int &x, int y) {if (x > y) x = y;}

#include <ctime>
#include <cstring>
>>>>>>> c7192327a6a74668e86d9a3a81fdc68e3571f230
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
<<<<<<< HEAD
		ans = ans * 10 + c - 48;
=======
		ans = ans * 10 + (c - 48);
>>>>>>> c7192327a6a74668e86d9a3a81fdc68e3571f230
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)
<<<<<<< HEAD
int n;

int c1(int n) {return n == 0 ? 0 : (int)ceil(log2(n));}
=======

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
>>>>>>> c7192327a6a74668e86d9a3a81fdc68e3571f230

int main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();
<<<<<<< HEAD
	REP(x, 1, n)
	{
		int ans = 1 + c1(n);
		REP(y, x, n)
		{
			int res = 0;
			ans = max(ans, 2 * c1(n - x + 1) + 1);
		}
		printf("%d%c", ans, x == end_x ? '\n' : ' ');
	}
=======
	REP(i, 2, n) lg[i] = lg[i + 1 >> 1] + 1;
	bf :: work();
	cerr << clock() * 1. / CLOCKS_PER_SEC << endl;
>>>>>>> c7192327a6a74668e86d9a3a81fdc68e3571f230
	return 0;
}
