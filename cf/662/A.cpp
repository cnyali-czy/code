/*
	Problem:	A.cpp
	Time:		2020-02-14 09:51
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

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

int n, p[100], cnt, need;

void insert(int x)
{
	DEP(i, 62, 0) if (x & (1ll << i))
		if (!p[i]) {p[i] = x;return void(++cnt);}
		else x ^= p[i];
}

signed main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();
	REP(i, 1, n)
	{
		int a = read<int>();
		need ^= a;
		insert(a ^ read<int>());
	}
	DEP(i, 62, 0) if (need & (1ll << i)) need ^= p[i];
	if (need) puts("1/1");
	else printf("%lld/%lld\n", (1ll << cnt) - 1, 1ll << cnt);
	return 0;
}
