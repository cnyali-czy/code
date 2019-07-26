#define  REP(i, s, e) for (register int i = s; i <= e; i++)
#define DREP(i, s, e) for (register int i = s; i >= e; i--)

#include <algorithm>
#include <iostream>
#include <cstdio>
using namespace std;
#define int long long
const int maxn = 50000 + 10, maxm = 10 + 5;

int n, m, id[maxn];
char s[maxn];

template <int MOD, int base>
struct hash_table
{
	int bin[maxn], Hash[maxn], dis[maxn], ne[maxn][maxm], last[maxm];
	void init(int n, char s[])
	{
		bin[0] = 1;
		REP(i, 1, n) bin[i] = bin[i-1] * base % MOD;
		REP(i, 1, m) ne[n][i] = n, last[i]=-1;
		DREP(i, n-1, 0)
		{
			REP(j, 1, m) ne[i][j] = ne[i+1][j];
			ne[i][s[i]] = i;
		}
		REP(i, 0, n-1)
		{
			Hash[i+1] = Hash[i] * base % MOD + (dis[i] = i - last[s[i]]), Hash[i+1] %= MOD;
			last[s[i]] = i;
		}
	}
	inline int get(int l, int r)
	{
		int res = Hash[r+1] - Hash[l] * bin[r - l + 1] % MOD;
		REP(i, 1, m)
		{
			int pos = ne[l][i];
			if (pos > r) continue;
			(res -= dis[pos] * bin[r - pos] % MOD) %= MOD;
		}
		return (res + MOD) % MOD;
	}
};
hash_table <(int)1e9 + 7, 103> H1;
hash_table <(int)1e9 + 9, 101> H2;
inline int calc(int x, int y)
{
	if (x > y) swap(x, y);
	int l(1), r(n-y), pos(0);
	while (l <= r)
	{
		int mid = l + r >> 1;
		if (H1.get(x, x + mid - 1) == H1.get(y, y + mid - 1) && H2.get(x, x + mid - 1) == H2.get(y, y + mid - 1))
		{
			pos = mid;
			l = mid + 1;
		}
		else r = mid - 1;
	}
	return pos;
}
inline bool cmp(int x, int y)
{
	int len = calc(x, y);
	return x + len >= n ? 0 : y + len >= n ? 1 : H1.dis[x+len] < H1.dis[y+len];
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	cin >> n >> m;
	scanf("%s", s);
	REP(i, 0, n-1) s[id[i] = i] -= 'a' - 1;
	H1.init(n, s);H2.init(n, s);
	sort(id, id + n, cmp);
	int ans = n * (n + 1) >> 1;
	REP(i, 1, -1+n)
		ans -= calc(id[i-1], id[i]);
	cout << ans << endl;
	return 0;
}
