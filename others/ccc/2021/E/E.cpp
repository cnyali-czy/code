#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1.5e5 + 10;

int n, q;
int l[maxn], r[maxn], v[maxn];

const int prime[] = {2, 3, 5, 7, 11, 13};
int k[6];
int need[6][maxn];

void split(int x)
{
	REP(i, 0, 5)
	{
		k[i] = 0;
		while (x % prime[i] == 0) x /= prime[i], k[i]++;
	}
}
int cur_work;
namespace SMT
{
	int t[6][maxn << 2];
#define ls p << 1
#define rs p << 1 | 1
#define mid (l + r >> 1)
#define lson ls, l, mid
#define rson rs, mid + 1, r
	void update(int p, int l, int r, int L, int R, int P, int v)
	{
		if (L <= l && r <= R)
		{
			t[P][p] = max(t[P][p], v);
			return;
		}
		if (L <= mid) update(lson, L, R, P, v);
		if (R >  mid) update(rson, L, R, P, v);
	}
	void dfs(int p, int l, int r, int v = 0)
	{
		v = max(v, t[cur_work][p]);
		if (l == r) need[cur_work][l] = v;
		else
		{
			dfs(lson, v);
			dfs(rson, v);
		}
	}
	void build(int p, int l, int r)
	{
		if (l == r)
		{
			REP(i, 0, 5) t[i][p] = need[i][l];
			return;
		}
		build(lson);build(rson);
		REP(i, 0, 5) t[i][p] = min(t[i][ls], t[i][rs]);
	}
	int query(int p, int l, int r, int L, int R, int P)
	{
		if (L <= l && r <= R) return t[P][p];
		else
		{
			if (R <= mid) return query(lson, L, R, P);
			if (L >  mid) return query(rson, L, R, P);
			return min(query(lson, L, R, P), query(rson, L, R, P));
		}
	}
}

int main()
{
#ifdef CraZYali
	freopen("E.in", "r", stdin);
	freopen("E.out", "w", stdout);
#endif
	cin >> n >> q;
	REP(i, 1, q)
	{
		scanf("%d%d%d", l + i, r + i, v + i);
		split(v[i]);
		REP(P, 0, 5) if (k[P])
		{
			SMT :: update(1, 1, n, l[i], r[i], P, k[P]);
//			REP(j, l[i], r[i]) need[P][j] = max(need[P][j], k[P]);
		}
	}
	for (cur_work = 0; cur_work < 6; cur_work++) SMT :: dfs(1, 1, n);
	SMT :: build(1, 1, n);
	REP(i, 1, q)
	{
		split(v[i]);
		REP(P, 0, 5)
		{
			int Min = SMT :: query(1, 1, n, l[i], r[i], P);
			if (Min > k[P])
			{
				puts("Impossible");
				return 0;
			}
		}
	}
	static int a[maxn];
	const int LIM = 1e9;
	REP(i, 1, n)
	{
		long long ans = 1;
		REP(P, 0, 5) REP(l, 1, need[P][i])
		{
			ans *= prime[P];
			if (ans > LIM)
			{
				puts("Impossible");
				return 0;
			}
		}
		a[i] = ans;
	}
	REP(i, 1, n)
	{
		printf("%d", a[i]);
		if (i < n) putchar(' ');
	}
	return 0 ;
}
