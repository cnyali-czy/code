/*
	Problem:	B.cpp
	Time:		2020-08-11 0N:35
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cstring>
#include <iostream>
#include <cstdio>
#define i64 long long
using namespace std;
const int N = 10, sig = N + 1, maxn = 5e5 + 10, MOD = 1e9 + 7;
//sig is fake sig
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
		ans = ans * N + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, q;
char str[maxn];

unsigned i64 qaq[sig][sig];
struct Matrix
{
	int a[sig][sig];
	void unit(int x)
	{
		REP(i, 0, N) REP(j, 0, N) a[i][j] = 0;
		REP(i, 0, N) a[i][i] = 1;
		REP(i, 0, N) a[i][x] = 1;
	}
	void unit_inv(int x)
	{
		REP(i, 0, N) REP(j, 0, N) a[i][j] = 0;
		REP(i, 0, N) a[x][i] = (i == x);
		REP(i, 0, N) if (i != x)
			REP(j, 0, N)
			{
				a[i][j] = (i == j) - (x == j);
				if (a[i][j] < 0) a[i][j] += MOD;
			}
	}
	inline int * operator [] (int x) {return a[x];}
};
inline Matrix operator * (Matrix a, Matrix b)
{
	static Matrix c;
	REP(i, 0, N) REP(j, 0, N) qaq[i][j] = 0;
	int ca = 0, cb = 0;
	REP(i, 0, N) REP(j, 0, N)
	{
		ca += !!a[i][j];
		cb += !!b[i][j];
	}
	if (ca < cb)
	{
		REP(i, 0, N) REP(k, 0, N) if (a[i][k])
			REP(j, 0, N) qaq[i][j] += 1ll * a[i][k] * b[k][j];
	}
	else
	{
		REP(k, 0, N) REP(j, 0, N) if (b[k][j])
			REP(i, 0, N) qaq[i][j] += 1ll * a[i][k] * b[k][j];
	}
	REP(i, 0, N) REP(j, 0, N) c[i][j] = qaq[i][j] % MOD;
	return c;
}

Matrix prod[maxn], Inv[maxn];

int main()
{
#ifdef CraZYali
	file("B");
#endif
	scanf("%s\n%d", str + 1, &q);
	n = strlen(str + 1);
	REP(i, 1, n) str[i] -= 'a';
	DEP(i, n, 1)
	{
		prod[i].unit(str[i]);
		Inv[i].unit_inv(str[i]);
		if (i < n)
		{
			prod[i] = prod[i] * prod[i + 1];
			Inv[i] = Inv[i + 1] * Inv[i];
		}
	}
	REP(Case, 1, q)
	{
		int l = read<int>(), r = read<int>();
		i64 ans = 0;
		REP(i, 0, N - 1)
		{
			i64 tmp = 0;
			REP(k, 0, N) tmp += 1ll * prod[l][N][k] * (r < n ? Inv[r + 1][k][i] : (k == i)) % MOD;
			ans += tmp;
		}
		printf("%lld\n", ans % MOD);
	}
	return 0;
}
