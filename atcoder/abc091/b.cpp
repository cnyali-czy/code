#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 200, maxm = 200;

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

int m, n, ans;

string a[maxn], b[maxm];

int main()
{
#ifdef CraZYali
	freopen("b.in", "r", stdin);
	freopen("b.out", "w", stdout);
#endif
	ios::sync_with_stdio(false);
	cin >> n;
	REP(i, 1, n) cin >> a[i];
	cin >> m;
	REP(i, 1, m) cin >> b[i];
	REP(i, 1, n)
	{
		int temp = 0;
		REP(j, 1, n) temp += a[i] == a[j];
		REP(j, 1, m) temp -= a[i] == b[j];
		chkmax(ans, temp);
	}

	REP(i, 1, m)
	{
		int temp = 0;
		REP(j, 1, m) temp -= b[i] == b[j];
		REP(j, 1, n) temp += b[i] == a[j];
		chkmax(ans, temp);
	}
	cout << ans;
	return 0;
}

