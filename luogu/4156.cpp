/*
	Problem:	4156.cpp
	Time:		2021-06-07 17:23
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
#define i64 long long

using namespace std;
const int maxn = 5e5 + 10;

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n;i64 w;

int fail[maxn];
char s[maxn];

void work()
{
	scanf("%d%lld%s", &n, &w, s + 1);
	int k = 0;
	REP(i, 2, n)
	{
		while (k && s[k + 1] ^ s[i]) k = fail[k];
		fail[i] = (k += (s[k + 1] == s[i]));
	}
	REP(i, 1, n) printf("%d%c", fail[i], i == end_i ? '\n' : ' ' );
}

int main()
{
#ifdef CraZYali
	file("4156");
#endif
	int T;cin >> T;
	while (T--) work();
	return 0;
}
