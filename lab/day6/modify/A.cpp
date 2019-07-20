#define  REP(i, s, e) for (int i = s; i <= e ; i++)
#define DREP(i, s, e) for (int i = s; i >= e ; i--)

#define chkmax(a, b) a = max(a, b)

#include <algorithm>
#include <iostream>
#include <cstdio>
#define int long long
#define double long double

using namespace std;
const int maxn = 3e6 + 10;
const double eps = 1e-8;

int n, a[maxn], id[maxn], rnk[maxn], dp[maxn];
int q[maxn], head, tail;

double K(int j, int k)
{
	return (dp[k] - dp[j]) * 1. / (k - j) ;
}
bool cmp(int x, int y) {return a[x] < a[y];}
int pos[21][maxn];
#define mid (l + r >> 1)
void merge(int l, int r, int d)
{
	if (l == r) pos[d][l] = id[l];
	else
	{
		merge(l, mid, d + 1);
		merge(mid + 1, r, d + 1);
		int p, i = l, j = mid + 1;
		for (p = l; p <= r; p++)
		{
			if (i > mid || j > r) break;
			pos[d][p] = pos[d+1][i] < pos[d+1][j] ? pos[d+1][i++] : pos[d+1][j++];
		}
		while (i <= mid)	pos[d][p++] = pos[d+1][i++];
		while (j <= r)		pos[d][p++] = pos[d+1][j++];
	}
}
bool check (int x, int y, int z) { return (dp[z] - dp[y]) * (y - x) >= (dp[y] - dp[x]) * (z - y); }
void solve(int l, int r, int d)
{
	if (l == r)
	{
		int u = id[l];
		dp[u] += a[u] - u * u;
		return;
	}
	solve(l, mid, d + 1);
	head = 1;tail = 0;
	REP(i, l, r)
	{
		int u = pos[d][i];
		if (rnk[u] <= mid)
		{
			while (head < tail && check(q[tail-1], q[tail], u)) tail--;
			q[++tail] = u;
		}
		else
		{
			while (head < tail && dp[q[head]] + u * q[head] <= dp[q[head+1]] + u * q[head+1]) head++;
			if (head <= tail) chkmax(dp[u], dp[q[head]] + u * q[head]);
		}
	}
	solve(mid + 1, r, d + 1);
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n) scanf("%lld", a + i), id[i] = i;
	sort(id + 1, id + 1 + n, cmp);
	REP(i, 1, n) rnk[id[i]] = i;
	merge(1, n, 0);
	solve(1, n, 0);
	int ans = -n * (n+1) / 2;
	REP(i, 1, n) chkmax(ans, dp[i] + i * (i + 1) / 2 - (n-i) * (n-i+1) / 2);
	cout << ans << endl;
	return 0;
}
