/*
 * File Name:	2038.cpp
 * Author	:	CraZYali
 * Year		:	2019.10.24 20:01
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;
const int maxn = 20 + 5;

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

int d, n, ans, cnt;
int x[maxn], y[maxn], qaq[maxn];

int main()
{
#ifdef CraZYali
	file("2038");
#endif
	cin >> d >> n;
	REP(i, 1, n)
	{
		x[i] = read<int>();
		y[i] = read<int>();
		qaq[i] = read<int>();
	}
	REP(x, 0, 128)
		REP(y, 0, 128)
		{
			int ccc(0);
			REP(i, 1, n)
				if (abs(::x[i] - x) <= d && abs(::y[i] - y) <= d) ccc += qaq[i];
			if (ccc > ans)
			{
				ans = ccc;
				cnt = 1;
			}
			else cnt += (ccc == ans);
		}
	cout << cnt << ' ' << ans << endl;
	return 0;
}
