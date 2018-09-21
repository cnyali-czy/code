#define DREP(i, s, e) for(register long long i = s; i >= e ;i--)
#define  REP(i, s, e) for(register long long i = s; i <= e ;i++)

#define DEBUG fprlong longf(stderr, "Passing [%s] in Line %lld\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
#include <cmath>

using namespace std;
const long long maxn = 1e5 + 10;

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

long long n, k;

long long s[maxn], m;
long long a[maxn], Max[maxn][30];

long long getmax(long long l, long long r)
{
	/*
	register long long _Max = a[l];
	DREP(i, 30, 0)
		if (l + (1 << i) <= r)
		{
			chkmax(_Max, Max[l][i]);
			l += 1 << i;
		}
	return _Max; 
	*/
	register long long k = log2(r - l + 1);
	return max(Max[l][k], Max[r - (1 << k) + 1][k]);
}

const long long inf = 1ll << 60ll;
long long dp[maxn], sum;

deque <long long> q;
deque <long long> :: iterator it;

int main()
{
#ifdef CraZYali
	freopen("3017.in", "r", stdin);
	freopen("3017.out", "w", stdout);
#endif
	n = read<long long>();
	m = read<long long>();
	register long long pos = 0;
	REP(i, 1, n)
	{
		scanf("%lld", a + i);
		if (a[i] > m)
		{
			cout << -1;
			return 0;
		}
		sum += a[i];
		while (sum > m) sum -= a[++pos];
		while (!q.empty() && q.front() <= pos) q.pop_front();
		while (!q.empty() && a[q.back()] <= a[i]) q.pop_back();
		q.push_back(i);
		dp[i] = inf;
		
		for (k = pos, it = q.begin(); it < q.end() ;k = *it, it ++)
			chkmin(dp[i], dp[k] + a[*it]);
	}
/*
	REP(j, 1, 30)
		REP(i, 1, n)
			if (i + (1 << j) - 1 <= n) Max[i][j] = max(Max[i][j-1], Max[i + (1 << j - 1)][j-1]);
			else break;

	REP(i, 1, n) dp[i] = inf;

	REP(i, 1, n)
		REP(j, 0, i - 1)
			if (s[i] - s[j] <= m) chkmin(dp[i], dp[j] + getmax(j + 1, i));
	cout << (dp[n] == inf ? -1 : dp[n]);
	*/
	cout << dp[n];
	return 0;
}
