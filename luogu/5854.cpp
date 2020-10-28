/*
	Problem:	5854.cpp
	Time:		2020-10-28 08:40
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

using namespace std;
const int maxn = 1e7 + 10;

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
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, a[maxn], stk[maxn], top, cur, ls[maxn], rs[maxn];

void build()
{
	top = cur = 0;
	REP(i, 1, n)
	{
		cur = top;
		while (cur && a[stk[cur]] > a[i]) cur--;
		if (cur) rs[stk[cur]] = i;
		if (cur < top) ls[i] = stk[cur + 1];
		stk[top = (++cur)] = i;
	}
}

int main()
{
#ifdef CraZYali
	file("5854");
#endif
	n = read<int>();
	REP(i, 1, n) a[i] = read<int>();
	build();
	long long ansl = 0, ansr = 0;
	REP(i, 1, n)
	{
		ansl ^= (1ll * i * (ls[i] + 1));
		ansr ^= (1ll * i * (rs[i] + 1));
	}
	cout << ansl << ' ' << ansr << endl;
	return 0;
}
