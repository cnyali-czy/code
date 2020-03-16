/*
	Problem:	G.cpp
	Time:		2020-03-16 17:31
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e6 + 10;

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

int prime[maxn], pcnt, phi[maxn], n, k;
bool notp[maxn];

int main()
{
#ifdef CraZYali
	file("G");
#endif
	n = read<int>();k = read<int>();
	phi[1] = 1;
	REP(i, 2, n)
	{
		if (!notp[i]) phi[prime[++pcnt] = i] = i - 1;
		REP(j, 1, pcnt)
		{
			int tmp = i * prime[j];
			if (tmp > n) break;
			notp[tmp] = 1;
			if (i % prime[j]) phi[tmp] = phi[i] * (prime[j] - 1);
			else {phi[tmp] = phi[i] * prime[j];break;}
		}
	}
	sort(phi + 1, phi + 1 + n);
	long long ans = 0;
	REP(i, 1, k + 2) ans += phi[i];
	cout << ans - (k == 1) << '\n';
	return 0;
}
