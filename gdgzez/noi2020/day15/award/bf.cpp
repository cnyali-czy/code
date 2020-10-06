/*
	Problem:	award.cpp
	Time:		2020-06-16 10:25
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
#define i64 long long
#define int i64

using namespace std;
const int maxn = 2e5 + 10;
const i64 inf = 1e18;

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

int n, a[maxn];
i64 dd[maxn];

i64 dis(i64 i, i64 j)
{
	if (i > j) swap(i, j);
	return dd[j] - dd[i];
}

bool vis[maxn];
i64 ans = inf;
void calc(i64 res)
{
	REP(i, 1, n) if (!vis[i]) return;
	chkmin(ans, res);
}
void dfs(int x, i64 y = 0)
{
	if (y >= ans) return;
	if (x == n) calc(y);
	else
	{
		x++;
		dfs(x, y);
		REP(i, 1, n) if (!vis[i])
		{
			vis[i] = 1;
			dfs(x, y + a[x] + dis(x, i));
			REP(j, i + 1, n) if (!vis[j])
			{
				vis[j] = 1;
				dfs(x, y + a[x] + a[x] + dis(x, i) + dis(x, j));
				vis[j] = 0;
			}
			vis[i] = 0;
		}
	}
}

signed main()
{
	freopen("award.in", "r", stdin);
	freopen("bf.out", "w", stdout);
	n = read<int>();
	REP(i, 2, n) dd[i] = read<int>() + dd[i - 1];
	REP(i, 1, n) a[i] = read<int>();
	dfs(0);
	cout << ans << endl;
	return 0;
}
