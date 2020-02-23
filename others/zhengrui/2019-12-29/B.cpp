/*
	Problem:	B.cpp
	Time:		2020-02-22 18:08
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <map>
#include <unordered_map>
#include <iostream>
#include <cstdio>

using namespace std;

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

namespace run
{
#define int long long
	unordered_map <int,int> f[64][2][64];
	int dfs(int n, int m, int val, int pre)
	{
		if (f[n][val][pre].count(m)) return f[n][val][pre][m];
		int u(0);
		if (n <= 2)
		{
			REP(i, 0, m)
			{
				int v = i + val;
				REP(j, 0, n - 1) if (i & (1 << j)) v += 1 << n - j - 1;
				u += __builtin_popcount(v) + (v& (1 << n) ? 0 : pre);
			}
			return f[n][val][pre][m] = u;
		}
		int mid = 1ll << n - 1, p = min(m, mid - 1);
		u = dfs(n - 2, p >> 1, 0, 0) + (val + pre) * (p + 2 >> 1);
		if (p) u += dfs(n - 2, p - 1 >> 1, val, pre + 1) + (val ? 0 : p + 1 >> 1);
		if (mid <= m)
		{
			u += dfs(n - 2, m - mid >> 1, val, pre + 1) + (val ? 0 : m - mid + 2 >> 1);
			if (m ^ mid) 
				u += dfs(n - 2, m - mid - 1 >> 1, 1, 0) + (val + 1) * (m - mid + 1 >> 1);
		}
		return f[n][val][pre][m] = u;
	}
	int n, ans;
	int main()
	{
		n = read<int>();
		REP(i, 0, 60)
		{
			if (n < 1ll << i) break;
			ans += dfs(i + 1, min((1ll << i + 1) - 1, n), 0, 0) - dfs(i + 1, (1ll << i) - 1, 0, 0);
		}
		cout << ans << endl;
		return 0;
	}

}

signed main()
{
#ifdef CraZYali
	file("B");
#endif
	return run::main();
}
