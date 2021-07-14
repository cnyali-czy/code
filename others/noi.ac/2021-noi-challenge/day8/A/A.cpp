/*
	Problem:	A.cpp
	Time:		2021-07-11 10:01
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <ctime>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 10000 + 10, inf = 1e9;

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

int n, C, A[maxn], B[maxn];

inline int a(int i, int j) {static const int MOD = C;return A[i] * B[j] % MOD;}

#define max(a, b) ( a > b ? a : b )
inline bool chkmax(int &x, int y) {if (x < y) {x = y; return 1;} return 0;}
void work(int x1, int y1, int x2, int y2)
{
	if (x1 == x2)
	{
		REP(i, 1, y2 - y1) putchar('R');
		return;
	}
	if (y1 == y2)
	{
		REP(i, 1, x2 - x1) putchar('D');
		return;
	}
	static int f[maxn], g[maxn];
	int mx = x1 + x2 >> 1;
	REP(i, y1 - 1, y2 + 1) f[i] = g[i] = -inf;
	f[y1] = 0;
	REP(i, x1, mx)
		REP(j, y1, y2) f[j] = max(f[j], f[j - 1]) + a(i, j);
	g[y2] = 0;
	DEP(i, x2, mx + 1)
		DEP(j, y2, y1) g[j] = max(g[j], g[j + 1]) + a(i, j);

	int res = -inf, bst;
	REP(i, y1, y2) if (chkmax(res, f[i] + g[i])) bst = i;
	work(x1, y1, mx, bst);
	putchar('D');
	work(mx + 1, bst, x2, y2);
}

int main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();C = read<int>();
	REP(i, 1, n) A[i] = read<int>();
	REP(i, 1, n) B[i] = read<int>();

	work(1, 1, n, n);
	cerr << clock() * 1. / CLOCKS_PER_SEC << endl;
	return 0;
}
