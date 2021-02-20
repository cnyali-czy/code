#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 2e6 + 10;

int prime[maxn], p_cnt;
bool notp[maxn];
void init(const int n = 2e6)
{
	notp[1] = 1;
	REP(i, 2, n)
	{
		if (!notp[i]) prime[++p_cnt] = i;
		REP(j, 1, p_cnt)
		{
			int t = i * prime[j];if (t > n) break;
			notp[t] = 1;
			if (i % prime[j] == 0) break;
		}
	}
}
pair <int, int> ans[maxn];

int main()
{
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
	init();
	for (int n = 4; n <= 1e6; n++)
		REP(i, 1, p_cnt)
		{
			if (prime[i] > n + n) break;
			if (!notp[n + n - prime[i]])
			{
				ans[n] = make_pair(prime[i], n + n - prime[i]);
				break;
			}
		}
	int T;cin >> T;
	while (T--)
	{
		int n;scanf("%d", &n);
		printf("%d %d\n", ans[n].first, ans[n].second);
	}
	return 0;
}
