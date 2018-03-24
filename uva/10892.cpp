#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
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
const int maxn = 100010;

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
int m, n, k;
int gcd(int a, int b) {return !b ? a : gcd(b, a % b);}

int main()
{
#ifdef CraZYali
	freopen("10892.in", "r", stdin);
	freopen("10892.out", "w", stdout);
#endif
	while (1)
	{
		n = read<int>();
		if (!n) return 0;
		printf("%d ", n);
		register long long ans = 1;
		for (register int i = 2; i * i <= n ; i++)
			if (n % i == 0)
			{
				register long long temp = 0;
				while (n % i == 0)
				{
					n /= i;
					temp++;
				}
				ans *= temp * 2 + 1;
			}
		if (n ^ 1)
			ans *= 3;
		printf("%lld\n", (ans - 1) / 2 + 1);
	}
	
	return 0;
}
