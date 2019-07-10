#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>
#define int long long

using namespace std;
const int maxn = 3e5 + 10, maxm = 3e5 + 10, maxN = maxn + maxm, maxnode = 10000000;

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

int rt[maxN], ls[maxnode], rs[maxnode], cnt[maxnode], sum[maxnode], cur;

#define mid (l + r >> 1)
#define lson ls[p], l, mid
#define rson rs[p], mid + 1, r

void update(int pre, int &p, int l, int r, int val)
{
	p = ++cur;
	ls[p] = ls[pre];
	rs[p] = rs[pre];
	sum[p] = sum[pre] + val;
	cnt[p] = cnt[pre] + (val >= 0 ? 1 : -1);
	if (l == r) return;
	if (abs(val) <= mid) update(ls[pre], lson, val);
	else update(rs[pre], rson, val);
}

int n, m, k, lastans = 1;
vector <int> v[maxn];
int id[maxn];

int query(int p, int l, int r, int val)
{
	if (l == r) return val * l;
	if (val <= cnt[ls[p]]) return query(lson, val);
	else return sum[ls[p]] + query(rson, val - cnt[ls[p]]);
}

signed main()
{
#ifdef CraZYali
	freopen("3168.in", "r", stdin);
	freopen("3168.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, n)
	{
		int s(read<int>()), e(read<int>()), p(read<int>());
		chkmax(k, p);
		v[s].push_back(p);v[e+1].push_back(-p);
	}
	REP(i, 1, m)
	{
		int siz = (int)v[i].size() - 1;
		DREP(j, siz, 0)
		{
			id[0]++;
			update(rt[id[0]-1], rt[id[0]], 1, k, v[i][j]);
		}
		id[i] = id[0];
	}
	REP(i, 1, m)
	{
		int x(read<int>()), a(read<int>()), b(read<int>()), c(read<int>());
		int K = (a * lastans + b) % c + 1, pos = rt[id[x]];
		printf("%lld\n", lastans = (cnt[pos] <= K ? sum[pos] : query(pos, 1, k, K)));
	}

	return 0;
}
