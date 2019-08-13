#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 50000 + 10;

int n, m;
int p[5400], p_cnt;
bool notprime[maxn];
long long mu[maxn], sigma[maxn], Min[maxn];

void get_prime(int N = 50000)
{
	mu[1] = sigma[1] = 1;
	REP(i, 2, N)
	{
		if (!notprime[i]) p[++p_cnt] = i, mu[i] = -1, sigma[i] = 2, Min[i] = 1;
		REP(j, 1, p_cnt)
		{
			int temp = i * p[j];
			if (temp > N) break;
			notprime[temp] = 1;
			if (i % p[j] == 0)
			{
				Min[temp] = Min[i] + 1;
				sigma[temp] = sigma[i] / (Min[i] + 1) * (Min[temp] + 1);
				break;
			}
			else mu[temp] = -mu[i], sigma[temp] = sigma[i] << 1, Min[temp] = 1;
		} 
	}
	REP(i, 1, N) mu[i] += mu[i-1];
	REP(i, 1, N) sigma[i] += sigma[i-1];
}

inline long long F(int n, int m)
{
	if (n > m) swap(n, m);
	long long ans = 0;
	REP(i, 1, n)
	{
		int j = min(n / (n / i), m / (m / i));
		ans += (mu[j] - mu[i - 1]) * sigma[n / i] * sigma[m / i];
		i = j;
	}
	return ans;
}

int main()
{
#ifdef CraZYali
	freopen("3994.in", "r", stdin);
	freopen("3994.out", "w", stdout);
#endif
	get_prime();
	int Case;cin >> Case;
	while (Case --> 0)
	{
		scanf("%d%d", &n, &m);
		printf("%lld\n", F(n, m));
	}
	return 0;
}
