#define DREP(i, s, e) for(register long long i = s; i >= e ;i--)
#define  REP(i, s, e) for(register long long i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %lld\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const long long maxn = 1e3 + 10, maxm = 1e3 + 10, MOD = 1e9 + 7, inf = 1ll << 60ll;

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

long long m, n, k;

long long c[maxn];
inline void add(long long x, long long y)
{
	while (x <= n + 1)
	{
		c[x] = (MOD + (c[x] + y) % MOD) % MOD;
		x += x & -x;
	}
}

inline long long sum(long long x)
{
	register long long res = 0;
	while (x > 0)
	{
		res = (res + c[x]) % MOD;
		x -= x & -x;
	}
	return (res + MOD) % MOD;
}

long long dp[maxm][maxn];
long long a[maxn];
pair <long long, long long> b[maxn];

long long rak[maxn];

int main()
{
#ifdef CraZYali
	freopen("5542.in", "r", stdin);
	freopen("5542.out", "w", stdout);
#endif
	register long long T = read<long long>(), Case = 0;
	while (T --> 0)
	{
		n = read<long long>();
		m = read<long long>();
		REP(i, 1, n) b[i] = make_pair(a[i] = read<long long>(), i);
		sort(b + 1, b + 1 + n);
		rak[b[1].second] = 2;
		REP(i, 2, n) rak[b[i].second] = rak[b[i-1].second] + (b[i-1].first < b[i].first);
		dp[0][0] = 1;
		REP(i, 1, m)
		{
			REP(j, 1, n + 1) c[j] = 0;
			add(1, dp[i-1][0]);
			REP(j, 1, n)
			{
				dp[i][j] = sum(rak[j] - 1);
				add(rak[j], dp[i-1][j]);
			}
		}
		register long long ans = 0;
		REP(i, 1, n)
			ans = (ans + dp[m][i]) % MOD;
		printf("Case #%lld: %lld\n", ++Case, (ans + MOD) % MOD);
	}
	
	return 0;
}
