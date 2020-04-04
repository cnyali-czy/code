/*
	Problem:	5325-new.cpp
	Time:		2020-04-04 20:27
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e7 + 10, MOD = 1e9 + 7, maxP = 7e5, inv2 = MOD + 1 >> 1, inv3 = (MOD + 1) / 3, inv6 = 1ll * inv2 * inv3 % MOD;
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
#define i64 long long
inline int add(int x, const int &y) {return (x += y) >= MOD ? x - MOD : x;}
inline int sub(int x, const int &y) {return (x -= y) <    0 ? x + MOD : x;}
inline i64 mul(i64 x, const int &y) {return (x *= y) >= MOD ? x % MOD : x;}
inline void inc(int &x, const int &y) {x += y;if (x >= MOD) x -= MOD;}
inline void dec(int &x, const int &y) {x -= y;if (x <    0) x += MOD;}
inline int upd(const i64 &x) {return x >= MOD ? x % MOD : x;}

int prime[maxP], sg[maxn], lp, p_cnt, N;
i64 n;
bool notp[maxn];
int G[40], H[maxP][40];

void init(int N)
{
	::N = N;
	sg[1] = 1;
	REP(i, 2, N)
	{
		if (!notp[i]) sg[prime[++p_cnt] = i] = i - 1;
		REP(j, 1, p_cnt)
		{
			int tmp = i * prime[j];if (tmp > N) break;
			notp[tmp] = 1;
			if (i % prime[j])
				sg[tmp] = sg[i] * (prime[j] - 1);
			else
			{
				sg[tmp] = sg[i] * prime[j];
				break;
			}
		}
		sg[i] = add(sg[i-1], mul(i, sg[i]));
	}
	G[0] = 1;
	REP(i, 1, p_cnt)
	{
		i64 p = prime[i];
		if (p * p > n)
		{
			lp = i - 1;
			break;
		}
		H[i][0] = 1;
		for (int k = 1; p <= n; p *= prime[i], k++)
		{
			G[k] = (prime[i] - 1ll) * upd(p / prime[i]) % MOD * upd(p) % MOD;
			H[i][k] = upd(p) * (upd(p) - 1ll) % MOD;
			REP(c, 0, k - 1) dec(H[i][k], 1ll * G[k - c] * H[i][c] % MOD);
		}
	}
}

namespace SG
{
	int mem[maxn];
	inline int S(i64 n)
	{
		if (n <= N) return sg[n];
		int &res = mem[::n / n];
		if (res) return res;
		res = upd(n) * (upd(n) + 1ll) % MOD * (upd(n) << 1 | 1) % MOD * inv3 % MOD;
		for (i64 i = 2, j; i <= n; i = j + 1)
		{
			j = n / (n / i);
			dec(res, upd(i + j) * (upd(j - i) + 1ll) % MOD * S(n / i) % MOD);
		}
		res = 1ll * res * inv2 % MOD;
		return res;
	}
}
using SG::S;

i64 ans;
void dfs(i64 d, int H, int lst)
{
	ans += 1ll * H * S(n / d) % MOD;
	if (lst == lp) return;
	REP(i, lst + 1, lp)
	{
		if (1ll * prime[i] * prime[i] > n / d) break;
		i64 dd = d * prime[i] * prime[i];
		for (int k = 2; dd <= n; k++, dd *= prime[i])
			dfs(dd, 1ll * H * ::H[i][k] % MOD, i);
	}
}
int main()
{
#ifdef CraZYali
	file("5325-new");
#endif
	n = read<i64>();
	init(max((int)100, (int)(2 * pow(n, 2. / 3))));
	dfs(1, 1, 0);
	cout << ans % MOD << endl;
	return 0;
}
