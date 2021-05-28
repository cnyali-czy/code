/*
	Problem:	D.cpp
	Time:		2021-05-27 21:34
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
const int maxn = 2e5 + 10;

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

int n, k;
char str[maxn];

int main()
{
#ifdef CraZYali
	file("D");
#endif
	n = read<int>();k = read<int>();
	scanf("%s", str + 1);
	if (k > 2 * n) k = 2 * n + ((k - 2 * n) & 1);
	int A = 'A', s = 1;
	while (k--)
	{
		if (str[s] == A) str[s] = 'A' + 'B' - A;
		else
		{
			A = 'A' + 'B' - A;
			s = (s == n ? 1 : s + 1);
		}
	}
	REP(i, s, n)		putchar("AB"[str[i] != A]);
	REP(i, 1, s - 1)	putchar("AB"[str[i] != A]);
	return 0;
}
