#define REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;
const int maxn = 2e5 + 10;
int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

template <typename T> T read()
{
	T ans(0), flag(1);
	char c(getchar());
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

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

int m, n, k;
inline bool chkmin(int &x, int y)
{
	if (x > y) {x = y;return 1;}
	return 0;
}
int dp[maxn][2];
void dfs(int x, int fa = 0)
{
	bool flag = 0;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa) flag = 1;
	if (!flag) return;
	dp[x][0] = dp[x][1] = 1e9;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
	{
		int y = to[i];
		dfs(y, x);
		chkmin(dp[x][0], min(dp[y][0] + 1, dp[y][1]));
		chkmin(dp[x][1], min(dp[y][0] + 1, dp[y][1]) + 1);
	}
}

int main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();
	REP(i, 2, n)
	{
		int x(read<int>()), y(read<int>());
		add(x, y);add(y, x);
	}
	dfs(1);
	cout << min(dp[1][0], dp[1][1]) << endl;
	return 0;
}
