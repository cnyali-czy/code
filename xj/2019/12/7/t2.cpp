#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <ctime>
#include <cassert>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>
#include <unordered_map>
using namespace std;
const int N = 2e6;

int to[N + 5], Max[N + 5], prime[N + 5], p_cnt;
char mu[N + 5];
unsigned sum[N + 5];
bool notp[N + 5];

struct __init__
{
	__init__()
	{
		sum[1] = mu[1] = 1;
		to[1] = 1;
		REP(i, 2, N)
		{
			if (!notp[i])
			{
				mu[prime[++p_cnt] = i] = -1;
				to[i] = Max[i] = i;
			}
			REP(j, 1, p_cnt)
			{
				int tmp = i * prime[j];
				if (tmp > N) break;
				notp[tmp] = 1;
				Max[tmp] = prime[j];
//				if (Max[tmp] < Max[i]) Max[tmp] = Max[i];
				if (i % prime[j])
				{
					mu[tmp] = -mu[i];
					to[tmp] = to[i] * prime[j];
				}
				else
				{
					to[tmp] = to[i];
					break;
				}
			}
			sum[i] = sum[i-1] + mu[i];
		}
	}
}__INIT__;

namespace MU
{
	unordered_map <int, unsigned> mem;
	unsigned query(int n)
	{
		if (n <= N) return sum[n];
		if (mem.count(n)) return mem[n];
		unsigned res(1);
		for (register int i = 2, j; i <= n; i = j + 1)
		{
			j = n / (n / i);
			res -= query(n / i) * (j - i + 1);
		}
		return mem[n] = res;
	}
}

unsigned ans;
#define LIM
#ifdef LIM
const int lim = 2.5e5;
unsigned *mem[lim + 5];
#endif
unsigned qaqaq[N + 5];
unsigned f(int n, int a)
{
	if (!n) return 0;
	if (a == 1) return MU::query(n);
	a = to[a];
#ifdef LIM
	if (1ll * n * a <= lim) return mem[a][n];
#endif
	vector <int> qaq;
	for (int tmp = a; tmp > 1; tmp /= Max[tmp]) qaq.emplace_back(Max[tmp]);
	unsigned res(0);
	int _n(qaq.size());
	REP(S, 0, (1 << _n) - 1)
	{  
		int d(1);
		REP(i, 0, _n-1)
			if (S & (1 << i)) d *= qaq[i];
		res += f(n / d, d);
	}
	return res;
}
signed main()
{
#ifdef CraZYali
	freopen("t2.in", "r", stdin);
	freopen("t2.out", "w", stdout);
	cout << "cost_init1 = " << clock() * 1. / CLOCKS_PER_SEC << endl;
#endif
	int n;
	cin >> n;
#ifdef LIM
	REP(a, 1, lim)
	{
		mem[a] = new unsigned[lim / a + 5];
		unsigned tmp(0);
		REP(i, 1, lim / a)
		{
			tmp += (__gcd(i, a) == 1) * mu[i];
			mem[a][i] = tmp;
		}
	}
#endif
	REP(i, 1, min(n, N)) if (mu[i])
	{
		unsigned tmp = f(n / i, i);
		ans += mu[i] * tmp * tmp;
	}
	REP(i, 1, n / N) if (mu[i])
		REP(j, i, n / N) if (mu[j])
		{
			int lcm = i / __gcd(i, j) * j;
			if (!qaqaq[lcm]) qaqaq[lcm] = f(N, i * j);
			if ((mu[i] == 1) ^ (mu[j] == 1)) ans -= (i == j ? 1 : 2) * (f(n / j, i * j) - qaqaq[lcm]);
			else ans += (i == j ? 1 : 2) * (f(n / j, i * j) - qaqaq[lcm]);
		}
#ifdef CraZYali
	cout << "cost_end = " << clock() * 1. / CLOCKS_PER_SEC << endl;
#endif
	cout << ans << endl;
	return 0;
}
