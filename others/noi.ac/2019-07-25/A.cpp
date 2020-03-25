/*
	Problem:	A.cpp
	Time:		2020-03-22 11:01
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cstdio>
#define i64 long long
using namespace std;
const int maxn = 45 + 5, MOD = 1e9 + 7;
inline int add(int x, int y) {x += y;return x >= MOD ? x - MOD : x;}
inline int sub(int x, int y) {x -= y;return x <    0 ? x + MOD : x;}
inline i64 mul(i64 x, int y) {x *= y;return x >= MOD ? x % MOD : x;}
inline void inc(int &x, int y) {x += y;if (x >= MOD) x -= MOD;}

int power_pow(int base, int b)
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

int n, m, k;
int p[maxn], q[maxn];

bool vis[maxn][maxn];
void dfs(int x, int y)
{
	if (vis[x][y]) return;
	vis[x][y] = 1;
	dfs(p[x], q[y]);
}

int str[maxn][maxn], fac[maxn], Inv[maxn], iv[maxn];
struct __init__
{
	__init__(const int n = 40)
	{
		str[0][0] = 1;
		REP(i, 1, n) REP(j, 0, i) str[i][j] = add(j ? str[i - 1][j - 1] : 0, mul(i - 1, str[i - 1][j]));
		fac[0] = 1;
		REP(i, 1, n) fac[i] = mul(fac[i - 1], i);
		iv[0] = iv[1] = Inv[0] = Inv[1] = 1;
		REP(i, 2, n)
		{
			iv[i] = mul(MOD - MOD / i, iv[MOD % i]);
			Inv[i] = mul(Inv[i - 1], iv[i]);
		}
	}
}__INIT__;

int ans;
int bin[maxn * maxn], g[maxn][maxn];

vector <vector <int> > cn, cm, *c;

vector <int> cur;
void split(int x, int las)
{
	if (!x)
	{
		c -> emplace_back(cur);
		return;
	}
	cur.emplace_back(x);
	c -> emplace_back(cur);
	cur.pop_back();
	REP(i, las, x / 2)
	{
		cur.emplace_back(i);
		split(x - i, i);
		cur.pop_back();
	}
}

int cnt[maxn];
int calc(const vector <int> &A, int n)
{
	int res = fac[n];
	for (auto i : A)
	{
		cnt[i] = 0;
		res = mul(res, iv[i]);
	}
	for (auto i : A) cnt[i]++;
	for (auto i : A) if (cnt[i])
	{
		res = mul(res, Inv[cnt[i]]);
		cnt[i] = 0;
	}
	return res;
}

int main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();m = read<int>();k = read<int>();
	bin[0] = 1;
	REP(i, 1, n * m) bin[i] = mul(bin[i - 1], k);
	REP(i, 1, n) REP(j, 1, m) g[i][j] = __gcd(i, j);
	c = &cn;
	split(n, 1);
	c = &cm;
	split(m, 1);
	int ans = 0;
	for (const auto &N : cn)
		for (const auto &M : cm)
		{
			int res = 0;
			for (auto i : N) for (auto j : M) res += g[i][j];
#ifdef CraZYali
			for (auto i : N) printf("%d ", i);puts("");		
			for (auto i : M) printf("%d ", i);puts("");		
			printf("%d %d %d\n", calc(N, n), calc(M, m), res);
			puts("");
#endif
			inc(ans, 1ll * calc(N, n) * calc(M, m) % MOD * bin[res] % MOD);
		}
	cout << 1ll * ans * Inv[n] % MOD * Inv[m] % MOD << '\n';
	return 0;
}
