#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxc = 1000 * 100 + 10;

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

int n, c;
int dp[maxc];

int main()
{
	freopen("chicken.in", "r", stdin);
	freopen("chicken.out", "w", stdout);
	n = read<int>();
	c = read<int>();
	while (n--)
	{
		int a(read<int>()), m(read<int>()), v(read<int>());
		while (a--)
			DREP(i, c, m)
				chkmax(dp[i], dp[i - m] + v);
	}
	cout << dp[c];
	return 0;
}
