/*
	Problem:	B.cpp
	Time:		2020-04-03 22:45
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
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, a[maxn];
bool ok[2][maxn], vis[maxn];

int main()
{
#ifdef CraZYali
	file("B");
#endif
	register int T = read<int>();
	while (T--)
	{
		n = read<int>();
		REP(i, 1, n) a[i] = read<int>(), ok[0][i] = ok[1][i] = 0;
		REP(i, 1, n) vis[i] = 0;
		int Max = 0, cnt = 0;
		REP(i, 1, n)
		{
			chkmax(Max, a[i]);
			if (vis[a[i]]) break;
			vis[a[i]] = 1;
			cnt++;
			ok[0][i] = (cnt == Max);
		}
		REP(i, 1, n) vis[i] = 0;
		Max = cnt = 0;
		DEP(i, n, 1)
		{
			chkmax(Max, a[i]);
			if (vis[a[i]]) break;
			vis[a[i]] = 1;
			cnt++;
			ok[1][i] = (cnt == Max);
		}
		int ans = 0;
		REP(i, 2, n) ans += (ok[0][i-1] && ok[1][i]);
		cout << ans << endl;
		REP(i, 2, n) if (ok[0][i-1] && ok[1][i]) printf("%d %d\n", i - 1, n - i + 1);
	}
	return 0;
}
