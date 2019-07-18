#define REP(i, s, e) for (int i = s; i <= e ; i++)

#include <bits/stdc++.h>
#define int unsigned long long

using namespace std;
const int N = 1e10, maxn = 30000000 + 10;
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
int n, k, ans;
vector <int> prime;
int p_cnt;
bitset <10000000010> notprime;

void init()
{
	REP(i, 2, N)
	{
		if (!notprime[i]) prime.push_back(i),++p_cnt;
		REP(j, 0, p_cnt-1)
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
	freopen("bfA.out", "w", stdout);
#endif
	init();
	cerr << "DONE !";
	cout << p_cnt << endl;
	return 0;
}
