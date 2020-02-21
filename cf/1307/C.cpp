/*
	Problem:	C.cpp
	Time:		2020-02-21 11:33
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
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

long long ans, C[26][26];
int n, cnt[26];
char s[maxn];

int main()
{
#ifdef CraZYali
	file("C");
#endif
	scanf("%s", s + 1);
	n = strlen(s + 1);
	REP(i, 1, n)
	{
		cnt[s[i] - 'a']++;
		REP(j, 0, 25)
			if (j != s[i] - 'a') C[j][s[i] - 'a'] += cnt[j];
			else C[j][s[i] - 'a'] += cnt[j] - 1;
	}
	REP(i, 0, 25)
	{
		chkmax(ans, cnt[i]);
		REP(j, 0, 25) chkmax(ans, C[i][j]);
	}
	cout << ans << '\n';
	return 0;
}
