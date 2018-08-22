#define  REP(i, s, e) for(register long long i = s; i <= e ; i++)
#define DREP(i, s, e) for(register long long i = s; i >= e ; i--)

#include <bits/stdc++.h>

using namespace std;
const long long MOD = 1e9 + 7;
const int maxn = 100 + 5;

int m, n, k;

long long a[maxn];

long long read()
{
	long long p = 1, ans = 0;
	register char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		ans %= MOD;
		c = getchar();
	}
	return (ans * p + MOD) % MOD;
}

vector <long long> ans;

int main()
{
#ifdef CraZYali
	freopen("2312.in", "r", stdin);
	freopen("2312.out", "w", stdout);
#endif
	cin >> n >> m;
	n++;
	REP(i, 1, n) a[i] = read();
	REP(x, 1, m)
	{
		register long long now = a[n];
		DREP(i, n-1, 1)	now = (now * x % MOD + a[i]) % MOD;
		if (!now) ans.push_back(x);
	}
	cout << ans.size() << endl;
	long long siz = ans.size() - 1;
	REP(i, 0, siz) printf("%lld\n", ans[i]);
	return 0;
}
