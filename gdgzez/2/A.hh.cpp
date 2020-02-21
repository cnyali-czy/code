#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxm = 400 + 10 << 1, MOD = 1e9 + 7;

int power_pow(long long base, int b)
{
	long long ans(1);
	while (b)
	{
		if (b & 1) (ans *= base) %= MOD;
		(base *= base) %= MOD;
		b >>= 1;
	}
	return (ans + MOD) % MOD;
}
#define inv(x) power_pow(x, MOD - 2)

int m, k, s;
int ans, l[maxm], r[maxm];

pair <int, int> p[maxm];

namespace solve2
{
	inline int work()
	{
		int ans(0);
		REP(i, 1, m + m)
			REP(j, 1, m + m)
			if (p[i].first + p[j].first <= s) (ans += 1ll * p[i].second * p[j].second * (s - p[i].first - p[j].first + 1)) %= MOD;
		if (s % 2 == 0)
			REP(i, 1, m + m)
				if (p[i].first + p[i].first <= s) (ans -= p[i].second) %= MOD;
		return (ans *= inv(2)) %= MOD;
	}
}
pair <int, int> p2[maxm * maxm];int cur;
inline int c2(long long x) {return x * (x-1) / 2 % MOD;}
namespace solve3
{
	inline int calc1()
	{
		int res(0), s1(0), s2(0), s3(0), j(1);
		DREP(i, m + m, 1)
			if (p[i].first <= s)
			{
				while (p[i].first + p2[j].first <= s && j <= cur)
				{
					(s1 += p2[j].second) %= MOD;
					(s2 -= 1ll * p2[j].second * p2[j].first) %= MOD;
					(s3 += 1ll * p2[j].second * c2(p2[j].first + 1)) %= MOD;
					j++;
				}
				int len = s - p[i].first + 2;
				(res += (1ll * s1 * c2(len) % MOD + 1ll * len * s2 % MOD + s3) % MOD * p[i].second) %= MOD;
			}
		return res;	
	}
	inline int calc2()
	{
		int res(0);
		REP(i, 1, m + m)
			REP(j, 1, m + m)
			if (p[i].first + p[i].first + p[j].first <= s)
				(res += 1ll * ((s - p[i].first - p[i].first - p[j].first) / 2 + 1) * p[j].second * p[i].second) %= MOD;
		return res;
	}
	inline int calc3()
	{
		int res(0);
		if (s % 3 == 0)
			REP(i, 1, m + m)
				if (3 * p[i].first <= s) (res += p[i].second) %= MOD;
		return res;
	}
	inline int work() {return 1ll * inv(6) * (calc1() - 3ll * calc2() % MOD + 2ll * calc3() % MOD) % MOD;	}
}
namespace solve4
{
	inline int work()
	{}
}
inline bool cmp(pair <int, int> A, pair <int, int> B) {return A.first < B.first;}

int main()
{
#ifdef CraZYali
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	cin >> m >> k >> s;
	REP(i, 1, m) scanf("%d%d", l + i, r + i);
	REP(i, 1, m) p[i] = make_pair(l[i], 1), p[i + m] = make_pair(r[i] + 1, -1);
	sort(p + 1, p + m + m + 1, cmp);
	REP(i, 1, m + m)
		REP(j, 1, m + m) p2[++cur] = make_pair(p[i].first + p[j].first, p[i].second * p[j].second);
	sort(p2 + 1, p2 + cur + 1, cmp);
	if (k == 2) ans = solve2::work();
	if (k == 3) ans = solve3::work();
	if (k == 4) ans = solve4::work();
	cout << (ans + MOD) % MOD << endl;
	return 0;
}
