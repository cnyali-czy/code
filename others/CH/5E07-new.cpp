/*
 * File Name:	5E07-new.cpp
 * Author	:	CraZYali
 * Year		:	2019.09.21 23:04
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <iostream>
#include <cstdio>
#define int long long
using namespace std;

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

const int M = 100000, maxm = M + 10;

int dp[maxm], a[10];

int num[666233], tot;

void split(int x, int id)
{
	int temp(0);
	REP(i, 0, 30)
	{
		x -= 1 << i;
		if (x < 0)
		{
			x += 1 << i;
			break;
		}
		num[++tot] = id * (1 << i);
	}
	if (x) num[++tot] = id * x;
}

signed main()
{
#ifdef CraZYali
	file("5E07-new");
#endif
	while (1)
	{
		int sum(0);
		REP(i, 1, 6) sum += (i * (a[i] = read<int>()));
		if (!sum) return 0;
		if (sum & 1) puts("Can't");
		else
		{
			tot = 0;
			REP(i, 1, 6) split(a[i], i);
			sum /= 2;
			REP(i, 0, sum) dp[i] = 0;
			REP(i, 1, tot)
				DREP(j, sum, num[i]) chkmax(dp[j], dp[j-num[i]] + num[i]);
			puts(dp[sum] == sum ? "Can" : "Can't");
		}
	}
	return 0;
}
