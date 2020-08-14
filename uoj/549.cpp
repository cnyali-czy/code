/*
	Problem:	549.cpp
	Time:		2020-08-14 11:50
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

inline void chkmin(int &x, int y) {if (x > y) x = y;}

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 60000 + 10, inf = 1e8;

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

int n, a[maxn], x[maxn], k;
int f[maxn], g[maxn], bst[1 << 8][1 << 8];

void ins(int j)
{
	int lj = (x[j - 1] >> 8) & 255, mj = x[j - 1] & 255;
	REP(m, 0, 255)
		chkmin(bst[lj][m ^ mj], g[j - 1] + m);
}

void work()
{
	swap(f, g);
	REP(i, 0, n) f[i] = inf;
	REP(i, 0, 255) REP(j, 0, 255) bst[i][j] = inf;
	REP(i, 1, n)
	{
		ins(i);
		int li = (x[i] >> 8) & 255, mi = x[i] & 255;
		REP(l, 0, 255)
		{
			int lj = li ^ l;
			chkmin(f[i], bst[lj][mi] + (l << 8));
		}
	}
}

int main()
{
#ifdef CraZYali
	file("549");
#endif
	n = read<int>();k = read<int>();
	REP(i, 1, n) a[i] = read<int>(), x[i] = x[i - 1] ^ a[i];
	REP(i, 1, n) f[i] = inf;
	REP(i, 1, k) work();
	REP(i, k, n) printf("%d%c", f[i], i == end_i ? '\n' : ' ');
	return 0;
}
