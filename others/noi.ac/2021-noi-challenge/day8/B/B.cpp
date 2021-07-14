#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdio>
#define int long long

using namespace std;
const int maxn = 100 + 5, maxw = 1e6 + 10, inf = 1e16, MOD = 1e9 + 7, inv2 = MOD + 1 >> 1;

	template <typename T>
inline T read()
{
	T ans = 0, flag = 1;
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int w, h, n, x[maxn], y[maxn];
vector <int> vx, vy;int nx, ny;
int s1[maxw], s2[maxw];
bool f1[maxw], f2[maxw];

bool vis[maxn][maxn];
int real[maxn][maxn], dis[maxn][maxn];
int d[][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
#define fi first
#define se second

void bfs(int sx, int sy)
{
	static pair <int, int> que[maxn * maxn];int head = 0, tail = -1;
	REP(i, 0, nx) REP(j, 0, ny) dis[i][j] = inf;
	dis[sx][sy] = 0;que[++tail] = {sx, sy};
	while (head <= tail)
	{
		int x = que[head].fi, y = que[head].se;head++;
		REP(i, 0, 3)
		{
			int tx = x + d[i][0], ty = y + d[i][1];
			if (tx < 0 || tx > nx || ty < 0 || ty > ny || vis[tx][ty] || dis[tx][ty] <= dis[x][y] + 1) continue;
			dis[tx][ty] = dis[x][y] + 1;que[++tail] = {tx, ty};
		}
	}
}

signed main()
{
#ifdef CraZYali
	file("B");
#endif
	cin >> w >> h >> n;
	vx.emplace_back(1);vx.emplace_back(w + 1);
	vy.emplace_back(1);vy.emplace_back(h + 1);
	REP(i, 1, w) s1[i] = h;
	REP(i, 1, h) s2[i] = w;
	REP(i, 1, n)
	{
		vx.emplace_back(x[i] = read<int>() + 1);vx.emplace_back(x[i] + 1);
		vy.emplace_back(y[i] = read<int>() + 1);vy.emplace_back(y[i] + 1);
		s1[x[i]]--;s2[y[i]]--;
		f1[x[i]] = f2[y[i]] = 1;
	}
	int ans = 0;
	sort(vx.begin(), vx.end());vx.resize(unique(vx.begin(), vx.end()) - vx.begin());nx = vx.size() - 1 - 1;
	sort(vy.begin(), vy.end());vy.resize(unique(vy.begin(), vy.end()) - vy.begin());ny = vy.size() - 1 - 1;
	REP(i, 0, nx) REP(j, 0, ny) real[i][j] = (vx[i + 1] - vx[i]) * (vy[j + 1] - vy[j]) % MOD;

	REP(i, 1, n) vis[lower_bound(vx.begin(), vx.end(), x[i]) - vx.begin()][lower_bound(vy.begin(), vy.end(), y[i]) - vy.begin()] = 1;
	REP(i, 0, nx) REP(j, 0, ny) if (!vis[i][j])
	{
		bfs(i, j);
		int res = 0;
		REP(u, 0, nx) REP(v, 0, ny) if (!vis[u][v]) (res += dis[u][v] * real[u][v]) %= MOD;
		(ans += real[i][j] * res) %= MOD;
	}
	(ans *= inv2) %= MOD;

	REP(i, 1, w) (s1[i] += s1[i - 1]) %= MOD;
	REP(i, 1, h) (s2[i] += s2[i - 1]) %= MOD;
	REP(i, 1, w - 1) if (!f1[i] && !f1[i + 1]) (ans += s1[i] * (s1[w] - s1[i])) %= MOD;
	REP(i, 1, h - 1) if (!f2[i] && !f2[i + 1]) (ans += s2[i] * (s2[h] - s2[i])) %= MOD;

	cout << (ans + MOD) % MOD << endl;
	return 0;
}
