#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %lld\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>
#define int long long

using namespace std;
const int maxn = 1e5 + 10;

template <typename T> T read()
{
	T ans = 0, p = 1;
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

int n, a[maxn], b[maxn];
bool judge(int mid)
{
	REP(i, 1, n) b[i] = a[i];
	b[1] -= mid;
	REP(i, 2, n)
		if (b[i-1] < b[i]) b[i] = max(b[i-1] + 1, b[i] - mid);
		else if (b[i] + mid <= b[i-1]) return 0;
		else b[i] = b[i-1] + 1;
	return 1;
}

signed main()
{
#ifdef CraZYali
	freopen("F.in", "r", stdin);
	freopen("F.out", "w", stdout);
#endif
	int T = read<int>();
	REP(Case, 1, T)
	{
		n = read<int>();
		REP(i, 1, n) a[i] = read<int>();
		int l(0), r(2e9), ans(2e9);
		while (l <= r)
		{
			int mid = l + r >> 1;
			if (judge(mid)) r = (ans = mid) - 1;
			else l = mid + 1;
		}
		printf("Case #%lld:\n%lld\n", Case, ans);
	}
	return 0;
}
