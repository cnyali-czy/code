/*
	Problem:	gen.cpp
	Time:		2020-07-27 09:29
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
#include <random>
int G[3030][3030];
int main()
{
	freopen("recover.in", "w", stdout);
	srand(time(0));
	mt19937 hh(rand());
	int n = rand() % 2000 + 1, m = hh()%(1ll*n*(n-1)/2), k=2000/n;
	cout<<n<<' ' <<m<<' ' <<k<<endl;
	while(m--)
	{
		int x(rand()%n+1),y(rand()%n+1);
		if(x==y||G[x][y]){m++;continue;}
		G[x][y]=G[y][x]=1;
		printf("%d %d\n",x,y);
	}
	return 0;
}
