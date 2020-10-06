/*
	Problem:	gen.cpp
	Time:		2020-06-16 09:07
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
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
vector <pair <int, int> > qaq;
int main()
{
	freopen("sell.in", "w", stdout);
	int n = 1000, T = n + n * (n + 1) / 2;
	REP(i,1,n)REP(j,0,min(i, 20))
	{
	qaq.emplace_back(i,j);
	}
	cout<<qaq.size()<<endl;
	for(auto i:qaq)cout<<i.first<<' '<<i.second<<endl;
	return 0;
}
