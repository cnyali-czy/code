/*
	Problem:	C.cpp
	Time:		2020-02-24 22:47
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cstring>
#include <iostream>
#include <cstdio>
#define int long long
using namespace std;
const int maxn = 2e5 + 10;

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

int n, m, p[maxn];
long long s[maxn], cnt[30];
char str[maxn];

signed main()
{
#ifdef CraZYali
	file("C");
#endif
	register int T = read<int>();
	while (T--)
	{
		n = read<int>();m = read<int>();
		REP(i, 1, n) s[i] = 0;
		scanf("%s", str + 1);
		REP(i, 1, m) s[read<int>()]++;
		s[n + 1] = 1;
		DEP(i, n, 1) s[i] += s[i + 1];
		REP(i, 0, 26) cnt[i] = 0;
		REP(i, 1, n) cnt[str[i] - 'a'] += s[i];
		REP(i, 0, 25) cout << cnt[i] << (i == 25 ? '\n' : ' ');
	}
	return 0;
}
