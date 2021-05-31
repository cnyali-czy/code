/*
	Problem:	631.cpp
	Time:		2021-05-29 19:17
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

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int N, M, S;
namespace Case1
{
	void work()
	{
		cout << N << endl;
		REP(i, 1, N) printf("%d %d\n", i, i);
		cout << M - 1 << endl;
		REP(i, 1, M - 1) printf("0 %d %d\n", i, i + 1);
	}
}
namespace Case2
{
	void work()
	{
		int n = 315 * 315 + 300;
		cout << n << endl;
		REP(i, 1, 315) REP(j, 1, 315) printf("%d %d\n", 2 * i - 1, j);
		REP(i, 1, 300) printf("%d 0\n", 2 * i);
		int m = 300;
		cout << m << endl;
		REP(i, 1, m) printf("0 %d %d\n", 2 * i - 1, 2 * i);
	}
}
int main()
{
#ifdef CraZYali
	file("631");
#endif
	cin >> N >> M >> S;
	if (N == 1000) Case1 :: work();
	else if (M == 300) Case2 :: work();
	return 0;
}
