#define REP(i, s, e) for (int i = s; i <= e ; i++)

#include <bits/stdc++.h>
#define int unsigned long long

using namespace std;
const int N = 1e7, maxn = N + 10;

int power_pow(int a, int b)
{
	int ans = 1, base = a;
	while (b)
	{
		if (b & 1) ans *= base;
		base *= base;
		b >>= 1;
	}
	return ans;
}

int n, m, k, ans;
bool notprime[maxn];
int prime[maxn], p_cnt;
void init()
{
	REP(i, 2, N)
	{
		if (!notprime[i]) prime[++p_cnt] = i;
		REP(j, 1, p_cnt)
		{
			if (i * prime[j] > N) break;
			notprime[i * prime[j]] = 1;
			if (i % prime[j] == 0) break;
		}
	}
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	init();
	cin >> n >> k;
	n--;
	REP(i, 1, p_cnt)
		if (n <= 1) break;
		else
		{
			int t = (n-1) / prime[i];
			ans += t * power_pow(prime[i], k);
			n -= n / prime[i];
		}
	cout << ans << endl;
	return 0;
}
