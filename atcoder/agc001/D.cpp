/*
	Problem:	1982.cpp
	Time:		2021-04-19 15:34
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
 
int n, a[maxn], b[maxn], m;
 
int main()
{
#ifdef CraZYali
	file("1982");
#endif
	n = read<int>();m = read<int>();
	int o1 = 0, o2 = 0;
	REP(i, 1, m)
	{
		a[i] = read<int>();
		if (a[i] & 1)
			if (!o1) o1 = a[i];
			else if (!o2) o2 = a[i];
			else
			{
				puts("Impossible");
				return 0;
			}
	}
	if (n == 1)
	{
		puts("1\n1\n1");
		return 0;
	}
	if (m == 1)
	{
		printf("%d\n2\n1 %d\n", n, n - 1);
		return 0;
	}

	int k = 0;
	if (o1) b[++k] = o1;
	REP(i, 1, m) if(!(a[i] & 1)) b[++k] = a[i];
	if (o2) b[++k] = o2;
	REP(i, 1, m) printf("%d%c", b[i], i == end_i ? '\n' : ' ' );
	b[1]++;b[m]--;
	while (!b[m]) m--;
	printf("%d\n", m);
	REP(i, 1, m) printf("%d%c", b[i], i == end_i ? '\n' : ' ' );
 
	return 0;
}
