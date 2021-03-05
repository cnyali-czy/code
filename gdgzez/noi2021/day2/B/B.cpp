/*
	Problem:	B.cpp
	Time:		2021-02-26 15:47
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 5e5 + 10;

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

int n, a[maxn];
i64 s[maxn];

inline bool chkmax(double &x, double y) {if (x < y) {x = y;return 1;}return 0;}

inline double f1(int mid, int k)
{
	return a[mid] - (s[k] + s[mid + k] - s[mid - 1]) / (2 * k + 1.);
}
inline double f2(int mid, int k)
{
	return (s[mid] - s[mid - k - 1] + s[n] - s[n - k]) / (2 * k + 1.) - a[mid];
}

namespace bf
{
	int main()
	{
		double ans = 0;
		REP(mid, 1, n)
		{
			REP(k, 1, min(n - mid, mid - 1))
				ans = max(ans, a[mid] - (s[k] + s[mid + k] - s[mid - 1]) / (2 * k + 1.));
			REP(k, 1, min(n - mid, mid - 1))
				ans = max(ans, (s[mid] - s[mid - k - 1] + s[n] - s[n - k]) / (2 * k + 1.) - a[mid]);
		}
		printf("%.10lf\n", ans);
		return 0;
	}
}

int main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read<int>();
	REP(i, 1, n) s[i] = s[i - 1] + (a[i] = read<int>());
	if (n <= 5000) return bf :: main();
	double ans = 0;
	int bst1 = 1, bst2 = 1;
	REP(i, 1, n)
	{
		/*
		   REP(k, 1, min(n - mid, mid - 1))
		   if (chkmax(ans, a[mid] - (s[k] + s[mid + k] - s[mid - 1]) / (2 * k + 1.)));
		   REP(k, 1, min(n - mid, mid - 1))
		   printf("%.2lf%c", a[mid] - (s[k] + s[mid + k] - s[mid - 1]) / (2 * k + 1.), k == end_k ? '\n' : ' ' );
		   */
		int l = 1, r = min(n - i, i - 1) - 1;chkmax(ans, f1(i, r + 1));
		while (l <= r)
		{
			int mid = l + r >> 1;
			double y1 = f2(i, mid), y2 = f2(i, mid + 1);
			chkmax(ans, max(y1, y2));
			if (y1 <= y2) l = mid + 1;
			else r = mid - 1;
		}
	}
	REP(i, 1, n)
	{
		/*
		   REP(k, 1, min(n - mid, mid - 1))
		   if (chkmax(ans, (s[mid] - s[mid - k - 1] + s[n] - s[n - k]) / (2 * k + 1.) - a[mid]));
		   REP(k, 1, min(n - mid, mid - 1))
		   printf("%.2lf%c", (s[mid] - s[mid - k - 1] + s[n] - s[n - k]) / (2 * k + 1.) - a[mid], k == end_k ? '\n' : ' ' );
		   */
		int l = 1, r = min(n - i, i - 1) - 1;chkmax(ans, f2(i, r + 1));
		while (l <= r)
		{
			int mid = l + r >> 1;
			double y1 = f2(i, mid), y2 = f2(i, mid + 1);
			chkmax(ans, max(y1, y2));
			if (y1 <= y2) l = mid + 1;
			else r = mid - 1;
		}
	}
	printf("%.10lf\n", ans);
	return 0;
}
