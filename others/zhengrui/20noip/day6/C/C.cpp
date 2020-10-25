#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cstring>
#include <cmath>
#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 1e5 + 10;

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

int n, p, B;

int solve(int s)
{
	if (s > n) return 0;
	const int MOD = p;
	static int f[maxn], g[maxn], G[maxn];
	REP(i, 1, n) f[i] = 0;f[0] = 1;
	int B = max(::B, s - 1);
	REP(i, s, B)
		REP(j, i, n) f[j] = (f[j] + f[j - i]) % MOD;
	memset(g, 0, sizeof g);
	memset(G, 0, sizeof G);
	g[0] = G[0] = 1;
	REP(i, 1, n / B)
	{
		REP(j, 0, n)
		{
			if (j >= i) g[j] = (g[j] + g[j - i]) % MOD;
			if (j + i * (B + 1) <= n)
				G[j + i * (B + 1)] = (G[j + i * (B + 1)] + g[j]) % MOD;
		}
	}
	i64 ans = 0;
	REP(i, 0, n) ans = (ans + 1ll * f[i] * G[n - i]) % MOD;
	return ans;
}

int x, y;

int main()
{
#ifdef CraZYali
	file("C");
#endif
	cin >> x >> y >> n >> p;
	B = sqrt(n);
	cout << (solve(x) - solve(y + 1) + p) % p << endl;
	return 0;
}
