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
const int maxn = 4700000, MOD = 1e9 + 7, inv2 = MOD + 1 >> 1, maxp = 325200;
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
int prime[maxp], phi[maxn], p_cnt, N, sg[maxn];
int G[35], H[maxp][35], l[maxp];
bool notp[maxn];
//G(x) = phi(x)
//F(p ^ k) = p xor k
void init(int N)
{
	::N = N;
	phi[1] = sg[1] = 1;
	REP(i, 2, N)
	{
		if (!notp[i]) phi[prime[++p_cnt] = i] = i - 1;
		REP(j, 1, p_cnt)
		{
			int tmp = i * prime[j];if (tmp > N) break;
			notp[tmp] = 1;
			if (i % prime[j])
				phi[tmp] = phi[i] * (prime[j] - 1);
			else
			{
				phi[tmp] = phi[i] * prime[j];
				break;
			}
		}
		sg[i] = add(sg[i - 1], phi[i]);
	}
	cerr << "p_cnt = " << p_cnt << endl;
	REP(i, 1, p_cnt)
	{
		int p = prime[i];
		G[0] = 1;G[1] = p - 1;
		//G[j]		= phi(p ^ j)
		
		//H[i][j]	= H(p ^ j)
		//			= p ^ {j - 1} (p - 1)
		H[i][0] = 1;
		if (i == 1) H[i][1] = 2;
		l[i] = 1;
		i64 lim = n / p;
		for (i64 k = 2, x = 1ll * p * p; ; x *= p, k++)
		{
			G[k] = 1ll * G[k - 1] * p % MOD;
			i64 res = p ^ k;
			REP(j, 0, k - 1) res -= 1ll * H[i][j] * G[k - j] % MOD;
			res %= MOD;if (res < 0) res += MOD;
			H[i][++l[i]] = res;
			if (x > lim) break;
		}
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
		i64 adjjs = n >= MOD ? n % MOD : n;
		i64 res = adjjs * (adjjs + 1) / 2 % MOD;
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
			REP(k, 2, l[i])
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
