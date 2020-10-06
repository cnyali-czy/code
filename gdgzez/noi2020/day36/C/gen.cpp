/*
	Problem:	gen.cpp
	Time:		2020-07-31 11:09
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <random>
#include <cstdlib>
#include <ctime>
#include <algorithm>
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
const int N = 1e9;
inline int Rand() {return rand() % N + 1;}
int main()
{
	freopen("C.in", "w", stdout);
	int q = 10000, w = 1, n = 0;
	cout << q << ' ' << w << endl;
	srand(time(0));
	hh = mt19937(rand());
	while (q--)
	{
		int opt = rand() % 2 + 1;
		while (opt == 2 && !n) opt = rand() % 2 + 1;
		if (opt == 1) printf("1 %d %d\n", Rand(), Rand()),n++;
		else printf("2 %d\n", Rand() % n + 1);
	}
	return 0;
}
