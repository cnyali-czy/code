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

long long m, n, k;
int main()
{
	freopen("copy.in", "r", stdin);
	freopen("copy.out", "w", stdout);
	cin >> n;
	long long cnt = 1ll, ans = 0ll;
	while (cnt < n)
	{
		cnt <<= 1ll;
		ans++;
	}
	cout << ans;

	return 0;
}
