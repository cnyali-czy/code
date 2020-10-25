/*
	Problem:	B.cpp
	Time:		2020-10-25 19:09
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 500 + 5, maxm = 500 + 5;

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

int n, m;
int r[maxn][maxm], c[maxm][maxn];
int pos[maxn * maxm];
int id[maxn];

inline bool cmp (int a, int b)
{
	REP(j, 1, m) if (pos[r[a][j]] > pos[r[b][j]]) return 0;
	return 1;
}

int main()
{
#ifdef CraZYali
	file("B");
#endif
	register int T = read<int>();
	while (T--)
	{
		n = read<int>();m = read<int>();
		REP(i, 1, n) REP(j, 1, m) r[i][j] = read<int>();
		REP(j, 1, m) REP(i, 1, n)
		{
			c[j][i] = read<int>();
			pos[c[j][i]] = i;
		}
		/*
		   REP(i, 1, n) REP(j, i + 1, n)
		   REP(k, 1, m) if (pos[r[i][k]] > pos[r[j][k]])
		   {
		   swap(r[i], r[j]);
		   break;
		   }
		   */
		REP(i, 1, n) id[i] = i;
		sort(id + 1, id + 1 + n, cmp);
		REP(i, 1, n) REP(j, 1, m) printf("%d%c", r[id[i]][j], j == end_j ? '\n' : ' ');
	}
	return 0;
}
