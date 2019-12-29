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
const int maxn = 1e7 + 10;

char mu[maxn];
int prime[maxn], p_cnt, to[maxn], Max[maxn];
bool notp[maxn];
long long f[maxn];

int stack[666], top;
void split(int x)
{
	if (x == 1) return;
	stack[++top] = Max[x];
	split(x / Max[x]);
}

struct __init__
{
	__init__(const int N = 1e7)
	{
		mu[1] = to[1] = 1;
		REP(i, 2, N)
		{
			if (!notp[i])
			{
				prime[++p_cnt] = i;
				mu[i] = -1;
				to[i] = Max[i] = i;
			}
			REP(j, 1, p_cnt)
			{
				int tmp = i * prime[j];
				if (tmp > N) break;
				notp[tmp] = 1;
				Max[tmp] = Max[i];
				if (Max[tmp] < prime[j]) Max[tmp] = prime[j];
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
		REP(T, 2, N)
		{
			top = 0;
			split(to[T]);
			REP(i, 1, top) f[T] += mu[T / stack[i]];
			f[T] += f[T-1];
		}
	}
}__INIT__;

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

signed main()
{
#ifdef CraZYali
	file("2257");
#endif
	register int T(read<int>());
	while (T--)
	{
		int n(read<int>()), m(read<int>());
		if (n > m) swap(n, m);
		long long ans(0);
		for (int i = 1, j; i <= n; i = j + 1)
		{
			j = min(n / (n / i), m / (m / i));
			ans += 1ll * (n / i) * (m / i) * (f[j] - f[i-1]);
		}
		printf("%lld\n", ans);
	}
	return 0;
}
