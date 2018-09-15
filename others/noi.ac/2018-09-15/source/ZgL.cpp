#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 5000 + 10, maxm = 5000 + 10;

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

int m, n, k, MOD;

int A[maxn], ans, vis[maxn];

void dfs(int x)
{
	if (x == n) {ans++; if (ans >= MOD) ans %= MOD;}
	else
	{
		x++;
		if (x < m)
			REP(i, 1, m)
			{
				vis[i]++;
				A[x] = i;
				dfs(x);
				vis[i]--;
			}
		else
		{
			vis[A[x - m]]--;
			bool flag = 0;
			REP(i, 1, m)
				if (vis[i] > 1)
				{
					flag = 1;
					break;
				}
			if (flag)
				REP(i, 1, m)
				{
					vis[i]++;
					A[x] = i;
					dfs(x);
					A[x] = 0;
					vis[i]--;
				}
			else
				REP(i, 1, m)
					if (vis[i])
					{
						vis[i]++;
						A[x] = i;
						dfs(x);
						A[x] = 0;
						vis[i]--;
					}
			vis[A[x - m]]++;
		}
	}
}

long long power_pow(long long a, long long b, const long long mod = (long long)MOD)
{
	long long ans = 1, base = a;
	while (b)
	{
		if (b & 1) ans = ans * base % MOD;
		base = base * base % MOD;
		b >>= 1;
	}
	return (ans + MOD) % MOD;
}

int main()
{
#ifdef CraZYali
	freopen("out", "w", stdout);
#endif
	for (m = 2;m <= 10;m++)
		for (n = m; n <= 10;n++)
		{
			MOD = (((1 << 30) - 1) << 1) + 1;
			ans = 0;
			dfs(0);
			printf("%d\t%d\t:\t%d\n", n, m, ans);
			fflush(stdout);
		}
	return 0;
}
