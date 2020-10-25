/*
	Problem:	C.cpp
	Time:		2020-10-25 19:22
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
#define int long long

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
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int a[10], n, b[maxn];
int ans;

int work(int I, int J)
{
	int Min = b[I] - a[J], Max = -1;
	REP(i, 1, n) if (I != i)
	{
		bool flag = 0;
		DEP(j, 6, 1)
			if (b[i] - a[j] >= Min)
			{
				flag = 1;
				Max = max(Max, b[i] - a[j]);
				break;
			}
		if (!flag) return 1e18;
	}
	if (Max != -1) return Max - Min;
	else return 1e18;
}
int work(int i)
{
	int ans = 1e18;
	REP(j, 1, 6) ans = min(ans, work(i, j));
	return ans;
}
int work2(int I, int J)
{
	int Max = b[I] - a[J], Min = 1e18;
	REP(i, 1, n) if (I != i)
	{
		bool flag = 0;
		REP(j, 1, 6)
			if (b[i] - a[j] <= Max)
			{
				flag = 1;
				Min = min(Min, b[i] - a[j]);
				break;
			}
		if (!flag) return 1e18;
	}
	if (Min < 1e18) return Max - Min;
	else return 1e18;
}
int work2(int i)
{
	int ans = 1e18;
	REP(j, 1, 6) ans = min(ans, work2(i, j));
	return ans;
}

signed main()
{
#ifdef CraZYali
	file("C");
#endif
	REP(i, 1, 6) a[i] = read<int>();sort(a + 1, a + 7);
	n = read<int>();
	REP(i, 1, n) b[i] = read<int>();
	sort(b + 1, b + 1 + n);
	int l = 1, r = n;
	ans = 1e18;
	ans = min(ans, work(1));
	ans = min(ans, work(n));
	while (l < r)
	{
		int m1 = (l + l + r) / 3;
		int m2 = (r + r + l + 2) / 3;
		int f1 = work(m1), f2 = work(m2);
		ans = min(min(f1, f2), ans);
		if (f1 > f2) r = m2 - 1;
		else l = m1 + 1;
	}
	l = 1, r = n;
	ans = min(ans, work2(1));
	ans = min(ans, work2(n));
	while (l < r)
	{
		int m1 = (l + l + r) / 3;
		int m2 = (r + r + l + 2) / 3;
		int f1 = work2(m1), f2 = work2(m2);
		ans = min(min(f1, f2), ans);
		if (f1 > f2) r = m2 - 1;
		else l = m1 + 1;
	}
	cout << ans << endl;
	return 0;
}
