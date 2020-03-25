/*
	Problem:	C.cpp
	Time:		2020-03-23 23:08
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
#include <vector>
#include <cstdio>

using namespace std;
const int maxn = 200 + 5, maxm = 200 + 5, maxk = 200 + 5, maxM = maxm * maxm;

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

int n, m, k;

int main()
{
#ifdef CraZYali
	file("C");
#endif
	cin >> n >> m >> k;
	cout << 2 * m * (n - 1) + m - 1 + m - 1 << endl;
	REP(i, 1, m + m)
	{
		char c = (i & 1) ? 'U' : 'D';
		REP(i, 1, n - 1) putchar(c);
		if (i != m && i != m + m) putchar(i <= m ? 'R' : 'L');
	}
	return 0;
}
