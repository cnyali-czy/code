/*
	Problem:	C.cpp
	Time:		2020-04-08 22:48
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

using namespace std;
#define i64 long long
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

int n;
i64 s[maxn], a[maxn];
int cnt[maxn];
int main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();
	REP(i, 1, n)
	{
		s[i] = s[i-1] + read<int>();
		a[i] = s[i];
	}
	sort(a, a + 1 + n);
	int m = unique(a, a + 1 + n) - a;
	REP(i, 0, n)
		s[i] = lower_bound(a, a + 1 + m, s[i]) - a;
	cnt[s[0]] = 1;
	int j = 0;
	i64 ans = 0;
	REP(i, 1, n)
	{
		cnt[s[i]]++;
		while (cnt[s[i]] > 1) cnt[s[j++]]--;
		ans += i - j;
	}
	cout << ans << endl;
	return 0;
}
