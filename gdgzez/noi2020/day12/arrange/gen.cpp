/*
	Problem:	gen.cpp
	Time:		2020-06-12 08:51
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <ctime>
#include <iostream>
#include <cstdio>

using namespace std;


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
inline long long Rand(){return 1ll*rand()*rand();}
int main()
{
	freopen("arrange.in", "w", stdout);
	srand(time(0));
	int n = 2e3, k = rand() % n + 1;
	cout << n << ' ' << k << endl;
	const int N = 1e6;
	REP(i, 1, n) printf("%d%c", Rand() % N + 1, i == n ? '\n' : ' ');
	REP(i,2,n)printf("%d %d\n",i,rand()%(i-1)+1);
	return 0;
}
