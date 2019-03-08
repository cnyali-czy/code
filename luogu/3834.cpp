#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>
#define int long long

using namespace std;
const int maxn = 2e5 + 10, maxm = 2e5 + 10;

template <typename T> T read()
{
	T ans = 0, p = 1;
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

int n, m, q, a[maxn], b[maxn], T[maxn];
/*
   struct Question
   {
   int l, r, k, pos;
   Question(){}
   Question(int _pos) : pos(_pos), l(read<int>()), r(read<int>()), k(read<int>()) {}
   }Q[maxm];
   bool cmp1(Question A, Question B) {return A.l < B.l;}
   bool cmp2(Question A, Question B) {return A.r < B.r;}

   int block_siz, block_cnt, Left[maxn], Right[maxn];
   void get_belong()
   {
   sort(Q + 1, Q + 1 + n, cmp1);
   block_siz = sqrt(n);
   int l = 1, r = 1;
   while (r < n)
   if (Q[r + 1].l - Q[l].l <= block_siz) ++r;
   else		
   {
   ++block_cnt;
   Left[block_cnt] = l;Right[block_cnt] = r;
   l = ++r;
   }
   if (l < n)
   {
   ++block_cnt;
   Left[block_cnt] = l;Right[block_cnt] = n;
   }
   }

   struct node
   {
   int l, r, s, order, val;
   node(){}
   node(int _val) : val(_val), l(0), r(0), s(1), order(rand()) {}
   };
   struct FHQ_TREAP
   {
   node t[maxn];
   int root, cur;
   void clear() {root = cur = 0;}
   int newnode(int val) {t[++cur] = node(val);return cur;}
   void maintain(int x) {t[x].s = t[t[x].l].s + t[t[x].r].s + 1;}
   void merge(int &x, int a, int b)
   {
   if (!(a * b)) x = a + b;
   else
   {
   if (t[a].order > t[b].order) merge(t[x = b].l, a, t[b].l);
   else merge(t[x = a].r, t[a].r, b);
   maintain(x);
   }
   }
   void split(int x, int &a, int &b, int val)
   {
   if (!x) a = b = 0;
   else
   {
   if (t[x].val > val) split(t[b = x].l, a, t[x].l, val);
   else split(t[a = x].r, t[x].r, b, val);
   maintain(x);
   }
   }
   void insert(int val)
   {
   int x(0), y(0), z(newnode(val));
   split(root, x, y, val);
   merge(x, x, z);
   merge(root, x, y);
   }
void del(int val)
{
	int x(0), y(0), z(0);
	split(root, x, y, val);
	split(x, x, z, val - 1);
	merge(z, t[z].l, t[z].r);
	merge(x, x, z);
	merge(root, x, y);
}
int kth(int k)
{
	int now = root;
	while (t[t[now].l].s + 1 != k)
		if (t[t[now].l].s >= k) now = t[now].l;
		else
		{
			k -= t[t[now].l].s + 1;
			now = t[now].r;
		}
	return t[now].val;
}
}T;

int ans[maxm];
void add(int val) {T.insert(val);}
void del(int val) {T.del(val);}
*/

int cnt, sum[maxn << 5], L[maxn << 5], R[maxn << 5];

#define mid (l + r >> 1)
#define lson l, mid
#define rson mid + 1, r

int build(int l, int r)
{
	int rt = ++cnt;
	if (l < r)
	{
		L[rt] = build(lson);
		R[rt] = build(rson);
	}
	return rt;
}
int update(int pre, int l, int r, int x)
{
	int rt = ++cnt;
	L[rt] = L[pre];R[rt] = R[pre];sum[rt] = sum[pre] + 1;
	if (l < r)
	{
		if (x <= mid) L[rt] = update(L[pre], lson, x);
		else R[rt] = update(R[pre], rson, x);
	}
	return rt;
}

int query(int u, int v, int l, int r, int k)
{
	if (l >= r) return l;
	int x = sum[L[v]] - sum[L[u]];
	if (x >= k) return query(L[u], L[v], lson, k);
	else return query(R[u], R[v], rson, k - x);
}

signed main()
{
#ifdef CraZYali
	freopen("3834.in", "r", stdin);
	freopen("3834.out", "w", stdout);
#endif
	srand((unsigned long long)new char);
	cin >> n >> q;
	REP(i, 1, n) a[i] = b[i] = read<int>();
	/*
	   REP(i, 1, m) Q[i] = Question(i);
	   get_belong();
	   REP(i, 1, block_cnt)
	   {
	   sort(Q + Left[i], Q + Right[i] + 1, cmp2);
	   T.clear();
	   int l = Q[Left[i]].l, r = Q[Left[i]].r;
	   REP(j, l, r) add(a[j]);
	   ans[Q[Left[i]].pos] = T.kth(Q[Left[i]].k);
	   REP(j, Left[i] + 1, Right[i])
	   {
	   while (l < Q[j].l) del(a[l++]);
	   while (l > Q[j].l) add(a[--l]);
	   while (r < Q[j].r) add(a[++r]);
	   ans[Q[j].pos] = T.kth(Q[j].k);
	   }
	   REP(i, l, r) del(a[i]);
	   }
	   REP(i, 1, m) printf("%d\n", ans[i]);
	   */
	sort(b + 1, b + 1 + n);
	DEBUG;
	m = unique(b + 1, b + 1 + n) - b - 1;
	DEBUG;
	T[0] = build(1, m);
	DEBUG;
	REP(i, 1, n) T[i] = update(T[i-1], 1, m, lower_bound(b + 1, b + 1 + m, a[i]) - b);
	DEBUG;
	while (q--)
	{
		int x(read<int>()), y(read<int>()), z(read<int>());
		printf("%d\n", b[query(T[x-1], T[y], 1, m, z)]);
	}
	return 0;
}
