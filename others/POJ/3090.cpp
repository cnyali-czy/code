#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>

using namespace std;
const int N = 1000 , maxn = N + 10;

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

bool notprime[maxn];
int prime[maxn], prime_cnt, phi[maxn], sum[maxn];

void init(int N)
{
	phi[1] = 1;sum[1] = 1;
	REP(i, 2, N)
	{
		if (!notprime[i]) prime[++prime_cnt] = i, phi[i] = i - 1;
		REP(j, 1, prime_cnt)
		{
			if (prime[j] > i || i * prime[j] > N) break;
			notprime[i * prime[j]] = 1;
			if (i % prime[j] == 0) phi[i * prime[j]] = phi[i] * prime[j];
			else phi[i * prime[j]] = phi[i] * (prime[j] - 1);
		}
		sum[i] = sum[i-1] + phi[i];
	}
}

int main()
{
#ifdef CraZYali
	freopen("3090.in", "r", stdin);
	freopen("3090.out", "w", stdout);
#endif
	init(N);

	register int T = read<int>();
	REP(i, 1, T)
	{
		write(i);putchar(' ');
		write(n = read<int>());putchar(' ');
		write(1 + 2 * sum[n]);putchar(10);
	}
	return 0;
}
