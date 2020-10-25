/*
	Problem:	3185.cpp
	Time:		2020-10-25 20:44
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cstring>
#include <cstdlib>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 22;

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

int n, a[maxn];
int mex(long long sta) {return __builtin_ctzll(~sta);}

int sg[maxn];

void work()
{
	n = read<int>();
	sg[n] = 0;
	DEP(i, n - 1, 1)
	{
		long long sta = 0;
		REP(j, i + 1, n) REP(k, j, n)
			sta |= (1ll << (sg[j] ^ sg[k]));
		sg[i] = mex(sta);
	}
	int ssr = 0;
	REP(i, 1, n)
	{
		a[i] = read<int>();
		if (a[i] & 1) ssr ^= sg[i];
	}
	if (ssr)
	{
		int cnt = 0;
		REP(i, 1, n) if (a[i])
			REP(j, i + 1, n) REP(k, j, n) if ( (ssr ^ sg[i] ^ sg[j] ^ sg[k]) == 0)
			{
				cnt++;
				if (cnt == 1) printf("%d %d %d\n", i - 1, j - 1, k - 1);
			}
		printf("%d\n", cnt);
	}
	else
	{
		puts("-1 -1 -1");
		puts("0");
	}
}

int main()
{
#ifdef CraZYali
	file("3185");
#endif
	register int T = read<int>();
	while (T--) work();
	return 0;
}
