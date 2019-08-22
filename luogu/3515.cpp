#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) (a = max(a, b), a == b)
#define chkmin(a, b) (a = min(a, b), a == b)

#include <iostream>
#include <cstdio>
#include <cmath>
#define int long long
using namespace std;
const int maxn = 5e5 + 10;
template <typename T> inline T read()
{
	T ans(0), p(1);
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}

int n, a[maxn];

int best[maxn], ans[maxn];
void solve1(int l, int r, int L, int R)
	//ans \in [L, R]
{
	if (l > r) return;
	int mid = l + r >> 1;
	int &pos = best[mid];
	pos = mid;
	REP(i, L, min(mid - 1, R))
		if (a[pos] + sqrt(mid-pos) < a[i] + sqrt(mid-i)) pos = i;
	chkmax(ans[mid], a[pos] + (int)ceil(sqrt(mid-pos)) - a[mid]);
	solve1(l, mid - 1, L, pos);
	solve1(mid + 1, r, pos, R);
}
void solve2(int l, int r, int L, int R)
	//ans \in [L, R]
{
	if (l > r) return;
	int mid = l + r >> 1;
	int &pos = best[mid];
	pos = mid;
	REP(i, max(L, mid), R)
		if (a[pos] + sqrt(pos-mid) < a[i] + sqrt(i-mid)) pos = i;
	chkmax(ans[mid], a[pos] + (int)ceil(sqrt(pos-mid)) - a[mid]);
	solve2(l, mid - 1, L, pos);
	solve2(mid + 1, r, pos, R);
}

signed main()
{
#ifdef CraZYali
	freopen("3515.in", "r", stdin);
	freopen("3515.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n) a[i] = read<int>();
	solve1(1, n, 1, n);
	solve2(1, n, 1, n);
	REP(i, 1, n) printf("%lld\n", ans[i]);
	return 0;
}
