/*
	Problem:	C.cpp
	Time:		2020-12-30 22:51
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

int n;
char s[maxn];
bool change[maxn];

int main()
{
#ifdef CraZYali
	file("C");
#endif
	register int T = read<int>();
	while (T--)
	{
		scanf("%s", s + 1);
		n = strlen(s + 1);
		/*
		REP(i, 1, n) s[i] -= 'a';
		REP(i, 1, n) REP(j, 0, 25) f[i][j] = inf;
		REP(i, 0, 25)
			if (i == s[1]) f[1][i] = 0;
			else f[1][i] = 1;
		REP(i, 1, n - 1)
			REP(j, 0, 25) REP(k, 0, 25) if (j != k)
			{
				if (i > 1 && s[i - 1] == k)
			}
		int ans = inf;
		REP(i, 0, 25) ans = min(ans, f[n][i]);
		*/
		REP(i, 1, n) change[i] = 0;
		int ans = 0;
		s[0] = s[n + 1] = s[n + 2] = '#';
		REP(i, 2, n)
			if (s[i] == s[i - 1] || s[i] == s[i - 2])
			{
				bool flg = 0;
				REP(j, 'a', 'z')
					if (j != s[i - 1] && j != s[i - 2] && j != s[i + 1] && j != s[i + 2])
					{
						s[i] = j;
						ans++;
						break;
					}
			}
		printf("%d\n", ans);
	}
	return 0;
}
