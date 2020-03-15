/*
	Problem:	E.cpp
	Time:		2020-03-15 17:09
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
const int maxn = 1e5 + 10, maxS = 1 << 7, maxp = 10;

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

int n, p, k;

struct person
{
	int a, s[maxp];
	inline bool operator < (const person &B) const {return a > B.a;}
}P[maxn];
#define s(i, j) P[i].s[j]
#define a(i) P[i].a

i64 dp[maxn][maxS];
int cnt[maxS];
int main()
{
#ifdef CraZYali
	file("E");
#endif
	n = read<int>();p = read<int>();k = read<int>();
	const int lim = (1 << p) - 1;
	REP(i, 1, n) a(i) = read<int>();
	REP(i, 1, n) REP(j, 1, p) s(i, j) = read<int>();
	sort(P + 1, P + 1 + n);
	REP(i, 1, lim) cnt[i] = cnt[i >> 1] + (i & 1);
//	REP(i, 1, n) printf("%d%c", a(i), i == n ? '\n' : ' ');
//	REP(i, 1, n) REP(j, 1, p) printf("%d%c", s(i, j), j == end_j ? '\n' : ' ');
	REP(i, 1, n) REP(j, 0, lim)
	{
		if (i > cnt[j])
		{
			dp[i][j] = dp[i-1][j];
			if (i - cnt[j] - 1 < k) dp[i][j] += a(i);
		}
		if (i >= cnt[j])
			REP(k, 0, p - 1) if (j >> k & 1)
				chkmax(dp[i][j], dp[i - 1][j ^ (1 << k)] + s(i, k + 1));
	}
//	REP(i, 1, n) REP(j, 0, lim) printf("%lld%c", dp[i][j], j == end_j ? '\n' : ' ');
	cout << dp[n][lim] << '\n';
	return 0;
}
