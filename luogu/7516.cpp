/*
	Problem:	7516.cpp
	Time:		2021-04-16 11:27
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <bitset>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e3 + 10, maxm = 2e5 + 10;

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

int n, m, u[maxm], v[maxm], ans[maxm];

bitset <maxn> G[maxn];
void floyd(int k)
{
	REP(i, 1, n) if (G[i][k])
		G[i] |= G[k];
}

int main()
{
#ifdef CraZYali
	file("7516");
#endif
	n = read<int>();m = read<int>();
	REP(i, 1, m) u[i] = read<int>(), v[i] = read<int>();
	ans[m + 1] = n;
	REP(i, 1, n) G[i][i] = 1;
	DEP(cur, m, 1)
	{
		G[u[cur]][v[cur]] = 1;
		floyd(u[cur]);floyd(v[cur]);
	}
	REP(i, 1, m + 1) printf("%d%c", ans[i], i == end_i ? '\n' : ' ' );
	return 0;
}
