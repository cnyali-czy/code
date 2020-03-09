/*
	Problem:	B.cpp
	Time:		2020-03-08 09:39
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
const int maxn = 500 + 5, maxm = maxn * maxn / 2, MOD = 1e9 + 7;

inline int add(int x, int y) {x += y;return x >= MOD ? x - MOD : x;}
inline int sub(int x, int y) {x -= y;return x <    0 ? x + MOD : x;}
inline i64 mul(i64 x, int y) {x *= y;return x >= MOD ? x % MOD : x;}
inline void inc(int &x, int y) {x += y;if (x >= MOD) x -= MOD;}
inline void dec(int &x, int y) {x -= y;if (x <    0) x += MOD;}

inline int power_pow(int base, int b)
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

int n, m, k, u[maxm], v[maxm];
int M[10005][10005];

inline int det(int n)
{
	int ans = 1;
	REP(i, 1, n)
	{
		if (!M[i][i])
			REP(j, i + 1, n) if (M[j][i])
			{
				swap(M[j], M[i]);
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

namespace bf
{
	void work()
	{
		int N = n * k;
		REP(i, 1, k)
		{
			int S = (i - 1) * n;
			REP(j, 1, m)
			{
				int u = S + ::u[j], v = S + ::v[j];
				if (!M[u][v]) M[u][v] = M[v][u] = MOD;
				M[u][v]--;M[v][u]--;
				M[u][u]++;M[v][v]++;
			}
		}
		REP(i, 2, k)
		{
			int S1 = (i - 2) * n, S2 = S1 + n;
			REP(j, 1, n)
			{
				int u = j + S1, v = j + S2;
				if (!M[u][v]) M[u][v] = M[v][u] = MOD;
				M[u][v]--;M[v][u]--;
				M[u][u]++;M[v][v]++;
			}
		}
		cout << det(N - 1) << '\n';
	}
}

int main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read<int>();m = read<int>();k = read<int>();
	REP(i, 1, m)
	{
		u[i] = read<int>();
		v[i] = read<int>();
	}
	bf::work();
	return 0;
}
