/*
	Problem:	count.cpp
	Time:		2021-01-23 22:37
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cassert>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 20 + 5, maxm = maxn * maxn, MOD = 998244353;
//1e9 + 7;

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

int n, m, u[maxm], v[maxm];

int fa[maxn];
int find(int x) {return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);}
void uni(int x, int y) {fa[find(x)] = find(y);}

namespace bf
{
	void work()
	{
		int ans = 0;
		REP(S, 0, (1 << m) - 1) if (__builtin_popcount(S) >= n - 1)
		{
			REP(i, 1, n) fa[i] = i;
			REP(i, 1, m) if (S >> (i - 1) & 1) uni(u[i], v[i]);
			REP(i, 2, n) if (find(i) ^ find(1)) goto gg;
			ans++;
gg:;
		}
		cout << ans << endl;
	}
}
int cnt[1 << 20];

#define poly vector <int>
int invs[maxn];

void init(int n)
{
	REP(i, 1, (1 << n) - 1) cnt[i] = cnt[i >> 1] + (i & 1);
	invs[0] = invs[1] = 1;REP(i, 2, n) invs[i] = 1ll * invs[MOD % i] * (MOD - MOD / i) % MOD;
}
inline int deg(const poly &f) {return (int)f.size() - 1;}
poly Exp(poly f)
{
	int n = deg(f);
	assert(!f[0]);
	REP(i, 0, n) f[i] = 1ll * f[i] * i % MOD;
	poly g(n + 1, 0);g[0] = 1;
	REP(N, 0, n - 1)
	{
		int res = 0;
		REP(i, 0, N) res = (res + 1ll * g[i] * f[N - i + 1]) % MOD;
		g[N + 1] = 1ll * res * invs[N + 1] % MOD;
	}
	return g;
}
poly Ln(poly f)
{
	int n = deg(f);
	if (f[0] ^ 1)
	{
		cerr << "Ln Error! " << f[0] << endl;
		REP(i, 0, n) fprintf(stderr, "%d%c", f[i], i == end_i ? '\n' : ' ');
	}
//	assert(f[0] == 1);
	poly g(n + 1, 0);
	REP(N, 0, n - 1)
	{
		int res = f[N + 1] * (N + 1ll) % MOD;
		REP(i, 0, N - 1)
			res = (res - 1ll * g[i] * f[N - i]) % MOD;
		g[N] = (res + MOD) % MOD;
	}
	DEP(i, n, 1) g[i] = 1ll * invs[i] * g[i - 1] % MOD;g[0] = 0;
	return g;
}

void fwt_or(poly &f, int flag)
{
	int N = f.size();
	int n = 0;while ((1 << n) ^ N) n++;
	if (flag == 1)
	{
		REP(i, 0, n - 1) REP(j, 0, N - 1) if (j >> i & 1) (f[j] += f[j ^ (1 << i)]) %= MOD;
	}
	else
	{
		REP(i, 0, n - 1) REP(j, 0, N - 1) if (j >> i & 1) (f[j] += MOD - f[j ^ (1 << i)]) %= MOD;
//		DEP(i, n - 1, 0) DEP(j, N - 1, 0) if (j >> i & 1) (f[j] += MOD - f[j ^ (1 << i)]) %= MOD;
	}
}
void fwt_or(int f[], int n, int flag)
{
	poly g(1 << n);
	REP(i, 0, (1 << n) - 1) g[i] = f[i];
	fwt_or(g, flag);
	REP(i, 0, (1 << n) - 1) f[i] = g[i];
}

poly BitLn(poly f)
{
	int N = f.size(), n = 0;while ((1 << n) ^ N) n++;
	static int mem[21][1 << 20];
	REP(i, 0, n)
	{
		REP(j, 0, N - 1) mem[i][j] = (cnt[j] == i ? f[j] : 0);
		fwt_or(mem[i], n, 1);
	}
	REP(i, 0, N - 1)
	{
		poly g(n + 1, 0);
		REP(j, 0, n) g[j] = mem[j][i];
//		g[0]++;
		g = Ln(g);
		REP(j, 0, n) mem[j][i] = g[j];
	}
	REP(i, 0, n) fwt_or(mem[i], n, -1);
	REP(i, 0, N - 1) f[i] = mem[cnt[i]][i];
	return f;
}

int main()
{
#ifdef CraZYali
	file("count");
#endif
	n = read<int>();m = read<int>();
	REP(i, 1, m) u[i] = read<int>(), v[i] = read<int>();
	bf :: work();
	DEBUG;

	init(n);
	const int N = 1 << n;
	poly f(N, 0);

	REP(S, 0, N - 1)
	{
		int res = 1;
		REP(i, 1, m) if ((S >> (u[i] - 1) & 1) && (S >> (v[i] - 1) & 1))
			(res <<= 1) %= MOD;
		f[S] = res;
	}

	cout << BitLn(f)[N - 1] << endl;

	return 0;
}
