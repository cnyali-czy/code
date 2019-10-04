#define  REP(i, s, e) for (int i(s), end_##i(e); i <= end_##i; i++)
#define DREP(i, s, e) for (int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <ext/pb_ds/priority_queue.hpp>
#include <tr1/unordered_map>

using namespace std;

using namespace std;
const int maxn = 1e6 + 10, maxq = 1e5 + 10;

long long n, x, a, b, c, Mod, q;

tr1 :: unordered_map <int, long long> cnt;
__gnu_pbds :: priority_queue <int> Q;

inline void insert(int val, long long t = 1)
{
	if (cnt.find(val) == cnt.end()) Q.push(val);
	cnt[val] += t;
}
long long sum[30000000];
int t[30000000];

pair <long long, int> qry[maxq];
int ans[maxn];
pair <int, long long> tnt[30000000];


int main()
{
#ifdef CraZYali
	freopen("seat.in", "r", stdin);
	freopen("seat.out", "w", stdout);
#endif
	cin >> n >> x >> a >> b >> c >> Mod;
	const long long MOD = Mod;
	REP(i, 1, n)
	{
		insert(x);
		x = (MOD + (a * x % MOD * x % MOD + b * x % MOD + c) % MOD) % MOD + 1;
	}
	while (!Q.empty())
	{
		register int qaq = Q.top();
		Q.pop();
		if (qaq == 2) break;
		else if (qaq == 3) continue;
		if (qaq & 1)
			insert(qaq / 2, cnt[qaq] * 2);
		else
		{
			insert(qaq / 2, cnt[qaq]);
			insert(qaq / 2 - 1, cnt[qaq]);
		}
	}
	n = cnt.size();
//	for (register auto i : cnt) tnt[++n] = i;
	copy(cnt.begin(), cnt.end(), tnt + 1);
//	REP(i, 1, n) printf("%d %lld\n", tnt[i].first, tnt[i].second);
	sort(tnt + 1, tnt + n + 1, greater <pair <int, long long> >() );
//	REP(i, 1, n) printf("%d %lld\n", tnt[i].first, tnt[i].second);

	REP(i, 1, n)
	{
		sum[i] = sum[i-1] + tnt[i].second;
		t[i] = tnt[i].first;
	}
	cin >> q;
	REP(i, 1, q)
	{
		register long long x;
		scanf("%lld", &x);
		qry[i] = make_pair(x, i);
	}
	sort(qry + 1, qry + 1 + q);
	int j(1);
	t[n+1] = 1;
	REP(i, 1, q)
	{
		while (j <= n && sum[j] < qry[i].first) j++;
		if (j == n + 1)
		{
			while (i <= q) ans[qry[i++].second] = 1;
			break;
		}
		ans[qry[i].second] = t[j];
	}
	REP(i, 1, q) printf("%d\n", ans[i]);
	return 0;
}
