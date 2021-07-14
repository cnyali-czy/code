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
#include <cstring>
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

#define fi first
#define se second
inline int a(int i, int j) {static const int MOD = C;return 1ll * A[i] * B[j] % MOD;}

inline bool chkmax(int &x, int y) {if (x < y) {x = y; return 1;} return 0;}
pair <int, string> calc(int x1, int y1, int x2, int y2)
{
	if (x1 == x2)
	{
		int res = 0;
		REP(j, y1, y2) res += a(x1, j);
		return make_pair(res, string(y2 - y1, 'R'));
	}
	if (y1 == y2)
	{
		int res = 0;
		REP(i, x1, x2) res += a(i, y1);
		return make_pair(res, string(x2 - x1, 'D'));
	}
	if (x2 == x1 + 1 && y2 == y1 + 1)
	{
		int res = a(x1, y1) + a(x2, y2), gor = a(x1, y2), god = a(x2, y1);
		if (gor > god) return make_pair(res + gor, "RD");
		else return make_pair(res + god, "DR");
	}
	if (x2 - x1 + 1 >= y2 - y1 + 1)
	{
		int mx = x1 + x2 >> 1;
		int ans = -inf;
		string path = "";
		REP(j, y1, y2)
		{
			auto r1 = calc(x1, y1, mx, j);
			auto r2 = calc(mx + 1, j, x2, y2);
			if (chkmax(ans, r1.fi + r2.fi)) path = r1.se + "D" + r2.se;
		}
		return make_pair(ans, path);
	}
	else
	{
		int my = y1 + y2 >> 1;
		int ans = -inf;
		string path = "";
		REP(i, x1, x2)
		{
			auto r1 = calc(x1, y1, i, my);
			auto r2 = calc(i, my + 1, x2, y2);
			if (chkmax(ans, r1.fi + r2.fi)) path = r1.se + "R" + r2.se;
		}
		return make_pair(ans, path);
	}
}

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
	int mx = x1 + x2 >> 1;
	static int f[maxn], g[maxn];
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
