/*
	Problem:	D.cpp
	Time:		2020-11-26 22:19
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
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, a[maxn], x;
int cnt[maxn], s1[maxn], s2[maxn], fir[maxn << 1];

int main()
{
#ifdef CraZYali
	file("D");
#endif
	n = read<int>();
	REP(i, 1, n)
	{
		a[i] = read<int>();
		cnt[a[i]]++;
		if (cnt[a[i]] > cnt[x]) x = a[i];
	}
	REP(i, 1, n) s1[i] = s1[i - 1] + (a[i] == x);
	int ans = 0;
	REP(y, 1, 100) if (cnt[y] && x != y)
	{
		REP(i, 1, n) s2[i] = s2[i - 1] + (a[i] == y);
		memset(fir, -1, sizeof fir);
		REP(i, 0, n)
		{
			int val = s1[i] - s2[i] + n;
			if (~fir[val]) ans = max(ans, i - fir[val]);
			else fir[val] = i;
		}
	}
	cout << ans << endl;
	return 0;
}
