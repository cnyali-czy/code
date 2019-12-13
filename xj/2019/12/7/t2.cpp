#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <cassert>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>
using namespace std;
const int maxn = 2e7 + 10, B = 233333;

int prime[6700000], p_cnt, Max[maxn];
char mu[maxn];
unsigned sum[maxn];
bool notp[maxn];

struct __init__
{
	__init__(const int n = 1e7)
	{
		sum[1] = mu[1] = 1;
		REP(i, 2, n)
		{
			if (!notp[i])
			{
				mu[prime[++p_cnt] = i] = -1;
				Max[i] = i;
			}
			REP(j, 1, p_cnt)
			{
				int tmp = i * prime[j];
				if (tmp > n) break;
				notp[tmp] = 1;
				Max[tmp] = prime[j];
				if (Max[tmp] < Max[i]) Max[tmp] = Max[i];
				if (i % prime[j]) mu[tmp] = -mu[i];
				else break;
			}
			sum[i] = sum[i-1] + mu[i];
		}
	}
}__INIT__;
unsigned ans;

pair <int, int> stack[6666];
int top;
void split(int x)
{
	if (x == 1) return;
	int res(0), tmp(Max[x]);
	while (x % tmp == 0)
	{
		x /= tmp;
		res++;
	}
	split(x);
	stack[++top] = make_pair(tmp, res);
}
int store[2000], qaq;
void dfs(int x, int res = 1)
{
	if (x == top) store[++qaq] = res;
	else
	{
		x++;
		dfs(x, res);
		REP(i, 1, stack[x].second)
		{
			res *= stack[x].first;
			dfs(x, res);
		}
	}
}

#include <unordered_map>
const int lim = 5e4;
unordered_map <int, unsigned> mem[lim + 5];
unordered_map <long long, unsigned> qaqaq;
unsigned f(int n, int a)
{
	if (!n) return 0;
	if (a == 1) return sum[n];
	if (n <= lim && mem[n].count(a)) return mem[n][a];
	qaq = top = 0;
	split(a);
	dfs(0);
	vector <int> tmp(store + 1, store + 1 + qaq);
	unsigned res(0);
	for (register auto d : tmp)
		res += f(n / d, d);
	return res;
}
signed main()
{
#ifdef CraZYali
	freopen("t2.in", "r", stdin);
	freopen("t2.out", "w", stdout);
#endif
	int n;
	cin >> n;
	const int d = 1.5e7;
	REP(n, 1, lim)
		for (int a = 1; a * n <= lim; a++)
		{
			unsigned tmp = f(n, a);
			mem[n][a] = tmp;
		}
	REP(i, 1, min(n, d)) if (mu[i])
	{
		unsigned tmp = f(n / i, i);
		ans += mu[i] * tmp * tmp;
	}
	REP(i, 1, n / d) if (mu[i])
		REP(j, i, n / d) if (mu[j])
		{
			long long lcm = i * j / __gcd(i, j);
			if (!qaqaq.count(lcm)) qaqaq[lcm] = f(d, i * j);
			if ((mu[i] == 1) ^ (mu[j] == 1)) ans -= (i == j ? 1 : 2) * (f(n / j, i * j) - qaqaq[lcm]);
			else ans += (i == j ? 1 : 2) * (f(n / j, i * j) - qaqaq[lcm]);
		}
	cout << ans << endl;
	return 0;
}
