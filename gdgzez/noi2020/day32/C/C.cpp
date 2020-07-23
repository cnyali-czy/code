/*
	Problem:	C.cpp
	Time:		2020-07-23 09:18
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
#define int long long
using namespace std;
const int maxn = 1e3 + 10;

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

int n, k, s[maxn];
bool vis[maxn][maxn], res[maxn][maxn];

bool dfs(int l, int r)
{
	if (l < 1 || r > n || s[l] < s[r]) return 0;
	if (l == 1 && r == n) return 1;
	if (vis[l][r]) return res[l][r];
	vis[l][r] = 1;
	return res[l][r] = dfs(l - 1, r) | dfs(l, r + 1);
}

signed main()
{
#ifdef CraZYali
	file("C");
#endif
	register int T = read<int>();
	while (T--)
	{
		n = read<int>();k = read<int>();
		REP(i, 1, n) s[i] = s[i - 1] + read<int>();
		REP(i, 1, n) REP(j, i, n) vis[i][j] = res[i][j] = 0;
		puts(dfs(k, k) ? "Yes" : "No");
	}
	return 0;
}
