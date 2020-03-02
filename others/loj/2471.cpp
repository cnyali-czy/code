/*
	Problem:	2471.cpp
	Time:		2020-03-02 17:43
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <unordered_map>
#include <iostream>
#include <cstdio>
#define ui64 unsigned long long
using namespace std;
const int maxn = 10 + 5, maxm = 10 + 5, inf = 1e9;
const ui64 base = 1e9 + 9;

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

int n, m, a[maxn][maxm], b[maxn][maxm];
int sta[maxn];
inline ui64 Hash()
{
	ui64 res = 0;
	REP(i, 1, n) res = res * base + sta[i];
	return res;
}
unordered_map <ui64, int> Mem;
int dfs(ui64 status, int ard)
{
	if (ard == n * m) return 0;
	if (Mem[status]) return Mem[status];
	int &res = Mem[status];
	ard++;
	if (ard & 1) // A's round
	{
		res = -inf;
		REP(i, 1, n) if (sta[i] < m && sta[i - 1] > sta[i])
		{
			sta[i]++;
			chkmax(res, dfs(Hash(), ard) + a[i][sta[i]]);
			sta[i]--;
		}
	}
	else
	{
		res = inf;
		REP(i, 1, n) if (sta[i] < m && sta[i - 1] > sta[i])
		{
			sta[i]++;
			chkmin(res, dfs(Hash(), ard) - b[i][sta[i]]);
			sta[i]--;
		}
	}
	return res;
}

int main()
{
#ifdef CraZYali
	file("2471");
#endif
	n = read<int>();m = read<int>();
	REP(i, 1, n) REP(j, 1, m) a[i][j] = read<int>();
	REP(i, 1, n) REP(j, 1, m) b[i][j] = read<int>();
	sta[0] = inf;sta[1] = 1;
	cout << dfs(Hash(), 1) + a[1][1];
	return 0;
}
