>/*
	Problem:	5521.cpp
	Time:		2020-11-06 11:16
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e5 + 10;

vector <int> G[maxn];

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

int n, w[maxn], ans[maxn];
inline int cmp(int x, int y) {return ans[x] - w[x] > ans[y] - w[y];}
void dfs(int x)
{
	for (int y : G[x]) dfs(y);
	sort(G[x].begin(), G[x].end(), cmp);
	int ard = 0, mx = 0;
	for (int y : G[x])
		if (ard >= ans[y]) ard -= w[y];
		else
		{
			mx += ans[y] - ard;
			ard += ans[y] - ard;
			ard -= w[y];
		}
	ans[x] = mx + max(0, w[x] - ard);
}

int main()
{
#ifdef CraZYali
	file("5521");
#endif
	n = read<int>();
	REP(i, 2, n) G[read<int>()].emplace_back(i);
	REP(i, 1, n) w[i] = read<int>();
	dfs(1);
	REP(i, 1, n) printf("%d%c", ans[i], i == end_i ? '\n' : ' ');
	return 0;
}
