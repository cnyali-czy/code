/*
	Problem:	B.cpp
	Time:		2020-12-30 15:02
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <bitset>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e5 + 10, maxq = 1e5 + 10, maxk = 12, inf = 1e9;

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

int n, k, q, N;
int a[maxk][maxn], id[maxn][maxk];
bitset <1 << maxk> B[maxk + maxq];

int main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read<int>();k = read<int>();q = read<int>();
	N = k - 1;
	REP(i, 0, k - 1)
	{
		REP(j, 0, n - 1) a[i][j] = read<int>();
		REP(j, 0, (1 << k) - 1) if (j >> i & 1)
			B[i][j] = 1;
	}
	REP(i, 0, n - 1)
	{
		REP(j, 0, k - 1) id[i][j] = j;
		sort(id[i], id[i] + k, [&](int x, int y) {return a[x][i] > a[y][i];});
	}
	while (q--)
	{
		int opt = read<int>(), x = read<int>() - 1, y = read<int>() - 1;
		if (opt == 1) B[++N] = B[x] | B[y];
		else if (opt == 2) B[++N] = B[x] & B[y];
		else
		{
			int s = 0;
			REP(i, 0, k - 1)
				if (B[x][s |= (1 << id[y][i])])
				{
					printf("%d\n", a[id[y][i]][y]);
					break;
				}
		}
	}
	return 0;
}
