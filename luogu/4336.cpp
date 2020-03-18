/*
	Problem:	4336.cpp
	Time:		2020-03-18 20:31
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <iostream>
#include <cstdio>
#define i64 long long
using namespace std;
const int maxn = 20, MOD = 1e9 + 7;

inline int add(int x, int y) {x += y;return x >= MOD ? x - MOD : x;}
inline int sub(int x, int y) {x -= y;return x <    0 ? x + MOD : x;}
inline i64 mul(i64 x, int y) {x *= y;return x >= MOD ? x % MOD : x;}
inline void inc(int &x, int y) {x += y;if (x >= MOD) x -= MOD;}
inline void dec(int &x, int y) {x -= y;if (x <    0) x += MOD;}

int power_pow(int base, int b)
{
	int ans = 1;
	while (b)
	{
		if (b & 1) ans = mul(ans, base);
		base = mul(base, base);
		b >>= 1;
	}
	return ans;
}
#define inv(x) power_pow(x, MOD - 2)

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

int n, M[maxn][maxn], lg[1 << maxn];
int m[maxn];
pair <int, int> G[maxn][maxn * maxn];

int det(int n)
{
	int ans = 1;
	REP(i, 1, n)
	{
		if (!M[i][i])
			REP(j, i + 1, n) if (M[j][i])
			{
				swap(M[i], M[j]);
				ans = MOD - ans;
				break;
			}
		if (!M[i][i]) return 0;
		ans = mul(ans, M[i][i]);
		const int Inv = inv(M[i][i]);
		REP(j, i + 1, n) if (M[j][i])
		{
			const int ccc = mul(M[j][i], Inv);
			REP(k, i, n) dec(M[j][k], mul(ccc, M[i][k]));
		}
	}
	return ans;
}

int main()
{
#ifdef CraZYali
	file("4336");
#endif
	n = read<int>();
	REP(i, 1, n) lg[1 << i] = i;
	REP(i, 0, n - 2)
	{
		m[i] = read<int>();
		REP(j, 1, m[i]) G[i][j] = make_pair(read<int>(), read<int>());
	}
	int ans = 0;
	REP(S, 1, (1 << n - 1) - 1)
	{
		REP(i, 1, n) REP(j, 1, n) M[i][j] = 0;
		int cnt = 0;
		for (int x = S, i = lg[x & -x]; x; x &= (x - 1), i = lg[x & -x])
		{
			cnt++;
			REP(j, 1, m[i])
			{
				int u(G[i][j].first), v(G[i][j].second);
				M[u][u]++;M[v][v]++;
				if (!M[u][v]) M[u][v] = MOD; M[u][v]--;
				if (!M[v][u]) M[v][u] = MOD; M[v][u]--;
			}
		}
		inc(ans, mul(det(n - 1), (n - cnt) & 1 ? 1 : MOD - 1));
	}
	cout << ans << '\n';
	return 0;
}
