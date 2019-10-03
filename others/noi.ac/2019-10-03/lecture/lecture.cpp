#define  REP(i, s, e) for (int i(s), end_##i(e); i <= end_##i; i++)
#define DREP(i, s, e) for (int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <set>

using namespace std;
const int maxn = 1e5 + 10;

int n;
long long x[maxn], l[maxn], r[maxn];

set <pair <long long, long long> > s;
long long ans;

void doit(long long l, long long r, long long ext) 
{
	long long lb = l, rb = r;
	while (1) 
	{
		auto it = s.lower_bound(make_pair(l, 0ll));
		if (it == s.begin()) break;
		--it;
		if (it -> second - it -> first < ext) s.erase(it);
		else 
		{
			long long ll(max(lb, it -> first));
			long long rr(min(rb, it -> second));
			long long len(rr - ll + 1 - ext);
			if (len < 0) break;
			s.erase(it);
			ans += len;
			chkmin(l, it -> first);
			chkmax(r, it -> second);
		}
	}
	while (1) 
	{
		auto it = s.lower_bound(make_pair(l, 0));
		if (it == s.end()) break;
		if (it -> second - it -> first < ext) s.erase(it);
		else 
		{
			long long ll(max(lb, it -> first));
			long long rr(min(rb, it -> second));
			long long len(rr - ll + 1 - ext);
			if (len < 0) break;
			s.erase(it);
			ans += len;
			chkmax(r, it -> second);
		}
	}
	s.insert(make_pair(l, r));
}

int id[maxn];

int main() 
{
#ifdef CraZYali
	freopen("lecture.in", "r", stdin);
	freopen("lecture.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n) scanf("%d %d %d", x + i, l + i, r + i);
	REP(i, 1, n) id[i] = i;

	auto qaq = [](int a, int b) {return x[a] < x[b] || x[a] == x[b] && l[a] < l[b];};
	sort(id + 1, id + 1 + n, qaq);
	REP(i, 1, n)
		doit(l[id[i]] - x[id[i]], r[id[i]] + x[id[i]], 2ll * x[id[i]]);
	cout << ans << endl;
	return 0;
}
