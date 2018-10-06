#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 1e7 + 10, maxp = 665000;

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

int prime[maxp], p_cnt;
bool notprime[maxn];

int phi[maxn];

void init(int n)
{
	phi[1] = 1;
	REP(i, 2, n)
	{
		if (!notprime[i]) prime[++p_cnt] = i, phi[i] = i - 1;
		REP(j, 1, p_cnt)
		{
			if (prime[j] * i > n) break;
			notprime[prime[j] * i] = 1;
			if (i % prime[j] == 0)
			{
				phi[prime[j] * i] = phi[i] * prime[j];
				break;
			}
			phi[prime[j] * i] = phi[i] * (prime[j] - 1);
		}
	}
}

long long s[maxn];

int main()
{
#ifdef CraZYali
	freopen("2818.in", "r", stdin);
	freopen("2818.out", "w", stdout);
#endif
	init(n = read<int>());

	REP(i, 1, n) s[i] = s[i-1] + phi[i];
	register long long ans = 0 ;
	REP(i, 1, p_cnt) ans += s[n / prime[i]];
	cout << ans * 2 - p_cnt;
	return 0;
}
