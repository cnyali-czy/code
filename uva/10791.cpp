#define DREP(i, s, e) for(register long long i = s; i >= e ;i--)
#define  REP(i, s, e) for(register long long i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %lld\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <queue>
#include <map>
#include <set>

using namespace std;
const long long maxn = 100010;

template <typename T> T read()
{
	T ans(0), p(1);
	char c = getchar();
	while (!isdigit(c)) {
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c)) {
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}
long long m, n, k;

long long Case;

inline bool isprime(long long x)
{
	if (x == 2) return 1;
	for (register long long i = 2; i * i <= x ; i++)
		if (x % i == 0) return 0;
	return 1;
}

int main()
{
#ifdef CraZYali
	freopen("10791.in", "r", stdin);
	freopen("10791.out", "w", stdout);
#endif
	while (1)
	{
		n = read<long long>();
		if (!n) return 0;
		printf("Case %lld: ", ++Case);
		if (n == 1 || isprime(n)) printf("%lld\n", n + 1);
		else
		{
			long long ans = 0, tn = n;
			for (register long long i = 2; i * i <= n ;i++)
				if (n % i == 0)
				{
					register long long temp = 1;
					while (n % i == 0)
					{
						n /= i;
						temp *= i;
					}
					ans += temp;
				}
			if (n > 1) ans += n;
			printf("%lld\n", ans + (ans == tn));
		}
	}
}
