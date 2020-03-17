/*
	Problem:	B.cpp
	Time:		2020-03-17 09:24
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
#define i64 long long
using namespace std;
const int maxn = 500 + 5, MOD = 1e9 + 7;

inline int add(int x, int y) {x += y;return x >= MOD ? x - MOD : x;}
inline int sub(int x, int y) {x -= y;return x <    0 ? x + MOD : x;}
inline i64 mul(i64 x, int y) {x *= y;return x >= MOD ? x % MOD : x;}
inline void inc(int &x, int y) {x += y;if (x >= MOD) x -= MOD;}
inline void dec(int &x, int y) {x -= y;if (x <    0) x += MOD;}

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

int n, k, a[maxn][maxn], u[maxn], v[maxn], deg[maxn];

int det(int n)
{
	int ans = 1;
	//	REP(i, 1, n) REP(j, 1, n) printf("%d%c", a[i][j], j == n ? '\n' : ' ');
	REP(i, 1, n)
	{
		if (!a[i][i])
			REP(j, i + 1, n) if (a[j][i])
			{
				swap(a[i], a[j]);
				ans = MOD - ans;
				break;
			}
		if (!a[i][i]) return 0;
		ans = mul(ans, a[i][i]);
		const int Inv = inv(a[i][i]);
		REP(j, i + 1, n) if (a[j][i])
		{
			int qaq = mul(a[j][i], Inv);
			REP(k, i, n) dec(a[j][k], mul(a[i][k], qaq));
		}
	}
	//	cout << ans << endl;
	//	puts("");
	return ans;
}

int f[maxn];
namespace Gauss
{
	int a[maxn][maxn];
	void solve()
	{
		REP(i, 0, n - 1)
		{
			if (!a[i][i])
				REP(j, i + 1, n - 1) if (a[j][i])
				{
					swap(a[i], a[j]);
					break;
				}
			const int Inv = inv(a[i][i]);
			REP(j, i + 1, n) if (a[j][i])
			{
				int qaq = mul(a[j][i], Inv);
				REP(k, i, n) dec(a[j][k], mul(a[i][k], qaq));
			}
		}
		DEP(i, n - 1, 0)
		{
			REP(j, i + 1, n - 1) dec(a[i][n], mul(a[i][j], f[j]));
			f[i] = mul(a[i][n], inv(a[i][i]));
		}
	}
}

int main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read<int>();k = read<int>();
	REP(i, 2, n)
	{
		u[i] = read<int>();
		v[i] = read<int>();
		deg[u[i]]++;deg[v[i]]++;
	}
	REP(x, 0, n - 1)
	{
		REP(i, 1, n) a[i][i] = add(n - 1 - deg[i], mul(deg[i], x));
		REP(i, 1, n) REP(j, 1, n) if (i ^ j) a[i][j] = MOD - 1;
		REP(i, 2, n) a[u[i]][v[i]] = a[v[i]][u[i]] = MOD - x;
		int bin = 1;
		REP(i, 0, n - 1)
		{
			Gauss::a[x][i] = bin;
			bin = mul(bin, x);
		}
		Gauss::a[x][n] = det(n - 1);
	}
	Gauss::solve();
	int ans = 0;
	DEP(i, n - 1, n - k - 1) inc(ans, f[i]);
	cout << ans << '\n';
	return 0;
}
