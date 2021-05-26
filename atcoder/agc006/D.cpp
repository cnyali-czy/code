/*
	Problem:	2165.cpp
	Time:		2021-04-22 15:19
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
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, a[maxn << 1];
bool judge(int val)
{
	static bool b[maxn << 1];
	REP(i, 1, n + n - 1) b[i] = (val <= a[i]);
	REP(i, 0, n - 1)
	{
		if (b[n + i] == b[n + i + 1]) return b[n + i];
		if (b[n - i] == b[n - i - 1]) return b[n - i];
	}
	return b[1];
}

int main()
{
#ifdef CraZYali
	file("2165");
#endif
	n = read<int>();
	REP(i, 1, n + n - 1) a[i] = read<int>();
	int l = 1, r = n + n - 1, ans = -1;
	while (l <= r)
	{
		int mid = l + r >> 1;
		if (judge(mid))
		{
			ans = mid;
			l = mid + 1;
		}
		else r = mid - 1;
	}
	cout << ans << endl;
	return 0;
}
