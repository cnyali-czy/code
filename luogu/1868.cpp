#define REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;
const int maxn = 3e6 + 10, N = 3e6;

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

int l[maxn], r[maxn], n;
int dp[maxn];
vector <int> v[maxn];

int main()
{
#ifdef CraZYali
	file("1868");
#endif
	n = read<int>();
	REP(i, 1, n)
	{
		l[i] = read<int>();r[i] = read<int>();
		v[r[i]].push_back(l[i]);
	}
	REP(i, 1, N)
	{
		dp[i] = dp[i - 1];
		for (auto j : v[i]) chkmax(dp[i], dp[j - 1] + i - j + 1);
	}
	cout << dp[N] << endl;
	return 0;
}
