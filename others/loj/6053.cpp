#define REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;
const int maxn = 4700000, MOD = 1e9 + 7, inv2 = MOD + 1 >> 1;
#define i64 long long
inline int add(int x, int y) {return (x += y) >= MOD ? x - MOD : x;}
inline int sub(int x, int y) {return (x -= y) <    0 ? x + MOD : x;}
inline void inc(int &x, int y) {x += y;if (x >= MOD) x -= MOD;}
inline void dec(int &x, int y) {x -= y;if (x <    0) x += MOD;}

template <typename T> T read()
{
	T ans(0), flag(1);
	char c(getchar());
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

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}
i64 n;
int prime[maxn], phi[maxn], p_cnt, N, sg[maxn], mu[maxn], smu[maxn];
vector <int> H[maxn];
bool notp[maxn];
//G(x) = phi(x)
//F(p ^ k) = p xor k
void init(int N)
{
	::N = N;
	phi[1] = sg[1] = 1;
	mu[1] = smu[1] = 1;
	REP(i, 2, N)
	{
		if (!notp[i]) phi[prime[++p_cnt] = i] = i - 1, mu[i] = -1;
		REP(j, 1, p_cnt)
		{
			int tmp = i * prime[j];if (tmp > N) break;
			notp[tmp] = 1;
			if (i % prime[j])
			{
				phi[tmp] = phi[i] * (prime[j] - 1);
				mu[tmp] = -mu[i];
			}
			else
			{
				phi[tmp] = phi[i] * prime[j];
				break;
			}
		}
		sg[i] = add(sg[i - 1], phi[i]);
		smu[i] = smu[i - 1] + mu[i];
	}
	cerr << "p_cnt = " << p_cnt << endl;
	REP(i, 1, p_cnt)
	{
		int p = prime[i];
		vector <int> G(1, 1);
		G.emplace_back(p - 1);
		//G[j]		= phi(p ^ j)
		
		//H[i][j]	= H(p ^ j)
		//			= p ^ {j - 1} (p - 1)
		H[i].emplace_back(1);
		if (i == 1)	H[i].emplace_back(2);
		else 		H[i].emplace_back(0);
		i64 lim = n / p;
		for (i64 k = 2, x = 1ll * p * p; ; x *= p, k++)
		{
			G.emplace_back(1ll * G.back() * p % MOD);
			i64 res = p ^ k;
			REP(j, 0, k - 1) res -= 1ll * H[i][j] * G[k - j] % MOD;
			res %= MOD;if (res < 0) res += MOD;
			H[i].emplace_back(res);
			if (x > lim) break;
		}
	}
}
namespace SMU
{
	int mem[maxn];
	bool vis[maxn];
	int s(i64 n)
	{
		if (n <= N) return smu[n] < 0 ? MOD + smu[n] : smu[n];
		int pos = ::n / n;
		if (vis[pos]) return mem[pos];
		vis[pos] = 1;
		i64 res = 1;
		int blk = sqrt(n + .5);
		for (i64 i = 2; i <= blk; i++) res -= s(n / i);
		for (i64 i = blk + 1, j; i <= n; i = j + 1)
		{
			j = n / (n / i);
			res -= (j - i + 1ll) * s(n / i) % MOD;
		}
		res %= MOD;if (res < 0) res += MOD;
		return mem[pos] = res;
	}
}
namespace SG
{
	int mem[maxn];
	bool vis[maxn];
	int s(i64 n)
	{
		if (n <= N) return sg[n];
		int pos = ::n / n;
		if (vis[pos]) return mem[pos];
		vis[pos] = 1;
		unsigned i64 res = 0;
		int blk = sqrt(n + .5);
		for (i64 i = 1; i <= blk; i++) res += i * SMU :: s(n / i) % MOD;
		res = 2ll * res % MOD;
		for (i64 i = blk + 1, j; i <= n; i = j + 1)
		{
			j = n / (n / i);
			res += (unsigned i64)(i + j) % MOD * (j - i + 1) % MOD * SMU :: s(n / i) % MOD;
		}
		res = res % MOD * inv2 % MOD;
		return mem[pos] = res;
	}
}

i64 ans;
void dfs(int lst, i64 d, i64 h)
{
	if (!h) return;
	ans += h * SG :: s(n / d) % MOD;
	REP(i, lst + 1, p_cnt)
	{
		i64 lim = n / prime[i];
		if (d <= lim)
		{
			i64 nd = d * prime[i];
			if (i == 1) dfs(i, nd, 2);
			REP(k, 2, (int)H[i].size() - 1)
			{
				if (nd > lim) break;
				nd *= prime[i];
				dfs(i, nd, h * H[i][k] % MOD);
			}
		}
		else break;
	}
}

signed main()
{
#ifdef CraZYali
	file("6053");
#endif
	n = read<i64>();
	init(pow(n, 2. / 3) + 5);
	dfs(0, 1, 1);
	cout << ans % MOD << endl;
	return 0;
}
