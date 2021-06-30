/*
	Problem:	A.cpp
	Time:		2021-06-29 08:10
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

using namespace std;
const int maxn = 1e5 + 10, inf = 1e8;

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

int n, f[maxn], fir[26], g[26];
char s[maxn];

int main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();
	scanf("%s", s + 1);
	REP(i, 0, 25) fir[i] = -1, g[i] = inf;
	REP(i, 1, n)
	{
		int c = s[i] - 'a';
		f[i] = inf;
		REP(j, 0, 25) if (j != c && ~fir[j])
			f[i] = min(f[i], g[j]/*f[fir[j] - 1]*/ + 1);
		fir[c] = i;
		g[c] = min(g[c], f[i - 1]);
	}
	printf("%d\n", f[n] < n ? f[n] : -1);
	return 0;
}
