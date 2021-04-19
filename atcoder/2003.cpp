/*
	Problem:	2003.cpp
	Time:		2021-04-18 08:34
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

int n, a[maxn];

int main()
{
#ifdef CraZYali
	file("2003");
#endif
	n = read<int>();REP(i, 1, n) a[i] = read<int>();
	static int pos[maxn];REP(i, 1, n) pos[i] = i ;
	sort(pos + 1, pos + 1 + n, [&](int x, int y) {return a[x] < a[y];});
	int ans = 0;
	REP(i, 1, n) if (i + pos[i] & 1) ans++;
	cout << ans / 2 << '\n';
	return 0;
}
