#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <algorithm>
#include <cstring>
#include <iostream>
#include <cstdio>
#define int long long
using namespace std;
const int maxn = 2e5 + 10;

template <typename T>
inline T read()
{
	register T ans(0), flag(1);
	register char c(getchar());
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

int bg[maxn], ne[maxn], to[maxn], w[maxn], e = 1;
inline void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
}

int n, pig, x[maxn];
inline void chkmax(int &x, int y) {if (x < y) x = y;}
const int inf = 1e15;
namespace bf
{
	int dp[1 << 10];
	inline bool check(int a)
	{
		memset(dp, -1, sizeof dp);
		dp[1] = a;
		REP(S, 1, (1 << n) - 1) if (dp[S] > 0)
			REP(x, 1, n)
				if (S & (1 << x - 1))
					for (int i = bg[x]; i; i = ne[i])
						if (!(S & (1 << to[i] - 1)) && w[i] <= dp[S])
							chkmax(dp[S | (1 << to[i] - 1)], dp[S] - w[i] + ::x[to[i]]);
		REP(S, 1, (1 << n) - 1)
			if (dp[S] > 0 && S & (1 << pig - 1)) return 1;
		return 0;
	}
	int main()
	{
		int l(1), r(1e18);
		while (l <= r)
		{
			int mid = l + r >> 1;
			if (check(mid)) r = mid - 1;
			else l = mid + 1;
		}
		cout << r + 1 << endl;
		return 0;
	}
}
namespace lian
{
	bool check(int a)
	{
		REP(i, 2, n)
		{
			if (w[i] > a) return 0;
			a -= w[i];a += x[i];
			if (x[i] == inf) return 1;
		}
		return -233;
	}
	int main()
	{
		int l(1), r(1e18);
		while (l <= r)
		{
			int mid = l + r >> 1;
			if (check(mid)) r = mid - 1;
			else l = mid + 1;
		}
		cout << r + 1 << endl;
		return 0;
	}
}
namespace flower
{
	int id[maxn];
	bool check(int a)
	{
		REP(i, 2, n)
			if (a >= w[id[i]] && w[id[i]] <= x[to[id[i]]])
			{
				a -= w[id[i]];a += x[to[id[i]]];
				if (to[id[i]] == pig) return 1;
			}
		return 0;
	}
	int main()
	{
		REP(i, 2, n) id[i] = i;
		sort(id + 2, id + 1 + n, [&](int x, int y) {return w[x] < w[y];});
		int l(1), r(1e18);
		while (l <= r)
		{
			int mid = l + r >> 1;
			if (check(mid)) r = mid - 1;
			else l = mid + 1;
		}
		cout << r + 1 << endl;
		return 0;
	}
}
signed main()
{
#ifdef CraZYali
	freopen("prospecting.in", "r", stdin);
	freopen("prospecting.out", "w", stdout);
#endif
	cin >> n;
	bool islian(1);
	bool isflower(1);
	REP(i, 2, n)
	{
		int p(read<int>() + 1), _x(read<int>()), y(read<int>());
		islian &= (p == i - 1);
		isflower &= (p == 1);
		add(p, i, y);
		x[i] = _x;
		if (x[i] < 0) x[pig = i] = inf + 1;
	}
	if (n <= 10) return bf::main();
	if (isflower) return flower::main();
	if (islian) return lian::main();
	return 0;
}
