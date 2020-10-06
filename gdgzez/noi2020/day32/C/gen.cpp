/*
	Problem:	gen.cpp
	Time:		2020-07-23 09:23
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

int main()
{
	freopen("C.in", "w", stdout);
	int Case = 10;
	cout << Case << endl;
	srand(time(0));
	while(Case--)
	{
		int n =1000,k=rand()%n+1;
		cout<<n<<' '<<k<<endl;
		const int N =1000;
		REP(i,1,n)printf("%d%c",(rand()&1?-1:1)*rand()%N,i==end_i?'\n':' ');
	}
	return 0;
}
