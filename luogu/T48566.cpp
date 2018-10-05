#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

#define int long long

using namespace std;
const int maxn = 1000000 + 10, MOD = 998244353;

template <typename T> inline T read()
{
	T ans(0), p(1);
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}

template <typename T> void write(T x)
{
	if (x < 0) putchar('-'), write(-x);
	else if (x / 10) write(x / 10);
	putchar(x % 10 + '0');
}

int m, n, k;

signed main()
{
#ifdef CraZYali
	freopen("T48566.in", "r", stdin);
	freopen("T48566.out", "w", stdout);
#endif
	n = read<int>();
	register int a = 1, b = 0;
	REP(i, 2, n) a = a * 2 % MOD;
	REP(i, 1, n) b = (b + read<int>()) % MOD;
	register int ans = a * b % MOD;
	cout << (ans + MOD) % MOD;

	return 0;
}
