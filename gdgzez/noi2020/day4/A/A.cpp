#define REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;
#define i64 long long
const int maxn = 1000 + 5;
template <typename T> T read()
{
	T ans(0), flag(1);
	char c(getchar());
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

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

int n, k, MOD;
inline int add(int x, int y) {return (x += y) >= MOD ? x - MOD : x;}
inline int sub(int x, int y) {return (x -  y) <  MOD ? x + MOD : x;}
inline void inc(int &x, int y) {x += y;if (x >= MOD) x -= MOD;}
inline void dec(int &x, int y) {x -= y;if (x <    0) x += MOD;}

int C[maxn][maxn], f[maxn][13], g[maxn][13];
void init_C(int N)
{
	REP(i, 0, N) C[i][0] = 1;
	REP(i, 1, N) REP(j, 1, i) C[i][j] = add(C[i - 1][j], C[i - 1][j - 1]);
}
int calc(int n, int k)
{
	i64 s = 0;
	REP(i, 1, n)
		s += 1ll * C[n - 1][i - 1] * g[i][k] % MOD * g[n - i + 1][k] % MOD;
	return s % MOD;
}
int main()
{
#ifdef CraZYali
	file("A");
#endif
	cin >> n >> k >> MOD;
	if (k > 12) return 0 * puts("0");
	init_C(max(n, k));
	REP(i, 0, 12) f[1][i] = 1;
	REP(i, 1, 12) f[2][i] = 1;
	REP(i, 3, n)
		REP(j, 1, 12)
		REP(k, 2, i - 1)
		{
			inc(f[i][j], 1ll * C[i - 3][k - 2] * f[k][j] % MOD * 
												 f[i - k + 1][j] % MOD);
			dec(f[i][j], 1ll * C[i - 3][k - 2] * (MOD + f[k][j] -  f[k][j - 1]) % MOD *
												 (MOD + f[i - k + 1][j] - f[i - k + 1][j - 1]) % MOD);

		}
	REP(i, 0, 12) g[1][i] = 1;
	REP(i, 2, n) REP(j, 1, 12) REP(k, 1, i - 1)
		inc(g[i][j], 1ll * C[i - 2][k - 1] * g[k][j] % MOD * f[i - k + 1][j] % MOD);
	cout << (MOD + calc(n, k) - calc(n, k - 1)) % MOD << endl;
	return 0;
}
