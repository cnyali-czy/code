/*
	Problem:	B.cpp
	Time:		2021-06-19 12:30
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
#define int long long

using namespace std;
const int maxk = 26, maxl = maxk * (maxk + 1) / 2 + 10;

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int k, n, l;
int f[maxl][maxk][maxk];

signed main()
{
#ifdef CraZYali
	file("B");
#endif
	cin >> k >> n;
	l = k * (k + 1) / 2;
	REP(i, 1, l)
	{
	}
	puts("-1");
	return 0;
}
