/*
	Problem:	A.cpp
	Time:		2020-02-20 09:30
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
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

namespace run
{
#define i64 long long
	using namespace std;
	const int MOD = 998244353, maxn = 2000 + 10;

	inline int add(int x, int y) {register int res = x + y;return res >= MOD ? res - MOD : res;}
	inline int sub(int x, int y) {register int res = x - y;return res <    0 ? res + MOD : res;}
	inline i64 mul(i64 x, int y) {register i64 res = x * y;return res >= MOD ? res % MOD : res;}
	template <typename T>
	inline void inc(T &x, int y) {x += y;if (x >= MOD) x -= MOD;}
	int power_pow(i64 base, int b)
	{
		i64 ans = 1;
		while (b)
		{
			if (b & 1) ans = mul(ans, base);
			base = mul(base, base);
			b >>= 1;
		}
		return ans;
	}

	char s[maxn][maxn];
	int n, m, k;
	i64 sum[maxn][maxn], a[maxn][maxn], b[maxn][maxn], c[maxn][maxn], d[maxn][maxn];

	inline void delad(i64 a[maxn][maxn], int x1, int y1, int x2, int y2)
	{
		a[x1][y1]++;
		a[x2 + 1][y1]--;
		a[x1][y2 + 1]--;
		a[x2 + 1][y2 + 1]++;
	}

	inline void getsum(i64 a[maxn][maxn])
	{
		REP(i, 1, n) REP(j, 1, m) inc(a[i][j], sub(add(a[i-1][j], a[i][j-1]), a[i-1][j-1]));
	}

	int main()
	{
		n = read<int>();m = read<int>();k = read<int>();
		REP(i, 1, n)
		{
			scanf("%s", s[i] + 1);
			REP(j, 1, m) sum[i][j] = sum[i][j-1] + s[i][j] - '0';
		}
		REP(i, 1, n) REP(j, 1, m)
			for (int y = j; y <= m && s[i][y] == '1'; y++)
				for (int x = i; x <= n && sum[x][y] - sum[x][j-1] == y - j + 1;x++)
				{
					delad(a, i, j, x, y);
					delad(b, i, j, x, y - 1);
					delad(c, i, j, x - 1, y);
					delad(d, i, j, x - 1, y - 1);
				}
		getsum(a);
		getsum(b);
		getsum(c);
		getsum(d);
		int ans = 0;
		REP(i, 1, n) REP(j, 1, m)
			inc(ans, sub(add(power_pow(a[i][j], k), power_pow(d[i][j], k)), add(power_pow(b[i][j], k), power_pow(c[i][j], k))));
		cout << ans << endl;
		return 0;
	}
}


int main()
{
#ifdef CraZYali
	file("A");
#endif
	return run::main();
}
