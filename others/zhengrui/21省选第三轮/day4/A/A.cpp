#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>
#define poly vector <int>
#define bpoly vector <poly > 
#define i64 long long
#define u64 unsigned i64

using namespace std;
const int maxn = 400 + 5;

int n, k, p;
int fac[maxn], invs[maxn], Invs[maxn], bin[maxn][maxn], Bin[maxn][maxn];
void init(int n)
{
	const int MOD = p;
	REP(i, 0, n)
	{
		bin[i][0] = 1;
		REP(j, 1, n) bin[i][j] = 1ll * i * bin[i][j - 1] % MOD;
	}
	REP(i, 1, n) REP(j, 1, n) Bin[i][j] = bin[j][i];
	fac[0] = invs[0] = Invs[0] = 1;
	fac[1] = invs[1] = Invs[1] = 1;
	REP(i, 2, n)
	{
		fac[i] = 1ll * i * fac[i - 1] % MOD;
		invs[i] = 1ll * (MOD - MOD / i) * invs[MOD % i] % MOD;
		Invs[i] = 1ll * invs[i] * Invs[i - 1] % MOD;
	}
}

i64 Ans, K;int a[maxn];
void dfs(int x)
{
	if (x == n)
	{
		static int pmax[maxn], smin[maxn];
		pmax[1] = a[1];REP(i, 2, n) pmax[i] = max(a[i], pmax[i - 1]);
		smin[n] = a[n];DEP(i, n - 1, 0) smin[i] = min(a[i], smin[i + 1]);
		int flg = 1;
		REP(i, 1, n - 1) if (pmax[i] == smin[i + 1]) {flg = 0;break;}
		Ans += flg;return;
	}
	x++;
	REP(i, 1, K) a[x] = i, dfs(x);
}

int f[404][404];
i64 F(int _)
{
	return f[n][_];
	K = _;
	Ans = 0;
	dfs(0);
	return Ans;
}

const u64 LIM = 14e18;
inline int deg(const poly &f) {return (int)f.size() - 1;}

