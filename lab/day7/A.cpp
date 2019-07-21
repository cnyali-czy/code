#define REP(i, s, e) for (int i = s; i <= e ; i++)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 1e6 + 10, maxnode = 21 * maxn;

int n, k, a[maxn];
long long ans;

int rt[maxn], ls[maxnode], rs[maxnode], cnt[maxnode], cur;
#define mid (l + r >> 1)
#define lson ls[p], l, mid
#define rson rs[p], mid + 1, r
void build(int pre, int &p, int l, int r, int pos)
{
	p = ++cur;
	ls[p] = ls[pre];
	rs[p] = rs[pre];
	cnt[p] = cnt[pre] + 1;
	if (l == r) return;
	if (pos <= mid) build(ls[pre], lson, pos);
	else build(rs[pre], rson, pos);
}
int query(int u, int v, int L, int R, int l, int r)
{
	if (L <= l && r <= R) return cnt[v] - cnt[u];
	int ans = 0;
	if (L <= mid) ans += query(ls[u], ls[v], L, R, l, mid);
	if (R >  mid) ans += query(rs[u], rs[v], L, R, mid + 1, r);
	return ans;
}
int query(int l, int r, int L, int R) {return query(rt[l-1], rt[r], L, R, 1, n);}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n)
	{
		scanf("%d", a + i);
		build(rt[i-1], rt[i], 1, n, a[i]);
	}
	REP(i, 1, n)
		REP(j, i + 1, n - 1)
		if (a[j] - 1 >= a[i] + 1) ans += query(j+1, n, a[i]+1, a[j]-1);
	cout << ans << endl;
	return 0;
}
