/*
	Problem:	A.cpp
	Time:		2020-04-03 22:38
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 500 + 5;

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

int n, x, a[maxn], ans;
bool vis[maxn];
int main()
{
#ifdef CraZYali
	file("A");
#endif
	register int T = read<int>();
	while (T--)
	{
		memset(vis, 0, sizeof vis);
		n = read<int>();x = read<int>();
		REP(i, 1, n) a[i] = read<int>();
//		sort(a + 1, a + 1 + n);n = unique(a + 1, a + 1 + n) - a - 1;
		REP(i, 1, n) vis[a[i]] = 1;
		REP(i, 1, 114514)
			if (vis[i]) continue;
			else
			{
				if (!x)
				{
					cout << i - 1 << endl;
					break;
				}
				x--;
			}
	}
	return 0;
}
