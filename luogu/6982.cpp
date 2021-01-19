/*
	Problem:	6982.cpp
	Time:		2021-01-18 22:14
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1000 + 10;

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

int n, a[maxn], real[maxn];
int ask()
{
#ifdef CraZYali
	int k = 0;
	REP(i, 1, n) k += (real[i] == a[i]);
	if (k == n || k == n / 2) return k;
	return 0;
#endif
	REP(i, 1, n) putchar(48 + a[i]);cout<<endl;
	return read<int>();
}
int main()
{
#ifdef CraZYali
	file("6982");
#endif
	n = read<int>();
#ifdef CraZYali
	REP(i, 1, n) real[i] = rand() & 1;
#endif
	while (1)
	{
		REP(i, 1, n) a[i] = rand() & 1;
		int res = ask();
		if (res == n) return 0;
		else if (res == n / 2) break;
	}
	static bool qaq[maxn];
	a[1] ^= 1;
	REP(i, 2, n)
	{
		a[i] ^= 1;
		int res = ask();
		if (res == n) return 0;
		qaq[i] = (res == n / 2);
		a[i] ^= 1;
	}
	a[1] ^= 1;
	REP(i, 2, n) if (qaq[i]) a[i] ^= 1;
	if (ask() == n) return 0;
	REP(i, 1, n) a[i] ^= 1;
	ask();
	return 0;
}
