#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 5000 + 10;

int n, p;
int invs[maxn];

int f1[maxn], f2[maxn];
vector <int> Div[maxn];

int main()
{
#ifdef CraZYali
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	cin >> n >> p;const int MOD = p;
	invs[0] = invs[1] = 1;REP(i, 2, n) invs[i] = 1ll * (MOD - MOD / i) * invs[MOD % i] % MOD;

	DEP(i, n, 1) REP(j, 1, n / i) Div[i * j].emplace_back(i);

	static int f[5001][5001];
	//f[i][j] = P(i \in subtree(j))

/*
	REP(i, 1, n)
	{
		f[i][i] = 1;
		i64 iv = invs[Div[i].size() - 1];
		for (int fi : Div[i]) if (fi ^ i)
		{
			for (int j : Div[fi])
				f[i][j] = (f[i][j] + iv * f[fi][j]) % MOD;
		}
	}
 */
	REP(i, 1, n) f[i][i] = 1;
	DEP(j, n, 1)
	{
		for (int fi = j; fi <= n; fi += j)
			for (int i = fi + fi; i <= n; i += fi)
			{
				i64 iv = invs[Div[i].size() - 1];
				f[i][j] = (f[i][j] + iv * f[fi][j]) % MOD;
			}
		i64 res = 0;
		for (int i = j; i <= n; i += j) res += f[i][j];
		f1[j] = res % MOD;
	}
	/*
	REP(i, 1, n)
	{
		i64 res = 0;
		for (int j = i; j <= n; j += i) res += f[j][i];
		f1[i] = res % MOD;
	}
	*/
	REP(j, 1, n) REP(k, j, n)
	{
		int G = __gcd(j, k);
		static int g[maxn];
		for (int l : Div[G]) g[l] = 1ll * f[j][l] * f[k][l] % MOD;
		for (int r : Div[G]) for (int l : Div[r]) if (l ^ r)
			g[l] = (g[l] - 1ll * g[r] * f[r][l] % MOD * f[r][l]) % MOD;
		for (int l : Div[G]) for (int i : Div[l])
			f2[i] = (f2[i] + ((j != k) + 1ll) * f[l][i] * g[l]) % MOD;
	}
#ifdef CraZYali
	REP(i, 1, n) printf("%d%c", f1[i], i == end_i ? '\n' : ' ' );
	REP(i, 1, n) printf("%d%c", (MOD + f2[i]) % MOD, i == end_i ? '\n' : ' ' );
#endif
	// static int g[501][501][501];
	// g[j][k][l] = P(lca(j, k) = l)

	/*
	   DEP(l, n, 1) zhen de shi mei de ma 
	   {
	   for (int j = l; j <= n; j += l) for (int k = l; k <= n; k += l)
	   g[j][k][l] = 1ll * f[j][l] * f[k][l] % MOD;
	   for (int r = l + l; r <= n; r += l) // real lca
	   for (int j = r; j <= n; j += r) for (int k = r; k <= n; k += r)
	   {
	   g[j][k][l] = (g[j][k][l] - 1ll * g[j][k][r] * f[r][l] % MOD * f[r][l]) % MOD;
	   }
	   }
	   REP(i, 1, n)
	   {
	   i64 res = 0;
	   for (int l = i; l <= n; l += i)
	   for (int j = l; j <= n; j += l) for (int k = l; k <= n; k += l)
	   (res += 1ll * f[l][i] * g[j][k][l]) %= MOD;
	   f2[i] = res % MOD;
	   }
	 */

	i64 ans = 0;
	REP(i, 1, n) (ans += 1ll * n * f1[i] - f2[i]) %= MOD;
	cout << (ans + MOD) * 2 % MOD << endl;

	return 0;
}
