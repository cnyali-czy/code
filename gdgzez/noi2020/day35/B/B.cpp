#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <iostream>
#include <cstdio>
#define poly vector <int>
#define i64 long long

using namespace std;
const int N = 16, maxn = 1 << N, MOD = 998244353, inv2 = MOD + 1 >> 1;

inline void inc(int &x, int y) {x += y;if (x >= MOD) x -= MOD;}
inline void dec(int &x, int y) {x -= y;if (x <    0) x += MOD;}

i64 power_pow(i64 base, int b)
{
	i64 ans = 1;
	while (b)
	{
		if (b & 1) (ans *= base) %= MOD;
		(base *= base) %= MOD;
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

void FWT(poly &a, int n, int flag)
{
	int len = 1 << n;
	REP(i, 0, n - 1)
	{
		int i2 = 1 << i;
		for (int k = 0; k < len; k += i2 + i2)
			REP(l, 0, i2 - 1)
				if (flag > 0)	inc(a[k + l + i2], a[k + l]);
				else			dec(a[k + l + i2], a[k + l]);
	}
}
int cnt[maxn];
int invs[N + 10];
poly Ln(poly f)
{
	static poly t[N + 10];
	int len = f.size(), n = 0;
	while ((1 << n) ^ len) n++;
	invs[0] = invs[1] = 1;
	REP(i, 2, n) invs[i] = 1ll * (MOD - MOD / i) * invs[MOD % i] % MOD; 
	REP(i, 0, n) t[i].clear(), t[i].resize(len);
	REP(i, 0, len - 1) t[cnt[i]][i] = f[i];
	REP(i, 0, n) FWT(t[i], n, 1);
	static int a[N + 10];
	REP(i, 0, len - 1)
	{
		REP(j, 0, n) a[j] = t[j][i];
		t[0][i] = 0;
		REP(j, 1, n)
		{
			int res = 1ll * j * a[j] % MOD;
			REP(k, 1, j - 1) res = (res - 1ll * k * t[k][i] % MOD * a[j - k]) % MOD;
			if (res < 0) res += MOD;
			t[j][i] = 1ll * invs[j] * res % MOD;
		}
	}
	REP(i, 0, n) FWT(t[i], n, -1);
	REP(i, 0, len - 1) f[i] = t[cnt[i]][i];
	return f;
}

poly mem[maxn];

int n, m;
int G[N][N], bin[N * N + 10];

inline poly operator * (const poly &a, const poly &b)
{
	int len = a.size(), n = 0;
	while ((1 << n) ^ len) n++;
	static poly A[N + 1], B[N + 1], C[N + 1];
	poly c(len);
	REP(i, 0, n)
	{
		A[i].clear();A[i].resize(len);
		B[i].clear();B[i].resize(len);
		C[i].clear();C[i].resize(len);
	}
	REP(i, 0, len - 1)
	{
		A[cnt[i]][i] = a[i];
		B[cnt[i]][i] = b[i];
	}
	REP(i, 0, n)
	{
		FWT(A[i], n, 1);
		FWT(B[i], n, 1);
	}
	REP(a, 0, n) REP(b, 0, n - a)
		REP(i, 0, len - 1) C[a + b][i] = (C[a + b][i] + 1ll * A[a][i] * B[b][i]) % MOD;
	REP(i, 0, n)
		FWT(C[i], n, -1);
	REP(i, 0, len - 1) c[i] = C[cnt[i]][i];
	return c;
}

int main()
{
#ifdef CraZYali
	file("B");
#endif
	REP(i, 0, maxn - 1) cnt[i] = cnt[i >> 1] + (i & 1);
	bin[0] = 1;
	REP(i, 1, N * N) bin[i] = (bin[i - 1] << 1) % MOD;
	REP(Case, 1, read<int>())
	{
		cin >> n >> m;
		REP(i, 0, n - 1) REP(j, 0, n - 1) G[i][j] = 0;
		const int lim = (1 << n) - 1;
		while (m--)
		{
			int x = read<int>() - 1, y = read<int>() - 1;
			G[x][y] = G[y][x] = 1;
		}
		if (n == 1)
		{
			puts("0");
			continue;
		}
		poly g(1 << n), h(1 << n);
		REP(S, 0, lim)
		{
			int res = 0;
			REP(i, 0, n - 1) if (S >> i & 1)
				REP(j, i + 1, n - 1) if (S >> j & 1) res += G[i][j];
			g[S] = bin[res];
		}
		poly f = Ln(g);
		mem[0] = f;
		REP(i, 0, n - 1)
		{
			REP(j, 0, lim) g[j] = 0;
			REP(j, 0, lim) if (j >> i & 1)
			{ 
				inc(g[j ^ (1 << i)], f[j]);
				f[j] = 0; 
			}
			g = Ln(g);
			REP(j, 0, lim) if (!(j >> i & 1))
				inc(f[j ^ (1 << i)], g[j]);
			mem[i + 1] = f;
		}
		poly F, G, H, Empty(lim + 1, 0);
		G = H = mem[n];
		DEP(i, n - 1, 0)
		{
			g = h = Empty;
			REP(j, 0, lim) if (j >> i & 1)
			{
				g[j ^ (1 << i)] = H[j];
				h[j ^ (1 << i)] = mem[i][j];
			}
			g = g * h;
			REP(j, 0, lim) if (!(j >> i & 1))
				H[j ^ (1 << i)] = g[j];

			F = G;
			g = Empty;
			REP(j, 0, lim) if (j >> i & 1)
				g[j ^ (1 << i)] = G[j];
			g = g * h;
			REP(j, 0, lim) if (!(j >> i & 1))
				G[j ^ (1 << i)] = g[j];

			g = h = Empty;
			REP(j, 0, lim) if (j >> i & 1)
			{
				g[j ^ (1 << i)] = F[j];
				h[j ^ (1 << i)] = G[j];
			}
			g = g * h;	
	
			REP(j, 0, lim) if (!(j >> i & 1))
				inc(H[j ^ (1 << i)], g[j]);
		}
		printf("%d\n", 1ll * inv2 * (G[lim] + H[lim]) % MOD);
//		cout << f[lim] << endl;
	}
	return 0;
}
