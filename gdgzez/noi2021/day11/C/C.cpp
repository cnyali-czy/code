#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <algorithm>
#include <map>
#include <deque>
#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 75, MOD = 998244353, inv2 = MOD + 1 >> 1;

#define node deque <int>

int n, a[maxn];
map <node, int > f[maxn];

void upd(int x, int y)
{
	for (auto i : f[y])
	{
		auto j = i.first;
        if (j.size() && a[x] == j.front())
		{
			j.pop_front();
			(f[x][j] += i.second) %= MOD;
		}
        j = i.first;j.emplace_back(a[x]);
		f[x][j] = (f[x][j] + (1ll + i.first.empty()) * i.second) % MOD;
	}
}

int main()
{
#ifdef CraZYali
	freopen("C.in", "r", stdin);
	freopen("C.out", "w", stdout);
#endif
	int T;cin >> T;
	while (T--)
	{
		scanf("%d", &n);
		if (n & 1)
		{
			puts("0");
			continue;
		}
		REP(i, 1, n) scanf("%d", a + i);
		REP(i, 0, n + 1) f[i].clear();
		f[0][{}] = f[n + 1][{}] = 1;
		REP(i, 1, n / 2) upd(i, i - 1);
		DEP(i, n, n / 2 + 1) upd(i, i + 1);
		map <node, int> x = f[n / 2], y;
		for(auto i : f[n/2 + 1])
		{
			auto j = i.first;
			reverse(j.begin(), j.end());
			y[j] = i.second;
		}
		i64 ans = 0;
		for (auto i : x)
		{
			i64 a = x[i.first], b = y[i.first];
			if (i.first.empty()) (ans += a * b) %= MOD;
			else (ans += 1ll * a * b % MOD * inv2) %= MOD;
		}
		cout << ans << '\n';
	}
	return 0;
}
