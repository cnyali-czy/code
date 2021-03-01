#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 10000 + 10;

int n, w[maxn], h[maxn];
inline int read() {int x;scanf("%d", &x);return x;}

int main()
{
#ifdef CraZYali
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n + 1) h[i] = read();
	long long ans = 0;
	REP(i, 1, n)
	{
		long long w = read();
		ans += w * (min(h[i], h[i + 1]) * 2ll + max(h[i + 1] - h[i], h[i] - h[i + 1]));
	}
	if (ans & 1) printf("%lld.5", ans / 2);
	else printf("%lld", ans / 2);
	return 0;
}
