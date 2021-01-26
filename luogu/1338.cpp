/*
	Problem:	1338.cpp
	Time:		2021-01-25 17:20
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
const int maxn = 5e4 + 10;

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

int n, k, a[maxn];
int c2(int x) {return x * (x - 1ll) / 2;}

int main()
{
#ifdef CraZYali
	file("1338");
#endif
	n = read<int>();k = read<int>();
	int l = 1, r = n;
	REP(i, 1, n)
	{
		if (c2(r - l) >= k) a[l++] = i;
		else
		{
			k -= r - l;
			a[r--] = i;
		}
	}
	REP(i, 1, n) printf("%d%c", a[i], i == end_i ? '\n' : ' ');
	return 0;
}
