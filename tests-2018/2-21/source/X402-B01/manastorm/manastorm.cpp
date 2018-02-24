#define  REP(i, s, e) for(register long long i = s; i <= e ;i++)
#define DREP(i, s, e) for(register long long i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 1e5 + 10, MOD = 998244353;

template <typename T> T read()
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

int m, n, k;

typedef long long ll;
inline ll Pow(ll x, ll y)
{
	ll res = 1;
	x %= MOD;
	while (y)
	{
		if (y & 1) res = (res * x) % MOD;
		x = (x * x) % MOD;
		y >>= 1;
	}
	return res % MOD;
}
int a[maxn];

ll tot, cnt;
inline void dfs(ll x, ll sum)
{
	if (x == k)
	{
		tot = (tot + sum) % MOD;
		cnt++;
		return;
	}
	REP(i, 1, n)
	{
		a[i]--;
		ll temp = 1;
		REP(j, 1, n) if (i ^ j) temp = (temp * a[j]) % MOD;
		dfs(x + 1, (sum + temp) % MOD);
		a[i]++;
	}
}

int main()
{
	freopen("manastorm.in", "r", stdin);
	freopen("manastorm.out", "w", stdout);
	n = read<int>();
	k = read<int>();
	REP(i, 1, n) a[i] = read<int>();
	dfs(0, 0);
	tot = (tot * Pow(cnt, MOD - 2) % MOD) % MOD;
	cout << (tot + MOD) % MOD;
	return 0;
}
