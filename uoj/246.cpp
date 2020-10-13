/*
	Problem:	246.cpp
	Time:		2020-10-12 20:54
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cmath>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 2e5 + 10, inf = 1e9;

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

int n, m, k;
int a[maxn];
const int B = 300;
int w[maxn][B + 5];

int main()
{
#ifdef CraZYali
	file("246");
#endif
	n = read<int>();m = read<int>();k = read<int>();
	REP(i, 1, n) a[i] = read<int>();
	DEP(j, n, 1)
	{
		w[j][0] = inf;
		int s = inf;
		DEP(i, j - 1, 1)
		{
			w[i][j - i] = min(abs(a[i] - a[j]), w[i + 1][j - (i + 1)]);
			if (j - i + 1 >= B) break;
		}
	}
	long long ans = 0;
	REP(i, 1, n)
	{
		int s = inf;
		REP(j, i + 1, min(i + B - 1, n))
		{
			s = min(s, w[i][j - i]);
			if (j - i + 1 >= k) ans = max(ans, 1ll * (j - i) * s);
		}
	}
	//r - l + 1 <= B done
	//now work r - l + 1 > B
	//r - l >= B
	//s <= m / B
	static int g[maxn], las[maxn];
	REP(i, 1, n)
	{
		int pre = 0;
		REP(j, 0, m / B + 1)
		{
			if (a[i] - j >= 1 && las[a[i] - j]) g[j] = max(g[j], las[a[i] - j]);
			if (a[i] + j <= m && las[a[i] + j]) g[j] = max(g[j], las[a[i] + j]);
			pre = max(pre, g[j]);
			if (i - pre >= k) ans = max(ans, 1ll * (i - pre - 1) * (j + 1));
		}
		las[a[i]] = i;
	}
	cout << ans << endl;
	return 0;
}
