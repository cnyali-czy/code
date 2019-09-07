/*
 * File Name:	3801.cpp
 * Author	:	CraZYali
 * Year		:	2019.09.07 23:33
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e5 + 10;

template <typename T> inline T read()
{
	T ans(0), flag(1);
	char c(getchar());
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

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout);

int n, a[maxn];

int main()
{
#ifdef CraZYali
	file("3801");
#endif
	cin >> n;
	REP(i, 1, n) a[i] = read<int>();
	double Ans1(0), Ans2(0), Ans3(0);
	REP(k, 0, 29)
	{
		int last[2]{0}, c1(0), c2(0), bin(1 << k);
		REP(i, 1, n)
			if (a[i] & bin)
			{
				Ans1 += 1. * bin / n / n + 2. * bin / n / n * c1;
				Ans2 += 1. * bin / n / n + 2. * bin / n / n * (i - 1 - last[0]);
				Ans3 += 1. * bin / n / n + 2. * bin / n / n * (i - 1);
				last[1] = i;
				c1++, swap(c1, c2);
			}
			else
			{
				Ans1 += bin * 2.0 / n / n * c2;
				Ans3 += bin * 2.0 / n / n * last[1];
				last[0] = i;
				c1++;
			}
	}
	printf("%.3lf %.3lf %.3lf\n", Ans1, Ans2, Ans3);

	return 0;
}
