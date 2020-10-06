#define REP(i, s, e) for (register i64 i = (s), end_##i = (e); i <= end_##i; i++)
#define DEP(i, s, e) for (register i64 i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;
const int maxn = 1e5 + 10;
#define i64 long long

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

int n;
i64 l[maxn], r[maxn], ans;
const i64 lim = (1ll << 62) - 1;
void dfs(int x, i64 cur = lim)
{
	if (x == n) chkmax(ans, cur);
	else
	{
		x++;
		REP(i, l[x], r[x]) dfs(x, cur & i);
	}
}

int main()
{
#ifdef CraZYali
	freopen("A.in", "r", stdin);
	freopen("bf.out", "w", stdout);
#endif
	n = read<int>();
	REP(i, 1, n) l[i] = read<i64>(), r[i] = read<i64>();
	dfs(0);
	cout << ans << endl;
	return 0;
}
