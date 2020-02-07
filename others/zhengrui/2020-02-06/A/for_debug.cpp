/*
 * File Name:	A.cpp
 * Author	:	CraZYali
 * Time		:	2020.02.06 09:35
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e6 + 10;
const double eps = 1e-8;

template <typename T> inline T read()
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

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout);

int prime[maxn], p_cnt, mu[maxn], to[maxn], Max[maxn];
bool notp[maxn];
struct __init__
{
	__init__(const int n = maxn - 10)
	{
		mu[1] = 1;
		REP(i, 2, n)
		{
			if (!notp[i]) mu[to[prime[++p_cnt] = i] = i] = -1, Max[i] = i;
			REP(j, 1, p_cnt)
			{
				int tmp = i * prime[j];
				if (tmp > n) break;
				notp[tmp] = 1;
				Max[tmp] = Max[i];
				if (prime[j] > Max[i]) Max[tmp] = prime[j];
				if (i % prime[j])
				{
					to[tmp] = to[i] * prime[j];
					mu[tmp] = -mu[i];
				}
				else
				{
					to[tmp] = to[i];
					break;
				}
			}
		}
	}
}__INIT__;

int MOD, n, stack[100], top, lg[(1 << 25) + 5], sig[maxn], cnt[maxn], status, base[114];
bool vis[maxn];
long long mem[maxn], all_pairs;

int shit;
vector <pair<int, pair <int, int> > > for_debug;
long long Out;
void calc(int X, int Y)
{
	int sum = __gcd(X, Y) + X * Y / __gcd(X, Y);
	if (sum <= n)
	{
#ifdef CraZYali
		for_debug.emplace_back(shit,make_pair(X, Y));
#endif
		all_pairs--;
		(Out += sum) %= MOD;
	}
}
void dfs(int x, int X = 1, int Y = 1)
{
	if (x == top) calc(X, Y);
	else
	{
		int here = 1;
		x++;
		REP(i, 0, cnt[stack[x]])
		{
			if (status & (1 << x - 1))	dfs(x, X * here, Y * base[x]);
			else						dfs(x, X * base[x], Y * here);
			here *= stack[x];
		}
	}
}

int main()
{
#ifdef CraZYali
	file("A");
	freopen("A.err", "w", stderr);
	FILE *badfile = fopen("A.bad.err","w");
#endif
	REP(i, 1, 25) lg[1 << i] = i;
	register int T = read<int>();
	MOD = read<int>();
	const long long llim = MOD * 10000ll;
	REP(i, 1, 1000000) {sig[i] = sig[i-1] + i; if (sig[i] >= MOD) sig[i] -= MOD;}
	while (T--)
	{
		n = read<int>();
		if (vis[n])
		{
			printf("%lld\n", mem[n]);
			continue;
		}
		vis[n] = 1;
		long long &ans = mem[n];
		ans = 0;
		/*
		REP(T, 1, n)
		{
			top = 0;
			for (int x = to[T]; x > 1; x /= Max[x]) stack[top++] = Max[x];
			REP(S, 0, (1 << top) - 1)
			{
				int x = 1;
				for (int l = S; l; l &= (l - 1)) x *= stack[lg[l & -l]];
				REP(i, 1, n / T)
				{
					int E = floor(eps + (1. * n * x / T - 1) / i / x / x);
					if (!E)
					{
						long long tmp = (n / T - i + 1ll) * (n / T) * n % MOD * mu[x];
						if (tmp <= -llim || tmp >= llim) tmp %= llim;
						ans += tmp;
						if (ans < 0)		ans += llim;
						if (ans >= llim)	ans -= llim;
						break;
					}
					chkmin(E, n / T);
					long long tmp = 0;
					tmp += E * (T / x);
					tmp += 1ll * i * x * T % MOD * sig[E];
					tmp += 1ll * (n / T - E) * n;
					tmp *= mu[x];
					if (tmp <= -llim || tmp >= llim) tmp %= llim;
					ans += tmp;
					if (ans < 0)	 ans += llim;
					if (ans >= llim) ans -= llim;
				}
			}
		}
		//REP(d, 1, n) REP(x, 1, n / d) REP(i, 1, n / d / x) REP(j, 1, n / d / x) ans += mu[x] * min(n, (i * j * x * x + 1) * d);
		*/
		all_pairs = n * n;
		REP(l, 1, n)
		{
			shit = l;
			top = 0;
			for (int x = l; x > 1; x /= Max[x])
			{
				if (!cnt[Max[x]]) stack[++top] = Max[x];
				cnt[Max[x]]++;
			}
			REP(i, 1, top)
			{
				base[i] = 1;
				REP(j, 1, cnt[stack[i]]) base[i] *= stack[i];
			}
			int end_status;
			for (status = 0, end_status = (1 << top) - 1; status <= end_status; status++)
			{
				Out = 0;
				dfs(0);
				ans += Out;
				if (ans >= MOD) ans -= MOD;
			}
			REP(i, 1, top) cnt[stack[i]] = 0;
		}
		REP(i, 2, n)
		{
			if (i + i <= n) (ans -= i + i) %= MOD, all_pairs++;
#ifdef CraZYali
#endif
		}
		ans += all_pairs * n % MOD;
		ans = (MOD + ans % MOD) % MOD;
		printf("%lld\n", ans);
		fflush(stdout);
#ifdef CraZYali
		sort(for_debug.begin(), for_debug.end());
		for_debug.resize(unique(for_debug.begin(),for_debug.end())-for_debug.begin());
		for (auto i : for_debug) fprintf(badfile, "%d %d %d\n", i.first, i.second.first, i.second.second);
		fprintf(badfile,"------------\n");
		for_debug.clear();
		REP(i, 1, n)
			REP(j, 1, n) if (__gcd(i, j) + i * j / __gcd(i, j) <= n) for_debug.emplace_back(i*j/__gcd(i,j),make_pair(i,j));
		sort(for_debug.begin(), for_debug.end());
		for (auto i : for_debug) fprintf(stderr, "%d %d %d\n", i.first, i.second.first, i.second.second);
		for_debug.clear();
		cerr<<"------------\n";
#endif
	}
	return 0;
}

