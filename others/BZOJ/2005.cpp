#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 100000 + 10, maxp = 10000;

int n, m;

int p[maxp], pnt, mu[maxn];
bool notprime[maxn];

void prepare(const int N = 100000)
{
	mu[1] = 1;
	REP(i, 2, N)
	{
		if (!notprime[i]) mu[p[++pnt] = i] = -1;
		REP(j, 1, pnt)
		{
			int d = i * p[j];
			if (d > N) break;
			notprime[d] = 1;
			if (i % p[j]) mu[d] = -mu[i];
			else break;
		}
	}
	REP(i, 2, N) mu[i] += mu[i-1];
}
long long ans;
inline long long calc(int n, int m)
{
	if (n > m) swap(n, m);
	long long res(0);
	REP(i, 1, n)
	{
		int j = min(n / (n / i), m / (m / i));
		res += 1ll * (mu[j] - mu[i-1]) * (n / i) * (m / i);
		i = j;
	}
	return res;
}

int main()
{
#ifdef CraZYali
	freopen("2005.in", "r", stdin);
	freopen("2005.out", "w", stdout);
#endif
	prepare();
	cin >> n >> m;
	if (n > m) swap(n, m);
	REP(i, 1, m) ans += 1ll * i * calc(n / i, m / i);
	cout << ans * 2 - 1ll * n * m << endl;
	return 0;
}
