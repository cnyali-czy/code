/*
	Problem:	K.cpp
	Time:		2020-07-27 12:01
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <bitset>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 5e6 + 10;

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

int n, k, a[maxn];
bool vis[maxn];

int main()
{
#ifdef CraZYali
	file("K");
#endif
	REP(Case, 1, read<int>())
	{
		n = read<int>();k = read<int>();
		REP(i, 1, n) a[i] = read<int>();
		if (k > n || n % k != 0)
		{
			puts("NO");
			continue;
		}
		bool flag = 1;
		for (int l = 1, r = k; r <= n; l += k, r += k)
		{
			REP(i, 1, k) vis[i] = 0;
			REP(i, l, r)
			{
				if (!(1 <= a[i] && a[i] <= k)) {flag = 0;goto End;}
				if (vis[a[i]]) {flag = 0;goto End;}
				vis[a[i]] = 1;
			}
		}
End:;
		puts(flag ? "YES" : "NO");
	}
	return 0;
}
