/*
	Problem:	3801-new.cpp
	Time:		2020-11-15 19:37
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
#define i64 long long

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

int n, a[maxn];

int main()
{
#ifdef CraZYali
	file("3801-new");
#endif
	n = read<int>();
	REP(i, 1, n) a[i] = read<int>();
	i64 ans_xor = 0, ans_and = 0, ans_or = 0, tot = 1ll * n * n;
	REP(j, 0, 30)
	{
		i64 res_xor = 0, res_and = 0, res_or = 0;
		int c[] = {1, 0}, s = 0, len = 0, lst = 0;
		REP(i, 1, n)
		{
			bool f = (a[i] >> j & 1);
			s ^= f;
			res_xor += c[!s];
			c[s]++;
			if (f & 1)
			{
				len++;
				res_and += len;
				lst = i;
				res_or += i;
			}
			else
			{
				len = 0;
				res_or += lst;
			}
		}
		ans_xor += (res_xor << j);
		ans_and += (res_and << j);
		ans_or += (res_or << j);
	}
	ans_xor *= 2;	REP(i, 1, n) ans_xor -= a[i];
	ans_and *= 2;	REP(i, 1, n) ans_and -= a[i];
	ans_or *= 2;	REP(i, 1, n) ans_or -= a[i];
	printf("%.3lf %.3lf %.3lf\n", ans_xor * 1. / tot, ans_and * 1. / tot, ans_or * 1. / tot);
	return 0;
}
