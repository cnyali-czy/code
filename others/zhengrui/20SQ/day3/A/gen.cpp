/*
	Problem:	gen.cpp
	Time:		2020-08-09 21:01
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include<random>
#include<ctime>
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

mt19937 hh;
int Rand()
{
	auto qaq = hh();
	if(qaq<0)qaq=-qaq;
	return qaq%INT_MAX;
}

int main()
{
	freopen("A.in","w",stdout);
	int n = 2e5;
	cout<<n<<endl;
	hh=mt19937(time(0));
	REP(i, 1,n)printf("%d%c",123123144+(rand()%5-8),i==end_i?'\n':' ');// Rand()%1000000000+1,i==end_i?'\n':' ');
	return 0;
}
