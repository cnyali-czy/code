/*
	Problem:	3524.cpp
	Time:		2020-08-03 09:02
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 3000 + 10;

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

int n, m;
bool G[maxn][maxn], in[maxn];

int main()
{
#ifdef CraZYali
	file("3524");
#endif
	n = read<int>();m = read<int>();
	int need = n / 3, cur = 0;
	REP(i, 1, n) in[i] = 1;
	while (m--)
	{
		int x = read<int>(), y = read<int>();
		G[x][y] = G[y][x] = 1;
	}
	REP(i, 1, n) if (in[i])
	{
		REP(j, i + 1, n) if (in[j] && !G[i][j]) {in[i] = in[j] = 0;break;}
		if (!in[i])
		{
			cur++;
			if (cur == need) break;
		}
	}
	REP(i, 1, n) if (in[i])
	{
		printf("%d ", i);
		if (!(--need)) break;
	}
	return 0;
}
