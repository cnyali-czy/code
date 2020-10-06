/*
	Problem:	gen.cpp
	Time:		2020-06-16 10:51
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
#define int long long
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

int Rand(){return 1ll*rand()*rand();}
signed main()
{
	freopen("award.in", "w", stdout);
	int n = 500;
	cout << n << endl;
	srand(time(0));
	const int N = 1e9;
	REP(i,2,n)printf("%lld%c",Rand()%N+1,i==end_i?'\n':' ');
	REP(i,1,n)printf("%lld%c",Rand()%N+1,i==end_i?'\n':' ');
	return 0;
}
