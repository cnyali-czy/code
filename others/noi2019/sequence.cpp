#define REP(i, s, e) for (int i = s; i <= e ;i++)

#include <bits/stdc++.h>
#define int long long
#define chkmax(a, b) a = max(a, b)

using namespace std;
const int maxn = 200 + 5;

int n, k, l;
int a[maxn], b[maxn], ans;
bool pick[maxn], pickA[maxn], pickB[maxn];
void calc()
{
	/*
	cerr << "pick:\t";REP(i,1,n)if(pick[i])cerr<<i<<' ';cerr<<endl;
	cerr << "pickA:\t";REP(i,1,n)if(pickA[i])cerr<<i<<' ';cerr<<endl;
	cerr << "pickB:\t";REP(i,1,n)if(pickB[i])cerr<<i<<' ';cerr<<endl;
	*/
	int res = 0;
	REP(i, 1, n)
		if (pick[i] || pickA[i]) res += a[i];
	REP(i, 1, n)
		if (pick[i] || pickB[i]) res += b[i];
	chkmax(ans, res);
}
void dfs2(int x, int ald = 0)
{
	if (ald > k - l) return;
	if (n - x + ald < k - l) return;
	if (ald == k - l) calc();
	else if (x == n) return;
	else
	{
		x++;
		if (pick[x]) dfs2(x, ald);
		else
		{
			pickB[x] = 1;
			dfs2(x, ald + 1);
			pickB[x] = 0;
			dfs2(x, ald);
		}
	}
}
void dfs1(int x, int ald = 0)
{
	if (ald > k - l) return;
	if (n - x + ald < k - l) return;
	if (ald == k - l) dfs2(0);
	else if (x == n) return;
	else
	{
		x++;
		if (pick[x]) dfs1(x, ald);
		else
		{
			pickA[x] = 1;
			dfs1(x, ald + 1);
			pickA[x] = 0;
			dfs1(x, ald);
		}
	}
}
void dfs(int x, int ald = 0)
{
	if (ald > l) return;
	if (n - x + ald < l) return;
	if (ald == l) dfs1(0);
	else if (x == n) return;
	else
	{
		x++;
		pick[x] = 1;
		dfs(x, ald + 1);
		pick[x] = 0;
		dfs(x, ald);
	}
}

signed main()
{
	freopen("sequence.in", "r", stdin);
	freopen("sequence.out", "w", stdout);
	int T;cin >> T;
	while (T--)
	{
		scanf("%lld%lld%lld", &n, &k, &l);
		REP(i, 1, n) scanf("%lld", a + i);
		REP(i, 1, n) scanf("%lld", b + i);
		ans = 0;
		dfs(0);
		printf("%lld\n", ans);
	}
	return 0;
}
