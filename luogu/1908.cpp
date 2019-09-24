#define  REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <queue>

using namespace std;
const int maxn = 5e5 + 10;

template <typename T> T read()
{
	T ans(0), flag(1);
	char c(getchar());
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

int n, a[maxn], t[maxn], p;
long long ans;

#define mid (l + r >> 1)
void cdq(int l, int r)
{
	if (l == r) return;
	cdq(l, mid);cdq(mid + 1, r);
//	REP(i, l, mid) ans += lower_bound(t + 1, t + 1 + p, a[i]) - t - 1;
	int keng = mid;
	REP(i, l, mid)
	{
		while (keng < r && a[i] > a[keng + 1]) keng++;
		ans += keng - mid;
	}
	int i, j;
	p = l-1;
	i = l;j = mid + 1;
	while (i <= mid && j <= r)
		if (a[i] <= a[j]) t[++p] = a[i++];
		else t[++p] = a[j++];
	while (i <= mid)	t[++p] = a[i++];
	while (j <= r)		t[++p] = a[j++];
	copy(t + l, t + r + 1, a + l);
}

int main()
{
#ifdef CraZYali
	file("1908");
#endif
	cin >> n;
	REP(i, 1, n) a[i] = read<int>();
	cdq(1, n);
	cout << ans << endl;
	return 0;
}
