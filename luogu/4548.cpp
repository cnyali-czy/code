#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e5 + 10, MOD = 1e4;

int T, n, m, a[maxn], bin[maxn];

int read()
{
	int res = 0;
	char c = getchar();
	while (!isdigit(c)) c = getchar();
	while (isdigit(c)) res = res * 10 + c - 48, c = getchar();
	return res;
}

int main()
{
#ifdef CraZYali
	freopen("4548.in", "r", stdin);
	freopen("4548.out", "w", stdout);
#endif
	m = read();T = read();
	bin[0] = 1;
	REP(i, 1, 100000) bin[i] = bin[i - 1] * m % MOD;
	while (T--)
	{
		n = read();
		REP(i, 1, n) a[i] = read();
		static int fail[maxn];
		int k = 0;
		REP(i, 2, n)
		{
			while (k && a[k + 1] != a[i]) k = fail[k];
			if (a[k + 1] == a[i]) k++;
			fail[i] = k;
		}
		long long ans = 0;
		for (int x = n; x; x = fail[x]) ans += bin[x];
		ans %= MOD;

		if (ans < 1000) putchar('0');
		if (ans < 100) putchar('0');
		if (ans < 10) putchar('0');
		printf("%lld\n", ans);
	}
	return 0;
}
