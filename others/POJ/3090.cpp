#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;
const int maxn = 1e6 + 10;

long long s[maxn];

bool notprime[maxn];

//vector <int> prime;

int prime[maxn];
int prime_cnt, phi[maxn];

void get_phi(int n)
{
	REP(i, 2, n)
	{
		if (!notprime[i])
		{
			prime[++prime_cnt] = i;
			phi[i] = i - 1;
		}
		REP(j, 1, prime_cnt)
		{
			if (prime[j] > i || prime[j] * i > n) break;
			notprime[i * prime[j]] = 1;
			phi[i * prime[j]] = phi[i] * (i % prime[j] ? prime[j] - 1 : prime[j]);
		}
	}

	REP(i, 1, n) s[i] = s[i - 1] + (long long)phi[i];
}


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

int m, n, k;

int main()
{
#ifdef CraZYali
	freopen("3090.in", "r", stdin);
	freopen("3090.out", "w", stdout);
#endif
	get_phi(1000000);

	register int T = read<int>();
	REP(i, 1, T)
	{
		n = read<int>();
		printf("%d %d %lld\n", i, n, s[n] * 2 + 3);
	}

	return 0;
}
