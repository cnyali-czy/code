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
const int maxn = 1e6 + 10;

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

int n, p[maxn];
long long k;

int main()
{
#ifdef CraZYali
	file("G");
#endif
	cin >> n >> k;
	long long ans(0);
	REP(i, 1, n)
		ans += p[i] = i;
	if (k < ans)
	{
		printf("-1\n");
		return 0;
	}
	k -= ans;
	DREP(i, n, 1)
		if (i > n - i + 1 && k)
		{
			long long tmp = min(i + i - n - 1ll, k);
			k -= tmp;
			ans += tmp;
			swap(p[i], p[i - tmp]);
		}
		else break;
	cout << ans << endl;
	REP(i, 1, n) printf("%d%c", p[i], i == n ? '\n' : ' ');
	REP(i, 1, n) printf("%d%c", i, i == n ? '\n' : ' ');
	return 0;
}
