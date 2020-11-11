/*
	Problem:	C.cpp
	Time:		2020-11-09 16:15
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
const int maxn = 2000 + 10;

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

int n, a[maxn], x[5];

int main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();
	REP(i, 0, 3) x[i] = read<int>();
	REP(i, 1, n) a[i] = read<int>();
	int ans = 0;
	REP(i, 1, n) REP(j, i + 1, n) REP(k, j + 1, n) REP(l, k + 1, n)
	{
		pair <int, int> b[] = {make_pair(i, 1), make_pair(j, 2), make_pair(k, 3), make_pair(l, 4)};
		sort(b, b + 4);
		bool flag = 1;
		REP(orz, 0, 3) if (b[orz].second ^ x[orz]) flag = 0;
		ans += flag;
	}
	cout << ans << endl;
	return 0;
}
