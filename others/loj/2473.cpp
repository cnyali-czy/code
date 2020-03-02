/*
	Problem:	2473.cpp
	Time:		2020-03-02 20:58
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
const int maxn = 1700, maxw = 1700, MOD = 64123;

inline int add(int x, int y) {x += y;return x >= MOD ? x - MOD : x;}
inline int sub(int x, int y) {x -= y;return x <    0 ? x + MOD : x;}
inline i64 mul(i64 x, int y) {x *= y;return x >= MOD ? x % MOD : x;}
inline void inc(int &x, int y) {x += y;if (x >= MOD) x -= MOD;}

int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
inline void Add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

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

int n, k, w, d[maxn];


inline bool cmp(int x, int y) {return d[x] > d[y];}

int id[maxn], a[maxn], dp[maxn][maxw];

void dfs(int x, int fa = 0)
{
	REP(i, 1, k) dp[x][i] = dp[fa][i - a[x]];
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
		dfs(to[i], x);
	if (fa) REP(i, 1, k) inc(dp[fa][i], dp[x][i]);
}

int main()
{
#ifdef CraZYali
	file("2473");
#endif
	n = read<int>();k = read<int>();w = read<int>();
	REP(i, 1, n) d[i] = read<int>();
	REP(i, 2, n)
	{
		int x(read<int>()), y(read<int>());
		Add(x, y);Add(y, x);
	}
	REP(i, 1, n) id[i] = i;
	sort(id + 1, id + 1 + n, cmp);
	int ans = 0;
	REP(I, 1, n)
	{
		int i = id[I];
		a[i] = 1;
		if (I < k) continue;
		dp[0][0] = 1;
		dfs(i);
		inc(ans, mul(d[i], dp[i][k]));
	}
	cout << ans << '\n';
	return 0;
}
