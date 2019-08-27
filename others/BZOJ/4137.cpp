#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;
const int maxn = 100000 + 10, maxN = maxn * 18, D = 16;

int n, m, tim, Q;
int bin[17], rt[maxn], ans[maxn], st[maxn];
struct question{int l, r, tl, tr, x;}q[maxn];
struct event
{
	int id, v, t;
	inline bool operator < (event B) const {return id < B.id;}
}e[maxn], e1[maxn], e2[maxn];

int cur, ch[maxN][2], cnt[maxN];
#define flag (!!(num & bin[d]))
void insert(int pre, int &p, int num, int d)
{
	p = ++cur;
	ch[p][0] = ch[pre][0];
	ch[p][1] = ch[pre][1];
	cnt[p] = cnt[pre] + 1;
	if (d == -1) return;
	insert(ch[pre][flag], ch[p][flag], num, d - 1);
}
int query(int x, int y, int num, int d) {return d == -1 ? 0 : cnt[ch[y][flag ^ 1]] - cnt[ch[x][flag ^ 1]] ? query(ch[x][flag ^ 1], ch[y][flag ^ 1], num, d - 1) + bin[d] : query(ch[x][flag], ch[y][flag], num, d - 1);}

vector<int> events[maxn << 2];
#define mid (l + r >> 1)
#define ls p << 1
#define rs p << 1 | 1
#define lson ls, l, mid
#define rson rs, mid + 1, r
void pushdown(int p, int l, int r, int L, int R, int id)
{
	if (l > r) return;
	if (L <= l && r <= R) return events[p].push_back(id), void();
	if (L <= mid) pushdown(lson, L, R, id);
	if (R >  mid) pushdown(rson, L, R, id);
}
void work(int p, int l, int r)
{
	cur = 0;
	int top(0), i1(0), i2(0);
	REP(i, l, r)
	{
		st[++top] = e[i].id;
		insert(rt[top-1], rt[top], e[i].v, D);
	}
	int siz = (int)events[p].size() - 1;
	REP(i, 0, siz)
		chkmax(ans[events[p][i]], query(rt[lower_bound(st + 1, st + 1 + top, q[events[p][i]].l) - st - 1], rt[upper_bound(st + 1, st + 1 + top, q[events[p][i]].r) - st - 1], q[events[p][i]].x, D));
	if (l == r) return;
	REP(i, l, r)
		if(e[i].t <= mid) e1[++i1] = e[i];
		else e2[++i2] = e[i];
	copy(e1 + 1, e1 + 1 + i1, e + l);
	copy(e2 + 1, e2 + 1 + i2, e + l + i1);
	work(lson);work(rson);
}
int opt, l, r, x, d;
int main()
{
#ifdef CraZYali
	freopen("4137.in", "r", stdin);
	freopen("4137.out", "w", stdout);
#endif
	bin[0] = 1;
	REP(i, 1, D) bin[i] = bin[i-1] << 1;
	cin >> n >> m;
	REP(i, 1, n)
	{
		scanf("%d", &x);
		insert(rt[i-1], rt[i], x, D);
	}
	tim=1;
	REP(i, 1, m)
	{
		scanf("%d", &opt);
		if(opt)
		{
			scanf("%d%d%d%d", &l, &r, &x, &d);
			q[++Q] = question{l, r, max(1, tim - d + 1), tim, x};
			ans[Q] = query(rt[l-1], rt[r], x, D);
		}
		else
		{
			scanf("%d%d", &l, &r);
			e[++tim] = event{l, r, tim};
		}
	}
	REP(i, 1, Q) pushdown(1, 1, tim, q[i].tl, q[i].tr, i);
	sort(e + 1, e + 1 + tim);
	work(1, 1, tim);
	REP(i, 1, Q) printf("%d\n", ans[i]);
	return 0;
}
