/*
	Problem:	A.cpp
	Time:		2020-02-18 13:00
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <ctime>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>
#define i64 long long
using namespace std;
const int maxn = 1e6 + 10;
int MOD;

inline int add(int x, int y) {register int res = x + y;return res >= MOD ? res - MOD : res;}
inline int sub(int x, int y) {register int res = x - y;return res <    0 ? res + MOD : res;}
inline i64 mul(i64 x, int y) {register i64 res = x * y;return res >= MOD ? res % MOD : res;}
inline void inc(int &x, int y) {x += y;if (x >= MOD) x -= MOD;}

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

int prime[maxn], cnt[maxn], p_cnt, bin[114];
bool notp[maxn];

int g[maxn], f[maxn], sf[maxn];

void init(const int n = maxn - 10)
{
	bin[0] = 1;
	REP(i, 1, 113) bin[i] = mul(2, bin[i-1]);
	REP(i, 2, n)
	{
		if (!notp[i]) cnt[prime[++p_cnt] = i] = 1;
		REP(j, 1, p_cnt)
		{
			int tmp = i * prime[j];if (tmp > n) break;
			notp[tmp] = 1;
			if (i % prime[j]) cnt[tmp] = cnt[i] + 1;
			else {cnt[tmp] = cnt[i];break;}
		}
	}
	REP(i, 2, n)
	{
		for (int j = i; j <= n; j += i) inc(g[j], bin[cnt[i - 1]]);
		f[i + 1] = add(f[i], g[i]);
		sf[i] = add(sf[i-1], f[i]);
	}
	const int tests = 0;
	REP(i, 1, tests) printf("%d%c", f[i], i == end_i ? '\n' : ' ');
	REP(k, 1, tests)
	{
		int res = 0;
		REP(i, 1, k) REP(j, 1, k) res += (i * j / __gcd(i, j) + __gcd(i, j) < k);
		printf("%d%c", res, k == end_k ? '\n' : ' ');
	}
}

int main()
{
#ifdef CraZYali
	file("A");
#endif
	register int T = read<int>();
	MOD = read<int>();
	init();
	while (T--)
	{
		int n = read<int>();
		int ans = sub(1ll * n * n % MOD * n % MOD, sf[n]);
		cout << ans << '\n';
	}
	cerr << clock() * 1. / CLOCKS_PER_SEC << endl;
	return 0;
}
