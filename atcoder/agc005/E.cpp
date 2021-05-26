/*
	Problem:	2063.cpp
	Time:		2021-05-05 20:51
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

using namespace std;
const int maxn = 200000 + 10;

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

int n, sa, sb;
vector <int> A[maxn], B[maxn];

int dep[maxn], fa[maxn];
void dfs_b(int x)
{
	for (int y : B[x]) if (y ^ fa[x])
	{
		fa[y] = x;
		dep[y] = dep[x] + 1;
		dfs_b(y);
	}
}
int u[maxn], v[maxn];
inline bool judge(int x, int y)
{
	if (dep[x] < dep[y]) swap(x, y);
	if (dep[x] == dep[y]) return fa[x] == fa[y];
	else if (dep[x] == dep[y] + 1) return fa[x] == y;
	else if (dep[x] == dep[y] + 2) return fa[fa[x]] == y;
	return 0;
}
bool ok[maxn];
int mx;
void dfs(int x, int f, int d)
{
	if (d >= dep[x]) return;
	if (ok[x])
	{
		puts("-1");
		exit(0);
	}
	mx = max(mx, dep[x]);
	for (int y : A[x]) if (y ^ f)
		dfs(y, x, d + 1);
}
int main()
{
#ifdef CraZYali
	file("2063");
#endif
	n = read<int>();sa = read<int>();sb = read<int>();
	REP(i, 2, n)
	{
		int x = read<int>(), y = read<int>();
		A[x].emplace_back(y);
		A[y].emplace_back(x);		
		u[i] = x;v[i] = y;
	}
	REP(i, 2, n)
	{
		int x = read<int>(), y = read<int>();
		B[x].emplace_back(y);
		B[y].emplace_back(x);		
	}
	dfs_b(sb);
	REP(i, 2, n) if (!judge(u[i], v[i])) ok[u[i]] = ok[v[i]] = 1;
	dfs(sa, 0, 0);
	cout << mx * 2 << endl;
	return 0;
}
