#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 20000 + 10, maxm = 20000 + 10;

template <typename T> T read()
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

int m, n, k;
int a[maxn], b[maxn];

int main()
{
	freopen("eat.in", "r", stdin);
	freopen("eat.out", "w", stdout);
	n = read<int>();
	m = read<int>();
	REP(i, 1, n) a[i] = read<int>();
	REP(i, 1, m) b[i] = read<int>();
	sort(a + 1, a + 1 + n);
	sort(b + 1, b + 1 + m);
	int ans = 0;
	REP(i, 1, n)
	{
		int l, r, res = 0;
		l = 1; r = m;
		while (l <= r)
		{
			int mid = l + r >> 1;
			if (a[i] > b[mid])
			{
				res = mid;
				l = mid + 1;
			}
			else r = mid - 1;
		}
		ans += res;
	}
	cout << ans;

	return 0;
}
