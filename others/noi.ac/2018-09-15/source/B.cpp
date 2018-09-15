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
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif
	cin >> n >> m >> MOD;
	if (n >= m) {dfs(0);cout << (ans + MOD) % MOD;}
	else cout << power_pow(m, n); 
	return 0;
}
