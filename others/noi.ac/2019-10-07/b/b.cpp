//orz ljf
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 5000 + 10;
const double eps = 1e-7;

inline char Getchar()
{
    static char buf[100000], *p1(buf), *p2(buf);
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
}
template <typename T>
inline T read()
{
	register char c(Getchar());
	register T res(0);
	while (!isdigit(c)) c = Getchar();
	while (isdigit(c))
	{
		res = res * 10 + c - 48;
		c = Getchar();
	}
	return res;
}

int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
inline void add(const int &x, const int &y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}
inline void Add(const int &x, const int &y) {add(x, y), add(y, x);}

int n, limit, v[maxn], T;

int stack[maxn], p, val[maxn];
double ans, dp[maxn][2];

void dfs(const int &x, const int &fa, const double &cost)
{
	register double t1(0), t2(0), t3(0);
	for (register int i(bg[x]); i; i = ne[i]) if (to[i] ^ fa)
	{
		dfs(to[i], x, cost);
		t3 = max(t3 + dp[to[i]][0], t2 + dp[to[i]][1]);
		t2 = max(t2 + dp[to[i]][0], t1 + dp[to[i]][1]);
		t1 += dp[to[i]][0];
	}
	dp[x][0] = max(max(t1, max(t2, t3) + val[x] - cost), .0);
	dp[x][1] = max(t1, t2) + val[x];
}

#define judge(cost) (dfs(1, -1, cost), dp[1][0] >= cost)

int main()
{
#ifdef CraZYali
	freopen("b.in", "r", stdin);
	freopen("b.out", "w", stdout);
#endif
	n = read<int>();
	limit = read<int>();
	register const int MOD = limit;
	register const double inf = n * (MOD - 1) / 2;
	REP(i, 1, n) v[i] = read<int>();
	REP(i, 2, n)
		Add(read<int>(), read<int>());
	stack[++p] = T = read<int>();
	REP(i, 1, n)
		if (v[i] + T >= limit) stack[++p] = limit - v[i] - 1;
	srand(19260817);
	random_shuffle(stack + 1, stack + 1 + p);
	REP(i, 1, p)
	{
		REP(j, 1, n) val[j] = (v[j] + stack[i]) % MOD;
		if (!judge(ans + eps))
			continue;
		register double l(ans), r(inf);
		while (r - l > eps)
		{
			register double mid = (l + r) / 2;
			if (judge(mid)) l = mid;
			else r = mid;
		}
		ans = l;
	}
	printf("%.8lf\n", ans);
	return 0;
}