const int p1 = (5 << 25) + 1, p2 = (7 << 26) + 1, p3 = 998244353;
const int maxN = 1024;
namespace Poly
{
	i64 power_pow(i64 base, int b, const int MOD)
	{
		i64 ans = 1;
		while (b)
		{
			if (b & 1) (ans *= base) %= MOD;
			if (b >>= 1) (base *= base) %= MOD;
		}
		return ans;
	}
#define inv(x, P) power_pow(x, P - 2, P)
	struct num
	{
		u64 v1, v2, v3;
		num() {}
		inline num(const u64 &v1, const u64 &v2, const u64 &v3) : v1(v1), v2(v2), v3(v3) {}
		inline num operator + (const num &B) {return num(v1 + B.v1, v2 + B.v2, v3 + B.v3);}
		inline num operator - (const num &B) {return num(v1 - B.v1, v2 - B.v2, v3 - B.v3);}
		inline num operator * (const num &B) {return num(v1 * B.v1 % p1, v2 * B.v2 % p2, v3 * B.v3 % p3);}
		inline int real()
		{
			static const int MOD = p;

			static const i64 mod_1_2 = 1ll * p1 * p2, moded_1_2 = mod_1_2 % MOD;
			static const int inv_1 = inv(p1, p2), inv_2 = inv(mod_1_2 % p3, p3);

			u64 x = (v2 + p2 - v1) % p2 * inv_1 % p2 * p1 + v1;
			return ((v3 + p3 - x % p3) * inv_2 % p3 * moded_1_2 + x) % MOD;
		}
	};
	const num M(p1, p2, p3);
	void NTT(num a[], int n, int flg)
	{
		if (flg < 0) reverse(a + 1, a + n);
		static int R[maxN];

		REP(i, 1, n - 1)
		{
			R[i] = (R[i >> 1] >> 1) | (i & 1 ? (n >> 1) : 0);
			if (i < R[i]) swap(a[i], a[R[i]]);
		}
		static bool vis[30];
		static num pool[maxN << 1 | 10], *cur = pool, *w[30];
		for (int i = 1, c = 0; i < n; i <<= 1, c++)
		{
			//	static num w[maxn];

			if (!vis[c])
			{
				vis[c] = 1;
				w[c] = cur;cur += i;
				w[c][0] = num(1, 1, 1);
				num wn = num(
						power_pow(3, (p1 - 1) >> (c + 1), p1), 
						power_pow(3, (p2 - 1) >> (c + 1), p2), 
						power_pow(3, (p3 - 1) >> (c + 1), p3)
						);
				REP(l, 1, i - 1) w[c][l] = w[c][l - 1] * wn;
			}
			for (int k = 0; k < n; k += i + i)
				for (int l = 0; l < i; l++)
				{
					num x = a[k + l], y = a[k + l + i] * w[c][l];
					a[k + l] = x + y;
					a[k + l + i] = x + M - y;
				}
		}
		REP(i, 0, n - 1) a[i].v1 %= p1, a[i].v2 %= p2, a[i].v3 %= p3;
		if (flg < 0)
		{
			num iv(inv(n, p1), inv(n, p2), inv(n, p3));
			REP(i, 0, n - 1) a[i] = a[i] * iv;
		}
	}
}
using Poly :: NTT;
using Poly :: num;
bpoly fix(bpoly f, int n, int m)
{
	f.resize(n + 1);
	REP(i, 0, n) f[i].resize(m + 1);
	return f;
}
void DFT(num f[1024][1024], int ln, int lm, int flg)
{
	static num b[1024];
	REP(i, 0, ln - 1) NTT(f[i], lm, flg);
	REP(j, 0, lm - 1)
	{
		REP(i, 0, ln - 1) b[i] = f[i][j];
		NTT(b, ln, flg);
		REP(i, 0, ln - 1) f[i][j] = b[i];
	}
}
bpoly sqr(bpoly f)
{
	int n = f.size() - 1, m = f[0].size() - 1;
	int ln = 1;while (ln <= n + n) ln <<= 1;
	int lm = 1;while (lm <= m + m) lm <<= 1;
	static num a[1024][1024];
	REP(i, 0, ln - 1) REP(j, 0, lm - 1) a[i][j] = num(0, 0, 0);
	REP(i, 0, n) REP(j, 0, m) a[i][j] = num(f[i][j] % p1, f[i][j] % p2, f[i][j] % p3);

	DFT(a, ln, lm, 1);
	REP(i, 0, ln - 1) REP(j, 0, lm - 1) a[i][j] = a[i][j] * a[i][j];
	DFT(a, ln, lm, -1);
	REP(i, 0, n) REP(j, 0, m) f[i][j] = a[i][j].real();
	return f;
}
bpoly operator * (bpoly f, bpoly g)
{
	int n1 = f.size() - 1, n2 = g.size() - 1;
	int m1 = f[0].size() - 1, m2 = g[0].size() - 1;
	int ln = 1;while (ln <= n1 + n2) ln <<= 1;
	int lm = 1;while (lm <= m1 + m2) lm <<= 1;
	static num a[1024][1024], b[1024][1024];
	REP(i, 0, ln - 1) REP(j, 0, lm - 1) a[i][j] = b[i][j] = num(0, 0, 0);
	REP(i, 0, n1) REP(j, 0, m1)
		a[i][j] = num(f[i][j] % p1, f[i][j] % p2, f[i][j] % p3);
	REP(i, 0, n2) REP(j, 0, m2)
		b[i][j] = num(g[i][j] % p1, g[i][j] % p2, g[i][j] % p3);

	DFT(a, ln, lm, 1);DFT(b, ln, lm, 1);
	REP(i, 0, ln - 1) REP(j, 0, lm - 1) a[i][j] = a[i][j] * b[i][j];
	DFT(a, ln, lm, -1);
	f.resize(n1 + n2 + 1);
	REP(i, 0, n1 + n2)
	{
		f[i].resize(m1 + m2 + 1);
		REP(j, 0, m1 + m2) f[i][j] = a[i][j].real();
	}
	return f;
}
bpoly operator + (bpoly f, const bpoly &g)
{
	static const int MOD = p;
	if (f.size() < g.size()) f.resize(g.size());
	REP(i, 0, g.size() - 1)
	{
		if (f[i].size() < g[i].size()) f[i].resize(g[i].size());
		REP(j, 0, deg(g[i])) f[i][j] = (f[i][j] + g[i][j]) % MOD;
	}
	return f;
}
int main()
{
#ifdef CraZYali
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	cin >> n >> k >> p;const int MOD = p;
	init(n);

	/*
	REP(i, 1, n) REP(j, 1, n)
	{
		u64 fk = 0;
		REP(l, 0, i) REP(z, 0, j + 1)
		{
			fk += (u64)Bin[i - l][z] * f[l][j + 1 - z];
			if (fk >= LIM) fk %= MOD;
		}
		REP(l, 0, i) REP(z, 0, j)
		{
			fk += 2llu * Bin[i - l][z] * (MOD - f[l][j - z]);
			if (fk >= LIM) fk %= MOD;
		}
		REP(l, 0, i) REP(z, 0, j - 1)
		{
			fk += (u64)Bin[i - l][z] * f[l][j - 1 - z];
			if (fk >= LIM) fk %= MOD;
		}

		f[i][j] = (Bin[i][j] + MOD - fk % MOD) % MOD;
		if (i % 50 == 0) cerr << i << ' ' << j << endl;
	}
	REP(i, 1, n) REP(j, 1, n) printf("%d%c", f[i][j], j == end_j ? '\n' : ' ' );
	puts("");
	*/

//	bpoly B(n + 1, poly(n + 1, 0));
	bpoly C(n + 1, poly(n + 1, 0));REP(i, 1, n) REP(j, 0, n)
	{
		i64 t = Bin[i][j + 1] - 2ll * Bin[i][j] + (j ? Bin[i][j - 1] : 0);
		C[i][j] = MOD - t % MOD;
	}
	/*
	bpoly Res(1, poly(1, 1)), cur = C;
	REP(i, 1, n)
	{
		Res = Res + cur;
		cur = fix(cur * C, n, n);
	}
	*/
	static num R[1024][1024], cur[1024][1024], B[1024][1024];
	int ln = 1; while (ln <= n + n) ln <<= 1;
	REP(i, 0, ln - 1) REP(j, 0, ln - 1)
		R[i][j] = B[i][j] = cur[i][j] = num(0, 0, 0);R[0][0] = num(1, 1, 1);
	REP(i, 0, n) REP(j, 0, n) cur[i][j] = num(C[i][j] % p1, C[i][j] % p2, C[i][j] % p3);
	REP(i, 1, n) REP(j, 1, n) B[i][j] = num(Bin[i][j] % p1, Bin[i][j] % p2, Bin[i][j] % p3);

	for (int b = n; b; )
	{
		DFT(R, ln, ln, 1);DFT(cur, ln, ln, 1);
		REP(i, 0, ln - 1) REP(j, 0, ln - 1)
		{
			R[i][j] = R[i][j] * (num(1, 1, 1) + cur[i][j]);
			cur[i][j] = cur[i][j] * cur[i][j];
			if (R[i][j].v1 >= p1) R[i][j].v1 %= p1;
			if (R[i][j].v2 >= p2) R[i][j].v2 %= p2;
			if (R[i][j].v3 >= p3) R[i][j].v3 %= p3;
			
			if (cur[i][j].v1 >= p1) cur[i][j].v1 %= p1;
			if (cur[i][j].v2 >= p2) cur[i][j].v2 %= p2;
			if (cur[i][j].v3 >= p3) cur[i][j].v3 %= p3;
		}
		DFT(R, ln, ln, -1);DFT(cur, ln, ln, -1);
		REP(i, 0, n) REP(j, 0, n)
		{
			int x = R[i][j].real();R[i][j] = num(x % p1, x % p2, x % p3);
			x = cur[i][j].real();cur[i][j] = num(x % p1, x % p2, x % p3);
		}
		REP(i, n + 1, ln - 1) REP(j, n + 1, ln - 1) R[i][j] = cur[i][j] = num(0, 0, 0);
		b >>= 1;
		cerr << b << endl;
		REP(i, 0, n) REP(j, 0, n) printf("%d%c", R[i][j].real(), j == end_j ? '\n' : ' ' );
	}
	DFT(R, ln, ln, 1);DFT(B, ln, ln, 1);
	REP(i, 0, ln - 1) REP(j, 0, ln - 1) R[i][j] = R[i][j] * B[i][j];
	DFT(R, ln, ln, -1);
//	Res = fix(Res * B, n, n);
//	REP(i, 1, n) REP(j, 1, n) f[i][j] = Res[i][j];
	REP(i, 1, n) REP(j, 1, n) f[i][j] = R[i][j].real();
	REP(i, 1, n) REP(j, 1, n) printf("%d%c", f[i][j], j == end_j ? '\n' : ' ' );

	if (k <= n)
	{
		cout << F(k) << '\n';
		return 0;
	}
	i64 ans = 0;
	REP(i, 0, n)
	{
		i64 res = 1;
		REP(j, 0, n) if (i ^ j)
		{
			(res *= (k - j)) %= MOD;
			if (i < j) (res *= -invs[j - i]) %= MOD;
			else (res *= invs[i - j]) %= MOD;
		}
		(ans += res * F(i)) %= MOD;
	}
	cout << (ans + MOD) % MOD << endl;
	return 0;
}
