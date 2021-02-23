/*
	Problem:	check.cpp
	Time:		2021-02-21 09:23
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
const int maxn = 1e6 + 10;

signed main()
{
	freopen("check.out", "w", stdout);
	FILE *fin = fopen("C.in", "r"), *fans = fopen("C.out", "r");
	int a, b, c, N;
	fscanf(fin, "%lld%lld%lld%lld", &a, &b, &c, &N);
	static int n, x[maxn], y[maxn];
	fscanf(fans, "%lld", &n);
	REP(i, 1, n) fscanf(fans, "%lld", x + i);
	REP(i, 1, n) fscanf(fans, "%lld", y + i);
	int ra = 0, rb = 0, rc = 0;
	REP(i, 1, n) ra += x[i] * x[i];
	REP(i, 1, n) rb += y[i] * y[i];
	REP(i, 1, n) rc += x[i] * y[i];
	int cnt = 0;
	if (a == ra) printf("a = %lld ok\n", a), cnt++;else cerr << a << ' ' << ra << endl;
	if (b == rb) printf("b = %lld ok\n", b), cnt++;else cerr << b << ' ' << rb << endl;
	if (c == rc) printf("c = %lld ok\n", c), cnt++;else cerr << c << ' ' << rc << endl;
	if (N < n) printf("%lld > %lld\n", n, N);
	else if (cnt == 3) puts("!!! ALL OK !!!");

	return 0;
}
