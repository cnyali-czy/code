#define DREP(i, s, e) for(register long long i = s; i >= e ;i--)
#define  REP(i, s, e) for(register long long i = s; i <= e ;i++)

#define DEBUG fprlong longf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <queue>
#include <map>
#include <set>

using namespace std;
const long long maxn = 100010;

template <typename T> T read()
{
	T ans(0), p(1);
	char c = getchar();
	while (!isdigit(c)) {
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c)) {
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}
const long long inf = (((1 << 30) - 1) << 1) + 1;

long long vis[300][300][300];
long long ans, a, b, c, d, rd;

#define MIN(x, y, z) min(min(x, y), z)

inline void dfs(long long A, long long B, long long C, long long cost)
{
	if (A < 0 || A > 200 || B < 0 || B > 200 || C < 0 || C > 200) return;
	fprintf(stderr, "%lld %lld %lld %lld\n", A, B, C, cost);
	if (vis[A][B][C] <= cost) return;
	vis[A][B][C] = vis[A][C][B] = vis[B][A][C] = vis[B][C][A] = vis[C][A][B] = vis[C][B][A] = cost;
	long long now = MIN(A, B, C);
	if (abs(d - now) < abs(d - rd))
	{
		rd = now;
		ans = cost;
	}
	else if (abs(d - now) == abs(d - rd)) chkmin(ans, cost);
	dfs(0, A + B, C, cost + A);
	dfs(A + B - 200, 200, C, cost + B - 200);
	dfs(0, B, A + C, cost + A);
	dfs(A + C - 200, B, 200, cost + C - 200);
	dfs(A + B, 0, C, cost + B);
	dfs(200, A + B - 200, C, cost + A - 200);
	dfs(A, 0, B + C, cost + B);
	dfs(A, B + C - 200, 200, cost + C - 200);
	dfs(A + C, B, 0, cost + C);
	dfs(200, B, A + C - 200, cost + A - 200);
	dfs(A, B + C, 0, cost + C);
	dfs(A, 200, B + C - 200, cost + B - 200);
}
signed main()
{
#ifdef CraZYali
	freopen("10603.in", "r", stdin);
	freopen("10603.out", "w", stdout);
#endif
	register long long T = read<long long>();
	while (T--)
	{
		ans = inf;
		a = read<long long>();
		b = read<long long>();
		c = read<long long>();
		d = read<long long>();
		rd = inf;
		memset(vis, 127 / 3, sizeof(vis));
		dfs(a, b, c, 0);
		printf("%lld %lld\n", rd, ans);
	}

	return 0;
}
