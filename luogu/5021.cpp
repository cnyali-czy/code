#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 50000 + 10, maxm = maxn;

int bg[maxn], ne[maxm << 1], to[maxm << 1], w[maxm << 1], e = 1;
inline void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
}

template <typename T> inline T read()
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

template <typename T> void write(T x)
{
	if (x < 0) putchar('-'), write(-x);
	else
	{
		if (x / 10) write(x / 10);
		putchar(x % 10 + '0');
	}
}

int m, n, L, R, ans;

int dfs(int x, int fa, int &len, int lim)
{
	register int ret = 0;
	multiset <int> S;
	multiset <int> :: iterator it;
	for (register int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ fa)
		{
			int res;
			ret += dfs(to[i], x, res, lim);
			res += w[i];
			if (res >= lim) ret++;
			else S.insert(res);
		}
	len = 0;
	while (!S.empty())
	{
		int res = *S.begin();
		S.erase(S.begin());
		it = S.lower_bound(lim - res);
		if (it != S.end())
		{
			S.erase(it);
			ret++;
		}
		else chkmax(len, res);
	}
	return ret;
}

int main()
{
#ifdef CraZYali
	freopen("5021.in", "r", stdin);
	freopen("5021.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 2, n)
	{
		register int x = read<int>(), y = read<int>(), z = read<int>();
		add(x, y, z);add(y, x, z);
		R += z;
	}
	while (L <= R)
	{
		register int mid = L + R >> 1, res;
		if (dfs(1, -1, res, mid) >= m) ans = mid, L = mid + 1;
		else R = mid - 1;
	}
	cout << ans;

	return 0;
}
