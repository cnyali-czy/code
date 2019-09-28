#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 300000 + 10, maxm = 1e5 + 10, inf = 0x3f3f3f3f;

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

int n, m, k, a[maxn], tpos1, tpos2;

vector <pair<int, int> > g[maxn];
priority_queue <pair <int, int> > q;

int s[maxn << 2], t[maxn << 2], Max[maxn], Min[maxn], p[maxn], ansl[maxm], ansr[maxm];

#define ls p << 1
#define rs p << 1 | 1
#define mid (l + r >> 1)
#define lson ls, l, mid
#define rson rs, mid + 1, r

void maintain(int p, int l, int r, int val) {s[p] += val;t[p] += val;}
void pushdown(int p, int l, int r)
{
	maintain(lson, t[p]);
	maintain(rson, t[p]);
	t[p] = 0;
}
void update(int p, int l, int r, int L, int R, int val)
{
	if (L <= l && r <= R) maintain(p, l, r, val);
	else
	{
		pushdown(p, l, r);
		if (L <= mid) update(lson, L, R, val);
		if (R >  mid) update(rson, L, R, val);
		s[p] = min(s[ls], s[rs]);
	}
}
int query(int p, int l, int r)
{
	if (l == r) return s[p] ? n + 1 : l;
	else
	{
		pushdown(p, l, r);
		return s[rs] <= s[ls] ? query(rson) : query(lson);
	}
}
void work(int x)
{
	if (x > 1) update(1, 1, n, 1, x - 1, -1);
	update(1, 1, n, x, x, -inf);
	REP(i, 0, (int)g[x].size() - 1) q.push(g[x][i]);
	while (tpos1 && a[Max[tpos1]] <= a[x])
	{
		update(1, 1, n, Max[tpos1 - 1] + 1, Max[tpos1], a[x] - a[Max[tpos1]]);
		tpos1--;
	}
	Max[++tpos1] = x;
	while (tpos2 && a[Min[tpos2]] >= a[x])
	{
		update(1, 1, n, Min[tpos2 - 1] + 1, Min[tpos2], a[Min[tpos2]] - a[x]);
		tpos2--;
	}
	Min[++tpos2] = x;
	while (!q.empty())
	{
		int l = q.top().first, pos = q.top().second;
		if (l < x) update(1, 1, n, l + 1, x, 1);
		int ans = query(1, 1, n);
		if (l < x) update(1, 1, n, l + 1, x, - 1);
		if (ans <= l) ansl[pos] = ans, ansr[pos] = x, q.pop();
		else break;
	}
}

int main()
{
#ifdef CraZYali
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif
	memset(s, inf, sizeof(s));
	cin >> n;
	REP(i, 1, n) a[i] = read<int>();
	cin >> m;
	REP(i, 1, m) g[read<int>()].push_back(make_pair(read<int>(), i));
	REP(i, 1, n) work(i);
	REP(i, 1, m) printf("%d %d\n", ansl[i], ansr[i]);
	return 0;
}
