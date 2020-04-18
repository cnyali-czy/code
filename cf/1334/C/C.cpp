/*
	Problem:	C.cpp
	Time:		2020-04-10 22:54
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <iostream>
#include <cstring>
#include <algorithm>
#define int long long
using namespace std;
const int maxn = 3e5 + 10;

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

int n;
int a[maxn], b[maxn];
bool vis[maxn];
signed main()
{
#ifdef CraZYali
	file("C");
#endif
	register int T = read<int>();
	while (T--)
	{
		n = read<int>();
		REP(i, 0, n - 1) a[i] = read<int>(), b[i] = read<int>();
		int ans = 0, Min = 1e18;
		REP(i, 0, n - 1) chkmin(b[i], a[(i + 1) % n]);
		REP(i, 0, n - 1)
		{
			ans += a[i] - b[(i+n-1)%n];
			chkmin(Min, b[i]);
		}
		cout << ans + Min << '\n';
	}
	return 0;
}
