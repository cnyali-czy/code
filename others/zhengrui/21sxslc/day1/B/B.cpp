/*
	Problem:	B.cpp
	Time:		2020-12-27 11:32
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <iostream>
#include <cstdio>
#define int long long

using namespace std;
const int maxn = 1e5 + 10;

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

int n, k, h, a[maxn], ans = 1e18;

int cur[maxn];

vector <int> G[maxn];
vector <pair <int, int> > E[maxn];

void dfs(int x, int t, int res = 0)
{
	if (res >= ans) return;
	if (t == h)
	{
		ans = min(ans, res);
		return;
	}
	t++;
	if (k == 1 || t % k == 1)
	{
		REP(i, 1, n) cur[i] += a[i];
	}
	for (int tx : G[x])
	{
		vector <int> mem(n + 1);
		REP(i, 1, n) mem[i] = cur[i];
		for (auto e : E[tx])
			cur[e.first] += cur[e.second], cur[e.second] = 0;
		int kill = cur[tx];cur[tx] = 0;
		dfs(tx, t, res + kill);
		REP(i, 1, n) cur[i] = mem[i];
	}
}
int rt;
void dfs0(int x, int fa = 0)
{
	for (int y : G[x]) if (y ^ fa)
	{
		E[rt].emplace_back(x, y);
		dfs0(y, x);
	}
}
signed main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read<int>();k = read<int>();h = read<int>();
	REP(i, 1, n) a[i] = read<int>();
	REP(i, 2, n)
	{
		int x = read<int>(), y = read<int>();
		G[x].emplace_back(y);
		G[y].emplace_back(x);
	}
	REP(i, 1, n)
		dfs0(rt = i);
	REP(i, 1, n) G[i].emplace_back(i);
	dfs(1, 0);
	cout << ans << endl;
	return 0;
}
