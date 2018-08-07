#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;

const long long MOD = 1e9 + 7;

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

namespace bf
{
	const int maxn = 100;
	int G[maxn][maxn], ans, S;

	int pick[maxn];

	bool vis[maxn];

	inline long long power_pow(long long a, long long b)
	{
		a %= MOD;b %= MOD;
		a = (a + MOD) % MOD;b = (b + MOD) % MOD;
		long long ans = 1, base = a;
		while (b)
		{
			if (b & 1) ans = (ans * base) % MOD;
			base = (base * base) % MOD;
			b >>= 1;
		}
		ans %= MOD;
		return (ans + MOD) % MOD;
	}

	int a[maxn];

	void dfs(int x, int last)
	{
		if (x == n)
			ans = (ans + G[S][last]) % MOD;
		else
		{
			x++;
			REP(i, 1, n)
				if (!vis[i])
				{
					vis[i] = 1;
					a[x] = i;
					if (last == -1) {S = i;dfs(x, i);}
					else if (G[last][i]) dfs(x, i);
					vis[i] = 0;
				}
		}
	}

	inline void work()
	{
		REP(i, 1, n)
			REP(j, 1, n)	
				G[i][j] = 1;
		while (m --> 0)
		{
			register int x, y;
			scanf("%d%d", &x, &y);
			G[x][y] = G[y][x] = 0;
		}
		ans = 0;
		dfs(0, -1);
		long long t = 1;
		REP(i, 2, n) t = (t * i) % MOD;
		t = (t + MOD) % MOD;
		ans = ans * power_pow(n, MOD - 2) % MOD;
		ans = ans * power_pow(2, MOD - 2) % MOD;
		cout << (ans + MOD) % MOD;
	}
}

namespace zero
{
	inline void work()
	{
		long long ans = 1;
		REP(i, 3, n - 1) ans = (ans * (long long)i) % MOD;
		cout << (ans + MOD) % MOD;
	}
}

int main()
{
	freopen("lighthouse.in", "r", stdin);
	freopen("lighthouse.out", "w", stdout);
	cin >> n >> m;
	if (m) bf::work();
	else zero::work();
	return 0;
}
