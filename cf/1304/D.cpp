/*
	Problem:	D.cpp
	Time:		2020-02-24 11:22
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
const int maxn = 2e5 + 10;

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int T, n, a[maxn];
char s[maxn];

int main()
{
#ifdef CraZYali
	file("D");
#endif
	cin >> T;
	while (T--)
	{
		scanf("%d%s", &n, s + 1);
		int last = 1, cur = n;
		REP(i, 1, n)
			if (i == n || s[i] == '>')
			{
				DEP(j, i, last) a[j] = cur--;
				last = i + 1;
			}
		REP(i, 1, n) printf("%d%c", a[i], i == n ? '\n' : ' ');
		last = 1, cur = 1;
		REP(i, 1, n)
			if (i == n || s[i] == '<')
			{
				DEP(j, i, last) a[j] = cur++;
				last = i + 1;
			}
		REP(i, 1, n) printf("%d%c", a[i], i == n ? '\n' : ' ');
	}
	return 0;
}
