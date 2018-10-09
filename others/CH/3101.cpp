#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 1e6 + 10, maxpcnt = 80000;

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

int prime[maxpcnt], prime_cnt;
bool notprime[maxn];

void init(int n = 1000000)
{
	REP(i, 2, n)
	{
		if (!notprime[i]) prime[++prime_cnt] = i;
		REP(j, 1, prime_cnt)
		{
			if (prime[j] > i || prime[j] * i > n) break;
			notprime[prime[j] * i] = 1;
		}
	}
}

bool p[maxn];
int c[maxn];

void divide(int x)
{
	REP(i, 1, prime_cnt)
		if (prime[i] * prime[i] > x) break;
		else if (x % prime[i] == 0)
		{
			register int cnt = 0;
			while (x % prime[i] == 0)
			{
				x /= prime[i];
				cnt++;
			}
			p[prime[i]] = 1;
			c[prime[i]] += cnt;
		}
	if (x ^ 1) p[x] = 1, c[x]++;
}

int main()
{
#ifdef CraZYali
	freopen("3101.in", "r", stdin);
	freopen("3101.out", "w", stdout);
#endif
	cin >> n;
	init(n);	

	REP(i, 2, n) divide(i);

	REP(i, 1, prime_cnt)
		if (p[prime[i]]) printf("%d %d\n", prime[i], c[prime[i]]);

	return 0;
}
