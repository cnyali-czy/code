/*
	Problem:	6187.cpp
	Time:		2020-03-07 22:41
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
#define i64 long long
using namespace std;
const int maxn = 2e5 + 10;

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

int n, q, a[maxn];

i64 mem[maxn], s[maxn];
i64 solve(int g)
{
	i64 &res = mem[g];
	if (res) return res;
	for (int i = n / g; i <= n; i += n / g)
		res += s[i-1] - s[i - n / g + 2] + 1ll * a[i] * a[i-1] + 1ll * a[i] * a[i-2] + 1ll * a[i-n/g+2] * a[i-n/g+1];
	return res;
}

int main()
{
#ifdef CraZYali
	file("6187");
#endif
	n = read<int>();q = read<int>();
	REP(i, 1, n) a[i] = read<int>(), mem[0] += 1ll * a[i] * a[i];
	sort(a + 1, a + 1 + n);
	REP(i, 3, n) s[i] = s[i - 1] + 1ll * a[i] * a[i - 2];
	while (q--)
	{
		int x = read<int>();
		if (!x) printf("%lld\n", mem[x]);
		else printf("%lld\n", solve(__gcd(n, x)));
	}
	return 0;
}
