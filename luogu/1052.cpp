#define DREP(i, s, e) for(register long long i = s; i >= e ;i--)
#define  REP(i, s, e) for(register long long i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %lld\n", __FUNCtION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const long long maxn = 100 + 10, maxlen = 20000, inf = 1ll << 60ll;

template <typename t> inline t read()
{
	t ans(0), p(1);
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

template <typename t> void write(t x)
{
	if (x < 0) putchar('-'), write(-x);
	else if (x / 10) write(x / 10);
	putchar(x % 10 + '0');
}

long long m, n, k, s, t, L;
long long a[maxn], dp[maxlen];

bool have[maxlen];

signed main()
{
#ifdef CraZYali
	freopen("1052.in", "r", stdin);
	freopen("1052.out", "w", stdout);
#endif
	cin >> L;
	cin >> s >> t >> n;
	REP(i, 1, n) scanf("%lld", a + i);
	a[++n] = L;
	register long long ans;
	if (s == t)
	{
		ans = 0;
		REP(i, 1, n) ans += (a[i] % s == 0);
	}
	else
	{
		ans = inf;
		sort(a + 1, a + 1 + n);
		register long long pos = 0;
		REP(i, 1, n)
		{
			if (a[i] - a[i - 1] >= t) pos += t + (a[i] - a[i - 1]) % t;
			else pos += a[i] - a[i - 1];
			have[pos] = 1;
		}
		have[pos] = 0;

		long long fin = pos;

		REP(i, 1, fin + t) dp[i] = inf;
		REP(i, s, fin + t)
			REP(j, s, t)
				if (i - j >= 0) chkmin(dp[i], dp[i - j] + have[i]);
		REP(i, fin, fin + t)
			chkmin(ans, dp[i]);
	}
	cout << ans;
	return 0;
}
