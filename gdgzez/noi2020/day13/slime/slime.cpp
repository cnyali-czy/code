/*
	Problem:	slime.cpp
	Time:		2020-06-13 11:33
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
const int maxn = 400 + 5;

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

int ans, n, m;
vector <int> G[maxn];
int pick[maxn];
bool vis[maxn], shit[maxn], good[maxn];

void Dfs(int x)
{
	shit[x] = 1;
	for (int y : G[x]) if (!shit[y] && good[y]) Dfs(y);
}
bool judge(int l, int r)
{
	REP(i, 1, n) shit[i] = good[i] = 0;
	REP(i, l, r) good[pick[i]] = 1;
	Dfs(pick[l]);
	REP(i, l + 1, r) if (!shit[pick[i]]) return 0;
	return 1;
}

int main()
{
#ifdef CraZYali
	file("slime");
#endif
	n = read<int>();m = read<int>();
	REP(i, 2, n)
	{
		int x(read<int>()), y(read<int>());
		G[x].emplace_back(y);G[y].emplace_back(x);
	}
	REP(i, 1, n) pick[i] = i;
	do
	{
		bool flag = 1;
		REP(i, 1, n - m + 1)
			if (!judge(i, i + m - 1)) {flag = 0;break;}
		if (flag)
		{
			REP(i, 1, n) printf("%d%c", pick[i], i == n ? '\n' : ' ');
		}
		ans += flag;
	}while (next_permutation(pick + 1, pick + 1 + n));
	cout << ans << endl;
	return 0;
}
