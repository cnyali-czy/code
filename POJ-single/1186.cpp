#define  REP(i, s, e) for(register long long i = s; i <= e ;i++)
#define DREP(i, s, e) for(register long long i = s; i >= e ;i--)

#define DEBUG fprlong longf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <iostream>
#include <cstdio>
#include <map>

using namespace std;
const long long maxn = 10;

long long k[maxn], p[maxn];

inline long long power_pow(long long a, long long b)
{
	long long ans = 1, base = a;
	while (b)
	{
		if (b & 1) ans *= base;
		base *= base;
		b >>= 1;
	}
	return ans;
}

map <long long, long long> s;

long long ans = 0;

long long X[maxn];

long long n, m;

void dfs(long long x, long long T, bool mode)
{
	if (x == T)
		if (!mode)
		{
			long long tt = 0;
			REP(i, 1, n / 2)
				tt += k[i] * power_pow(X[i], p[i]); 
			s[tt]++;
		}
		else
		{
			long long tt = 0;
			REP(i, n / 2 + 1, n)
				tt += k[i] * power_pow(X[i], p[i]);
			ans += s[-tt];
		}
	else
	{
		x++;
		REP(i, 1, 150)
		{
			X[x] = i;
			dfs(x, T, mode);
		}
	}
}

int main()
{
#ifdef CraZYali
	freopen("1186.in", "r", stdin);
	freopen("1186.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, n) scanf("%lld%lld", k + i, p + i);
	dfs(0, n / 2, 0);
	dfs(n / 2, n, 1);
	cout << ans;
	return 0;
}
