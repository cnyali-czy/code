/*
	Problem:	5337.cpp
	Time:		2020-07-30 23:43
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
#define i64 long long

using namespace std;
const int maxn = 26, MOD = 1e9 + 7;

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

i64 n;
char s[100005];

struct Matrix
{
	int a[maxn][maxn];
	inline int* operator [] (int x) {return a[x];}
	inline Matrix operator * (Matrix b)
	{
		Matrix res;
		REP(i, 0, 25) REP(j, 0, 25) res[i][j] = 0;
		REP(i, 0, 25) REP(k, 0, 25) if (a[i][k])
			REP(j, 0, 25) if (b[k][j]) res[i][j] = (res[i][j] + 1ll * a[i][k] * b[k][j]) % MOD;
		return res;
	}
}good;

Matrix power_pow(Matrix base, i64 b)
{
	Matrix ans = base;b--;
	while (b)
	{
		if (b & 1) ans = ans * base;
		base = base * base;
		b >>= 1;
	}
	return ans;
}

int main()
{
#ifdef CraZYali
	file("5337");
#endif
	scanf("%lld%s", &n, s + 1);
	REP(i, 0, 25) REP(j, 0, 25) good[i][j] = 1;
	REP(i, 2, strlen(s + 1)) good[s[i - 1] - 'a'][s[i] - 'a'] = 0;
	good = power_pow(good, n - 1);
	i64 ans = 0;
	REP(i, 0, 25) REP(j, 0, 25) ans += good[i][j];
	cout << ans % MOD << endl;
	return 0;
}
