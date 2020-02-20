/*
	Problem:	auction.cpp
	Time:		2020-02-20 10:15
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <bitset>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e5 + 10;

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

int n, q;
char s[maxn];
bitset <maxn> f, g;

int main()
{
#ifdef CraZYali
	file("auction");
#endif
	n = read<int>();q = read<int>();
	scanf("%s", s + 1);
	REP(i, 1, n) g[i] = 1;
	DEP(i, n, 1)
		if (s[i] == '1') f = (f << 1) ^ g;
		else f = (f << 1) & f;
	while (q--) printf("%d\n", f.test(read<int>()));
	return 0;
}
