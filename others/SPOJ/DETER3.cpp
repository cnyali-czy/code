/*
	Problem:	DETER3.cpp
	Time:		2020-02-14 14:46
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
#define int long long
using namespace std;
const int maxn = 200 + 5;

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
int n, MOD, a[maxn][maxn];

signed main()
{
#ifdef CraZYali
	file("DETER3");
#endif
	while (scanf("%d%d", &n, &MOD) != EOF)
	{
		REP(i, 1, n) REP(j, 1, n) a[i][j] = read<int>() % MOD;
		int flag = 1;
		REP(i, 1, n)
		{
			if (!a[i][i])
				REP(j, i + 1, n) if (a[j][i])
				{
					flag = -flag;
					swap(a[i], a[j]);
					break;
				}
			REP(j, i + 1, n)
			{
				while (a[j][i])
				{
					int ccc = a[i][i] / a[j][i];
					REP(k, i, n) ((a[i][k] -= a[j][k] * ccc % MOD) += MOD) %= MOD;
					swap(a[i], a[j]);
					flag = -flag;
				}
				REP(k, i + 1, n) if (a[k][i])
				{
					swap(a[i], a[k]);
					flag = -flag;
					break;
				}
				if (!a[i][i]) break;
			}
			if (!a[i][i]) break;
		}
		int ans = 1;
		REP(i, 1, n) (ans *= a[i][i]) %= MOD;
		cout << (MOD + flag * ans) % MOD << '\n';
	}
	return 0;
}
