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
const int MOD = 998244353, inv2 = MOD + 1 >> 1;

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

int n;
const int flag_or = 1, flag_and = 2, flag_xor = 3;
void FWT(int a[], int n, int flag, int flag_opt)
{
	if (n == 1) return;
	int mid(n >> 1);
	switch (flag_opt)
	{
		case flag_or:
			if (flag < 0) 
				REP(i, mid, n - 1) (a[i] -= a[i - mid]) %= MOD;
			FWT(a, mid, flag, flag_opt);
			FWT(a + mid, mid, flag, flag_opt);
			if (flag > 0)
				REP(i, mid, n - 1) (a[i] += a[i - mid]) %= MOD;
			break;
		case flag_and:
			if (flag < 0)
				REP(i, 0, mid - 1) (a[i] -= a[i + mid]) %= MOD;
			FWT(a, mid, flag, flag_opt);
			FWT(a + mid, mid, flag, flag_opt);
			if (flag > 0)
				REP(i, 0, mid - 1) (a[i] += a[i + mid]) %= MOD;
			break;
		case flag_xor:
			if (flag < 0)
				REP(i, 0, mid - 1)
				{
					int x(a[i]), y(a[i + mid]);
					a[i] = 1ll * (x + y) * inv2 % MOD;
					a[i + mid] = 1ll * (x - y) * inv2 % MOD;
				}
			FWT(a, mid, flag, flag_opt);
			FWT(a + mid, mid, flag, flag_opt);
			if (flag > 0)
				REP(i, 0, mid - 1)
				{
					int x(a[i]), y(a[i + mid]);
					a[i] = (x + y) % MOD;
					a[i + mid] = (x - y) % MOD;
				}
			break;
	}
}
int a[1 << 17], b[1 << 17], c[1 << 17];

int main()
{
#ifdef CraZYali
	file("4717");
#endif
	cin >> n;
	const int len((1 << n) - 1);
	REP(i, 0, len) a[i] = read<int>();
	REP(i, 0, len) b[i] = read<int>();
	FWT(a, len + 1, 1, flag_or);
	FWT(b, len + 1, 1, flag_or);
	REP(i, 0, len) c[i] = 1ll * a[i] * b[i] % MOD;
	FWT(a, len + 1, -1, flag_or);
	FWT(b, len + 1, -1, flag_or);
	FWT(c, len + 1, -1, flag_or);
	REP(i, 0, len) printf("%d%c", (c[i] + MOD) % MOD, i == end_i ? '\n' : ' ');
	FWT(a, len + 1, 1, flag_and);
	FWT(b, len + 1, 1, flag_and);
	REP(i, 0, len) c[i] = 1ll * a[i] * b[i] % MOD;
	FWT(a, len + 1, -1, flag_and);
	FWT(b, len + 1, -1, flag_and);
	FWT(c, len + 1, -1, flag_and);
	REP(i, 0, len) printf("%d%c", (c[i] + MOD) % MOD, i == end_i ? '\n' : ' ');
	FWT(a, len + 1, 1, flag_xor);
	FWT(b, len + 1, 1, flag_xor);
	REP(i, 0, len) c[i] = 1ll * a[i] * b[i] % MOD;
	FWT(c, len + 1, -1, flag_xor);
	REP(i, 0, len) printf("%d%c", (c[i] + MOD) % MOD, i == end_i ? '\n' : ' ');
	return 0;
}
