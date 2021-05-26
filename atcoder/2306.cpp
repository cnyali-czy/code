/*
	Problem:	2306.cpp
	Time:		2021-05-26 09:25
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <queue>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 2000 + 10;

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

int n, a[maxn], in[maxn];
vector <int> G[maxn], D[maxn];
bool vis[maxn];
void dfs(int x)
{
	vis[x] = 1;
	for (int y : G[x]) if (!vis[y])
	{
		D[x].emplace_back(y);
		in[y]++;
		dfs(y);
	}
}

int main()
{
#ifdef CraZYali
	file("2306");
#endif
	n = read<int>();
	REP(i, 1, n) a[i] = read<int>();sort(a + 1, a + 1 + n);
	REP(i, 1, n) REP(j, i + 1, n) if (__gcd(a[i], a[j]) ^ 1)
	{
		G[i].emplace_back(j);
		G[j].emplace_back(i);
	}
	REP(i, 1, n) sort(G[i].begin(), G[i].end());
	REP(i, 1, n) if (!vis[i]) dfs(i);
	
	priority_queue <int> que;
	REP(i, 1, n) if (!in[i]) que.emplace(i);
	while (que.size())
	{
		int x = que.top();que.pop();
		printf("%d ", a[x]);
		for (int y : D[x]) if (!(--in[y])) que.emplace(y);
	}
	return 0;
}
