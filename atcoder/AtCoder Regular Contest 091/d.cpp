#define  REP(i, s, e) for(register long long i = s; i <= e ;i++)
#define DREP(i, s, e) for(register long long i = s; i >= e ;i--)

#define DEBUG fprlong longf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;

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

long long n, k, ans;

int main()
{
#ifdef CraZYali
	freopen("d.in", "r", stdin);
	freopen("d.out", "w", stdout);
#endif
	cin >> n >> k;
	if (!k) {cout << n * n;return 0;}
	REP(i, k + 1, n)
	{
		ans += (i - k) * ((n - i + 1) / i + 1);
		if ((n - k) / i != (n - i + 1) / i) ans += (n - k) % i + 1;
//		if (n % i - k + 1 >= 0) ans += n % i - k + 1;
//		prlong longf("%d %d\n", i, i - k + k * ((n - i) / i) + n % i + 1 - k);
	}
	cout << ans;
	return 0;
}
