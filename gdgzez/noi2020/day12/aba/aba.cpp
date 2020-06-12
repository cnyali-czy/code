/*
	Problem:	aba.cpp
	Time:		2020-06-12 07:55
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 3000 + 10, maxk = 5000 + 10;

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

int n, k, L[maxn];
string ssr[maxn];
char tmp[maxk];

int main()
{
#ifdef CraZYali
	file("aba");
#endif
	n = read<int>();k = read<int>();
	REP(i, 1, k) ssr[i] = "z";
	REP(i, 1, n)
	{
		scanf("%s", tmp);
		string s = tmp;
		DEP(i, k, s.size()) chkmin(ssr[i], ssr[i - s.size()] + s);
	}
	cout << ssr[k] << endl;
	return 0;
}
