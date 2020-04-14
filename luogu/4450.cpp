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
const int maxn = 1e6 + 10;

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

int m, n, d;

int prime[maxn], mu[maxn], p_cnt;
bool notp[maxn];

int main()
{
#ifdef CraZYali
	file("4450");
#endif
	n = read<int>();m = read<int>();d = read<int>();
	if (n > m) swap(n, m);
	if (d > n) {puts("0");return 0;}
	n /= d;m /= d;
	mu[1] = 1;
	long long ans = 1ll * n * m;
	REP(i, 2, n)
	{
		if (!notp[i]) mu[prime[++p_cnt] = i] = -1;
		REP(j, 1, p_cnt)
		{
			int tmp = i * prime[j];
			if (tmp > n) break;
			notp[tmp] = 1;
			if (i % prime[j]) mu[tmp] = -mu[i];
			else break;
		}
		if (mu[i]) ans += 1ll * mu[i] * (n / i) * (m / i);
	}
	cout << ans << '\n';
	return 0;
}
