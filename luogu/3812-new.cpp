/*
 * File Name:	3812-new.cpp
 * Author	:	CraZYali
 * Time		:	2020.01.18 19:16
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <iostream>
#include <cstdio>

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

int n;
long long p[55];

inline void insert(long long x)
{
	DEP(i, 50, 0)
		if (x & (1ll << i))
			if (!p[i]) return void(p[i] = x);
			else x ^= p[i];
}

int main()
{
#ifdef CraZYali
	file("3812-new");
#endif
	REP(i, 1, n = read<int>()) insert(read<long long>());
	long long ans = 0;
	DEP(i, 50, 0) chkmax(ans, ans ^ p[i]);
	cout << ans << endl;
	return 0;
}
