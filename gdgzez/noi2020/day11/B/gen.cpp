/*
	Problem:	gen.cpp
	Time:		2020-06-11 08:24
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
#define i64 long long
inline i64 Rand() {return 1ll * rand() * rand();}
int main()
{
	freopen("B.in", "w", stdout);
	int n = 3000, m = 3000, K = n, N = 1e6;
	cout <<n << '\n';
	srand(time(0));
	REP(i,1,n)printf("%d%c",Rand() % N + 1,i==n?'\n':' ');
	cout<<m<<endl;
	int ccc = rand() % m + 1;
	REP(i, 1, m) if (i ^ ccc)printf("%d\n",Rand()%K+1);
	else printf("%d\n", n);
	return 0;
}
