/*
 * File Name:	B.cpp
 * Author	:	CraZYali
 * Year		:	2019.10.19 14:31
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 300 + 10;
const long long MOD = 998244353;

template <typename T> inline T read()
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

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout);

int n, ans;

bool a[maxn][maxn];
int flag1[maxn], FLAG1[maxn], flg0, flg1;

void dfs(int x, int y)
{
	if (x == n && y == n)
	{
		bool flag = (0 < flg0 && flg0 < n && 0 < flg1 && flg1 < n);
		ans += flag;/*
		if (flag)
		{
			REP(i, 1, n)
				REP(j, 1, n) printf("%d%c", a[i][j], j == end_j ? '\n' : ' ');
			REP(i, 1, n) printf("%d%c", flag1[i], i == n ? '\n' : ' ');
			REP(i, 1, n) printf("%d%c", FLAG1[i], i == n ? '\n' : ' ');
		cout << flg0 << ' ' << flg1 << endl;
			puts("-----");
			ans++;
		}*/
	}
	else
	{
		if (y == n) x++, y = 1;
		else y++;
		a[x][y] = 1;
		flag1[x]++;
		FLAG1[y]++;
		if (x == y) flg0++;
		if (x + y == n + 1) flg1++;
		if (x < n && y < n) dfs(x, y);
		else if (y < n && x == n && (0 < FLAG1[y] && FLAG1[y] < n)) dfs(x, y);
		else if (x < n && y == n && (0 < flag1[x] && flag1[x] < n)) dfs(x, y);
		else if (x == n && y == n && (0 < flag1[x] && flag1[x] < n && 0 < FLAG1[y] && FLAG1[y] < n)) dfs(x, y);
		flag1[x]--;
		FLAG1[y]--;
		if (x == y) flg0--;
		if (x + y == n + 1) flg1--;

		a[x][y] = 0;

		if (x < n && y < n) dfs(x, y);
		else if (y < n && x == n && (0 < FLAG1[y] && FLAG1[y] < n)) dfs(x, y);
		else if (x < n && y == n && (0 < flag1[x] && flag1[x] < n)) dfs(x, y);
		else if (x == n && y == n && (0 < flag1[x] && flag1[x] < n && 0 < FLAG1[y] && FLAG1[y] < n)) dfs(x, y);
	}
}

int main()
{
#ifdef CraZYali
	file("B");
#endif
	for (n = 6; n <= 10; n++)
	{
		ans = 0;
		a[1][1] = 1;
		dfs(1, 1);
		cout << 2ll * ans % MOD << endl;
		cerr << 2ll * ans % MOD << endl;
	}
	return 0;
}
