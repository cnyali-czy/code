#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e5 + 10;
#define i64 long long
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

int n, p;

int f[maxn], g[maxn];
int solve(int S)
{
	if (S > n) return 0;
	const int MOD = p;
	REP(i, 0, n) f[i] = 0;
	f[0] = 1;f[S] = MOD - 1;
	REP(i, S + 1, n)
		DEP(j, n, i) f[j] = (f[j] + MOD - f[j - i]) % MOD;
	g[0] = 1;
	REP(m, 1, n)
	{
		int res = 0;
		REP(i, 0, m - 1) res = (res + 1ll * g[i] * f[m - i]) % MOD;
		if (res) res = MOD - res;
		g[m] = res;
	}
	return g[n];
}
int x, y;

int main()
{
#ifdef CraZYali
	file("C");
#endif
	cin >> x >> y >> n >> p;
	cout<< solve(x)<<endl;
	cout << (p + solve(x) - solve(y + 1)) % p << endl;
	return 0;
}
