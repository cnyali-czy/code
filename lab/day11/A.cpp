#define REP(i, s, e) for (int i = s; i <= e; i++)

#include <bits/stdc++.h>
using namespace std;
const int maxn = 50 + 5, maxm = 50 + 5, MOD = 1e9 + 7;

unordered_map <unsigned long long, bool> vis;

int n, m, k, ans, a[maxn][maxm], v[maxn][maxm];

int p1[maxn], p2[maxm];

const unsigned long long P = 19260817;
unsigned long long Hash()
{
	unsigned long long H(0);
	REP(i, 1, n)
		REP(j, 1, m) H = H * P + a[p1[i]][p2[j]];
	return H;
}

void calc()
{
	REP(i, 1, n) p1[i] = i;
	do
	{
		REP(i, 1, m) p2[i] = i;
		do
			if (vis[Hash()]) goto end;
		while (next_permutation(p2 + 1, p2 + 1 + m));
	}while (next_permutation(p1 + 1, p1 + 1 + n));
	REP(i, 1, n) p1[i] = i;
	do
	{
		REP(i, 1, m) p2[i] = i;
		do
			vis[Hash()] = 1;
		while (next_permutation(p2 + 1, p2 + 1 + m));
	}while (next_permutation(p1 + 1, p1 + 1 + n));
	ans++;if (ans >= MOD) ans %= MOD;
end:return;
}

void dfs(int x, int y)
{
	if (x == n && y == m) calc();
	else
	{
		if (y == m) x++, y = 1;
		else y++;
		REP(i, 1, k) a[x][y] = i, dfs(x, y);
	}
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	cin >> n >> m >> k;
	dfs(1, 0);
	cout << ans % MOD << endl;
	return 0;
}
