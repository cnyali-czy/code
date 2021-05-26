#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <vector>
#include <iostream>
#include <cstdio>
#define i64 long long
#define u64 unsigned i64
#define poly vector <int>

using namespace std;
const int maxn = 2000 + 10, MOD = 924844033;

int n, k, fac[maxn];
i64 ans;

bool vis[maxn << 1];
void dfs(int x, int y)
{
	if (x == n)
	{
		ans += (y & 1 ? -1 : 1) * fac[n - y];
		return;
	}
	x++;
	dfs(x, y);
	if (x - k >= 1 && !vis[x - k])
	{
		vis[x - k] = 1;
		dfs(x, y + 1);
		vis[x - k] = 0;
	}
	if (x + k <= n && !vis[x + k])
	{
		vis[x + k] = 1;
		dfs(x, y + 1);
		vis[x + k] = 0;
	}
}

vector <int> G[maxn << 1];
inline void add(int x, int y) {G[x].emplace_back(y);G[y].emplace_back(x);}
int kzp;
void Dfs(int x)
{
	kzp++;
	vis[x] = 1;
//	printf("%d ", x);
	for (int y : G[x]) if (!vis[y]) Dfs(y);
}

int f[maxn << 1][maxn][2];
inline void inc(int &x, i64 y) {x = (x + y) % MOD;}

const u64 LIM = 17e18;
inline int deg(const poly &f) {return (int)f.size() - 1;}
poly operator * (poly a, poly b)
{
	int n = deg(a), m = deg(b);
	static u64 c[maxn];
	REP(i, 0, n) if (a[i]) REP(j, 0, m) if (b[j])
	{
		c[i + j] += (u64) a[i] * b[j];
		if (c[i + j] >= LIM) c[i + j] %= MOD;
	}
	a.resize(n + m + 1);
	REP(i, 0, n + m)
	{
		a[i] = c[i] % MOD;
		c[i] = 0;
	}
	return a;
}

int main()
{
#ifdef CraZYali
	freopen("2062.in", "r", stdin);
	freopen("2062.out", "w", stdout);
#endif
	cin >> n >> k;
	fac[0] = 1;REP(i, 1, n) fac[i] = 1ll * i * fac[i - 1] % MOD;

	/*
	dfs(0, 0);
	cout << (ans % MOD + MOD) % MOD << endl;
	puts("");
	*/

	f[0][0][0] = 1;
	REP(i, 0, n + n - k)
		REP(j, 0, i + 1 >> 1)
		{
			inc(f[i + 1][j][0], f[i][j][0] + f[i][j][1]);
			inc(f[i + 1][j + 1][1], f[i][j][0]);
		}
	ans = 0;
	REP(i, 1, n + n - k) vis[i] = 0;
	REP(i, 1, n)
	{
		if (i - k >= 1) add(i, i - k + n);
		if (i + k <= n) add(i, i + k + n);
	}
	poly F(1, 1);
	REP(i, 1, n + n - k) if (!vis[i])
	{
		kzp = 0;
		Dfs(i);
		poly G((kzp >> 1) + 1, 0);
		REP(j, 0, kzp >> 1)
		{
			G[j] = (f[kzp - 1][j][0] + f[kzp - 1][j][1]) % MOD;
			if (j & 1) G[j] = MOD - G[j];
		}
		F = F * G;
	}
	F.resize(n + 1);
	REP(i, 0, n) (ans += 1ll * F[i] * fac[n - i]) %= MOD;
	cout << ans << endl;
	return 0;
}
