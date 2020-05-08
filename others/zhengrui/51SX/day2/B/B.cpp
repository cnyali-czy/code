/*
	Problem:	B.cpp
	Time:		2020-05-02 10:02
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
const int maxn = 20, MOD = 1e9 + 7, maxm = maxn * maxn;

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

int n, m, u[maxm], v[maxm], R[maxn], w[maxn];

namespace smallR
{
	bool judge()
	{
		return 1;
		REP(i, 1, n) if (R[i] > 2) return 0;
		return 1;
	}
	int ans = 0;
	bool vis[114];
	void calc()
	{
		REP(i, 1, m) if (w[u[i]] == w[v[i]]) return;
		REP(i, 1, n) vis[w[i]] = 0;
		REP(i, 1, n) if (!vis[w[i]]) vis[w[i]] = 1, ans++;
	}
	void dfs(int x)
	{
		if (x == n) calc();
		else
		{
			x++;
			REP(i, 0, R[x]) w[x] = i, dfs(x);
		}
	}
	void work()
	{
		dfs(0);
		cout << ans << endl;
	}
}

int main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read<int>();m = read<int>();
	REP(i, 1, n) R[i] = read<int>();
	REP(i, 1, m) u[i] = read<int>(), v[i] = read<int>();
	if (n == 1)
	{
		cout << R[1] + 1 << endl;
		return 0;
	}
	else if (smallR::judge()) smallR::work();
	return 0;
}
