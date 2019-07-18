#define REP(i, s, e) for (int i = s; i <= e ;i++)

#include <bits/stdc++.h>
#define ll long long
#define ull unsigned ll

using namespace std;
const ll K = 170;

ull power_pow(ull a, int b)
{
	ull ans = 1, base = a;
	while (b)
	{
		if (b & 1) ans *= base;
		base *= base;
		b >>= 1;
	}
	return ans;
}
ll p[38000], p_cnt;
bitset <450000> notprime;
void init(int N)
{
	REP(i, 2, N)
	{
		if (!notprime[i]) p[++p_cnt] = i;
		REP(j, 1, p_cnt)
		{
			if (i * p[j] > N) break;
			notprime[i * p[j]] = 1;
			if (i % p[j] == 0) break;
		}
	}
}

ll n, k;
ull ans;
unordered_map <ll, ll> rem;
#define not_same_pos(x, y) ((x) * n + y)//make sure no ³åÍ»

ll dfs(int pos, ll cur, int flag)
{
	if (rem[not_same_pos(pos, cur)]) return rem[not_same_pos(pos, cur)] * flag;
	if (!pos) return cur * flag;
	ll ret = dfs(pos-1, cur, flag);
	if (p[pos] <= cur) ret += dfs(pos-1, cur / p[pos], -flag);
	rem[not_same_pos(pos, cur)] = ret * flag;
	return ret;
}
ll cnt, N;
bitset <200000000> w;

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	cin >> n >> k;
	init(sqrt(n) + 1);
	REP(i, 1, min(p_cnt, K)) ans += (dfs(i - 1, n / p[i], 1)-1) * power_pow(p[i], k);
	if (p_cnt > K)
	{
		cnt = N = n / p[K+1];
		REP(i, 1, K)
			for (int j = 1; p[i] * j <= N; j++)
				if (!w[p[i] * j])
				{
					w[p[i] * j] = 1;
					cnt--;
				}
		REP(i, K + 1, p_cnt)
		{
			ans += (cnt-1) * power_pow(p[i], k);
			if (i < p_cnt)
			{
				N = n / p[i+1];
				for (int j = n / p[i]; j > N; j--) cnt -= !w[j];
				for (int j = 1; p[i] * j <= N; j++)
					if (!w[p[i] * j])
					{
						w[p[i] * j] = 1;
						cnt--;
					}
			}
		}
	}
	cout << ans << endl;
	return 0;
}
