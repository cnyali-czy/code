/*
	Problem:	A.cpp
	Time:		2021-02-26 15:41
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
#define int long long

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

int n, q, a[maxn], x, y, ans;

inline int f(int i) {return 1 <= i && i <= n ? y * i + a[i] : -1;}

signed main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();q = read<int>();
	REP(i, 1, n) a[i] = read<int>();
	REP(i, 1, n) a[i] = -a[i];
	REP(i, 1, n) a[i] += a[i - 1];
	while (q--)
	{
		x = read<int>(), y = read<int>(), ans = 0;
		REP(i, y - 2, y + 2) if (f(i) == x) ans++;
		int l = 1, r = min(n, y - 3);
		while (l <= r)
		{
			int mid = l + r >> 1;
			if (f(mid) == x) {ans++;break;}
			if (f(mid) < x) l = mid + 1;
			else r = mid - 1;
		}
		l = min(y + 3, n + 1), r = n;
		while (l <= r)
		{
			int mid = l + r >> 1;
			if (f(mid) == x) {ans++;break;}
			if (f(mid) > x) l = mid + 1;
			else r = mid - 1;
		}
		cout << ans << '\n';
	}
	return 0;
}
