/*
	Problem:	B.cpp
	Time:		2021-03-02 19:16
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cstring>
#include <vector>
#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 3e4 + 10, MOD = 998244353;

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, k;
char str[maxn];

#define pii pair <int, int>
vector <pii> t[maxn];
pii g[5][256][512];
#define fi first
#define se second

int main()
{
#ifdef CraZYali
	file("B");
#endif
	scanf("%s\n%d", str + 1, &k);n = strlen(str + 1);

    REP(j, 0, k) REP(s, 0, (1 << k + k) - 1)
    {
		static int p[233];
		int res = -j;
		REP(i, 0, k - 1) res -= (s >> i & 1);
		p[0] = res;
		REP(i, 0, k + k - 1)
		{
			res += (s >> i & 1);
			p[i + 1] = res;
		}
		p[k + k + 1] = res;
		REP(i, 0, (1 << k + k + 1) - 1)
		{
			int mx = p[0], lst, x = 0, qk;
			REP(l, 0, k + k)
			{
				mx = max(mx, p[l + 1]);
				if (i >> l & 1) mx = max(mx, p[l] + 1);
				if (l) x += (mx - lst << l - 1);
				if (l == k) qk = mx;
				lst = mx;
			}
			g[j][s][i] = make_pair(1 - qk, x);
		}
	}

	static int cnt[512];
	static i64 F[5][256], H[5][256];
	auto *f = F, *h = H;
	f[0][0] = 1;

	REP(i, 1, n) 
	{
		swap(f, h);memset(f, 0, sizeof F);
		vector <int> t;
		REP(j, 0, 25)
		{
			int s = 0;
			REP(l, max(1, i - k), min(n, i + k)) if (str[l] == j + 'A') s |= (1 << l - i + k);
			cnt[s]++;
		}
		REP(j, 0, (1 << k + k + 1) - 1) if (cnt[j]) t.emplace_back(j);
		REP(j, 0, k) REP(s, 0, (1 << k + k) - 1) if (h[j][s]) for (auto o : t)
		{
			auto c = g[j][s][o];
			if (c.fi <= k) (f[c.fi][c.se] += h[j][s] * cnt[o]) %= MOD;
		}
		for (auto j : t) cnt[j] = 0;
	}

	i64 ans = 0;
	REP(j, 0, k) REP(s, 0, (1 << k + k) - 1) ans += f[j][s];
	cout << ans % MOD << endl;
	return 0;
}
