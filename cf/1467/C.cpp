/*
	Problem:	C.cpp
	Time:		2021-01-09 08:40
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
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n1, n2, n3, a[maxn], b[maxn], c[maxn];

signed main()
{
#ifdef CraZYali
	file("C");
#endif
	n1 = read<int>();
	n2 = read<int>();
	n3 = read<int>();
	int s = 0, s1 = 0, s2 = 0, s3 = 0;
	REP(i, 1, n1) s1 += (a[i] = read<int>());sort(a + 1, a + 1 + n1);
	REP(i, 1, n2) s2 += (b[i] = read<int>());sort(b + 1, b + 1 + n2);
	REP(i, 1, n3) s3 += (c[i] = read<int>());sort(c + 1, c + 1 + n3);
	s = s1 + s2 + s3;
	int ans = s;
	ans -= 2 * (a[1] + b[1] + c[1]);
	ans += 2 * max(a[1], max(b[1], c[1]));
	int res = s;
	res -= min(s1, min(s2, s3)) * 2;
	cout << max(ans, res) << endl;
	return 0;
}
