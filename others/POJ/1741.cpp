#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 1000 + 10, maxm = 1000 + 10;

int n, m, k;

int bg[maxn], ne[maxm << 1], to[maxm << 1], w[maxm << 1], e = 1;
inline void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
}

bool del[maxn];

int dis[maxn];

vector <int> v;
void getdis(int x, int fa = -1)
{
	for (register int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ fa && !del[to[i]])
		{
			v.push_back(dis[to[i]] = dis[x] + w[i]);
			getdis(to[i], x);
		}
}

int ans;

int calc(int x, int now)
{
	vector<int>().swap(v);
	v.push_back(dis[x] = now);
	getdis(x);
	sort(v.begin(), v.end());
	register int l = 0, r = (int)v.size() - 1, res = 0;
	while (l < r)
		if (v[l] + v[r] + 2 * now <= k) res += r - l, l++;
		else r++;
	return res;
}

int sum[maxn], Sum, Min, Minid;
int dp[maxn];

void dfs1(int x, int fa)
{
	sum[x] = 1;
	dp[x] = 0;
	for (register int i = bg[x]; i ; i = ne[i])
		if (!del[to[i]] && to[i] ^ fa)
		{
			dfs1(to[i], x);
			sum[x] += sum[to[i]];
			chkmax(dp[x], sum[to[i]]);
		}
}

void dfs2(int x, int fa)
{
	int temp = max(dp[x], Sum - sum[x]);
	if (temp < Min)
	{
		Min = temp;
		Minid = x;
	}
	for (register int i = bg[x]; i ; i = ne[i])
		dfs2(to[i], x);
}

int getroot(int x)
{
	dfs1(x, 0);
	Sum = sum[x];
	Min = 1e9;
	Minid = -1;
	dfs2(x, 0);
	return Minid;
}

void solve(int x)
{
	register int root = getroot(x);
	ans += calc(root, 0);
	del[root] = 1;
	for (register int i = bg[x]; i ; i = ne[i])
		if (!del[to[i]])
		{
			ans -= calc(getroot(to[i]), w[i]);
			solve(to[i]);
		}
}

int main()
{
#ifdef CraZYali
	freopen("1741.in", "r", stdin);
	freopen("1741.out", "w", stdout);
#endif
	while (scanf("%d%d", &n, &k) * (n + k))
	{
		e = 1;
		REP(i, 1, n) bg[i] = del[i] = 0;
		REP(i, 2, n)
		{
			register int x, y, z;
			scanf("%d%d%d", &x, &y, &z);
			add(x, y, z);add(y, x, z);
		}
		ans = 0;
		solve(1);
		printf("%d\n", ans);
	}

	return 0;
}
