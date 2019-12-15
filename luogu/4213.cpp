#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %lld\n", __FUNCTION__, __LINE__)

#include <algorithm>
#include <cassert>
#include <iostream>
#include <cstdio>
#include <unordered_map>
#include <cmath>
using namespace std;
const int N((1ll << 31) - 1), B(pow(N, 2. / 3));

int sum[B + 5], mu[B + 5], prime[B + 5], p_cnt;
bool notp[B + 5];
struct __init__
{
	__init__()
	{
		sum[1] = mu[1] = 1;
		REP(i, 2, B)
		{
			if (!notp[i]) mu[prime[++p_cnt] = i] = -1;
			REP(j, 1, p_cnt)
			{
				int tmp = i * prime[j];
				if (tmp > B) break;
				notp[tmp] = 1;
				if (i % prime[j]) mu[tmp] = -mu[i];
				else break;
			}
			sum[i] = sum[i-1] + mu[i];
		}
	}
}__INIT__;
unordered_map <int, long long> mem;
inline long long ans2(int n)
{
	if (n <= B) return sum[n];
	if (mem.count(n)) return mem[n];
	long long res(1);
	for (int i = 2, j; i <= n; i = j + 1)
	{
		j = n / (n / i);
		res -= 1ll * (j - i + 1) * ans2(n / i);
	}
	return mem[n] = res;
}
inline long long ans1(int n)
{
	long long res(0);
	for (int i = 1, j; i <= n; i = j + 1)
	{
		j = n / (n / i);
		res += 1ll * (ans2(j) - ans2(i-1)) * (n / i) * (n / i);
	}
	return res + 1 >> 1;
}
signed main()
{
#ifdef CraZYali
	freopen("4213.in", "r", stdin);
	freopen("4213.out", "w", stdout);
#endif
	register int T;
	cin >> T;
	while (T--)
	{
		int n;
		scanf("%d", &n);
		printf("%lld %lld\n", ans1(n), ans2(n));
	}
	return 0;
}
