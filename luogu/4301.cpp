/*
 * File Name:	4301.cpp
 * Author	:	CraZYali
 * Time		:	2020.01.18 22:39
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <algorithm>
#include <iostream>
#include <cstdio>
#define int long long
using namespace std;
const int maxn = 100 + 5;

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

int a[maxn], n, p[40];
inline void insert(int x)
{
	DEP(i, 30, 0) if (x & (1 << i))
		if (p[i]) x ^= p[i];
		else return void(p[i] = x);
}
inline bool inside(int x)
{
	DEP(i, 30, 0) if (x & (1 << i)) x ^= p[i];
	return !x;
}

signed main()
{
#ifdef CraZYali
	file("4301");
#endif
	long long ans = 0;
	REP(i, 1, n = read<int>()) a[i] = read<int>();
	sort(a + 1, a + 1 + n, greater <int>() );
	REP(i, 1, n)
		if (!inside(a[i])) insert(a[i]);
		else ans += a[i];
	cout << ans << endl;
	return 0;
}
