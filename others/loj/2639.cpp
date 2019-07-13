#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %lld\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>
#define int long long

using namespace std;
const int maxn = 50000 + 10, MOD = 1e9 + 7, maxnode = 780500;

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

int Mod(long long val) {return val >= MOD ? val % MOD : val;}
#define mod(x) Mod(0ll + (x))

int n, m, k;
int pos[maxn], v[maxn];

struct node
{
	int l, r, s, order, p, val, sum;
	node() : l(0), r(0), s(0), val(0), sum(0) {};
	node(int _p, int _val) : l(0), r(0), s(1), order(rand()), p(_p), val(_val), sum(_val) {}
}t[maxnode * 4];
int now;
int newnode(int p, int val) {t[++now] = node(p, val);return now;}

struct Tree
{
	int root;
	Tree() : root(0) {}
	void pushup(int x)
	{
		t[x].s = t[t[x].l].s + t[t[x].r].s + 1;
		t[x].sum = t[t[x].l].sum + t[t[x].r].sum + t[x].val;
		if (t[x].sum >= MOD) t[x].sum %= MOD;
	}
	void split(int x, int &a, int &b, int pos)
	{
		if (!x) a = b = 0;
		else
		{
			if (t[x].p > pos) split(t[b = x].l, a, t[x].l, pos);
			else split(t[a = x].r, t[x].r, b, pos);
			pushup(x);
		}
	}
	void merge(int &x, int a, int b)
	{
		if (!a || !b) x = a + b;
		else
		{
			if (t[a].order > t[b].order) merge(t[x = b].l, a, t[b].l);
			else merge(t[x = a].r, t[a].r, b);
			pushup(x);
		}
	}
	void insert(int pos, int val)
	{
		int x(0), y(0);
		split(root, x, y, pos);
		merge(x, x, newnode(pos, val));
		merge(root, x, y);
	}
	int smaller_cnt(int pos)
	{
		int x(0), y(0);
		split(root, x, y, pos-1);
		int ans = t[x].s;
		merge(root, x, y);
		return ans;
	}
	int smaller_sum(int pos)
	{
		int x(0), y(0);
		split(root, x, y, pos-1);
		int ans = t[x].sum;
		merge(root, x, y);
		return ans;
	}
	int bigger_cnt(int pos)
	{
		int x(0), y(0);
		split(root, x, y, pos);
		int ans = t[y].s;
		merge(root, x, y);
		return ans;
	}
	int bigger_sum(int pos)
	{
		int x(0), y(0);
		split(root, x, y, pos);
		int ans = t[y].sum;
		merge(root, x, y);
		return ans;
	}
	void erase(int pos)
	{
		int x(0), y(0), z(0);
		split(root, x, y, pos);
		split(x, x, z, pos - 1);
		merge(z, t[z].l, t[z].r);
		merge(x, x, z);
		merge(root, x, y);
	}
	void update(int pre, int nxt)
	{
		erase(pos[pre]);
		insert(pos[nxt], v[nxt]);
	}
}T[maxnode];
int root, ls[maxnode], rs[maxnode], cur;

#define mid (l + r >> 1)
#define lson ls[p], l, mid
#define rson rs[p], mid + 1, r
void build(int &p, int l, int r)
{
	p = ++cur;
	REP(i, l, r) T[p].insert(pos[i], v[i]);
}
int smaller_cnt(int &p, int l, int r, int L, int R, int pos)
{
	if (l > r || L > R || L > r || R < l) return 0;
	if (!p) build(p, l, r);
	if (L <= l && r <= R) return T[p].smaller_cnt(pos);
	if (L >  mid) return smaller_cnt(rson, L, R, pos);
	if (R <= mid) return smaller_cnt(lson, L, R, pos);
	return smaller_cnt(lson, L, R, pos) + smaller_cnt(rson, L, R, pos);
}
int smaller_cnt(int L, int R, int pos) {return smaller_cnt(root, 1, n, L, R, pos);}
int smaller_sum(int &p, int l, int r, int L, int R, int pos)
{
	if (l > r || L > R || L > r || R < l) return 0;
	if (!p) build(p, l, r);
	if (L <= l && r <= R) return T[p].smaller_sum(pos);
	if (L >  mid) return smaller_sum(rson, L, R, pos);
	if (R <= mid) return smaller_sum(lson, L, R, pos);
	return (smaller_sum(lson, L, R, pos) + smaller_sum(rson, L, R, pos)) % MOD;
}
int smaller_sum(int L, int R, int pos) {return smaller_sum(root, 1, n, L, R, pos);}
int bigger_cnt(int &p, int l, int r, int L, int R, int pos)
{
	if (l > r || L > R || L > r || R < l) return 0;
	if (!p) build(p, l, r);
	if (L <= l && r <= R) return T[p].bigger_cnt(pos);
	if (L >  mid) return bigger_cnt(rson, L, R, pos);
	if (R <= mid) return bigger_cnt(lson, L, R, pos);
	return bigger_cnt(lson, L, R, pos) + bigger_cnt(rson, L, R, pos);
}
int bigger_cnt(int L, int R, int pos) {return bigger_cnt(root, 1, n, L, R, pos);}
int bigger_sum(int &p, int l, int r, int L, int R, int pos)
{
	if (l > r || L > R || L > r || R < l) return 0;
	//cerr << l << ' ' << r << ' ' << L << ' ' << R << endl;
	//system("sleep 0.5");
	if (!p) build(p, l, r);
	if (L <= l && r <= R) return T[p].bigger_sum(pos);
	if (L >  mid) return bigger_sum(rson, L, R, pos);
	if (R <= mid) return bigger_sum(lson, L, R, pos);
	return (bigger_sum(lson, L, R, pos) + bigger_sum(rson, L, R, pos)) % MOD;
}
int bigger_sum(int L, int R, int pos) {return bigger_sum(root, 1, n, L, R, pos);}
void update(int &p, int l, int r, int pre, int nxt)
{
	if (!p) build(p, l, r);
	T[p].update(pre, nxt);
	if (l == r) return;
	if (pre <= mid) update(lson, pre, nxt);
	else update(rson, pre, nxt);
}
int ans;
int calc(int x, int L, int R) {return smaller_sum(L, R, pos[x]) + smaller_cnt(L, R, pos[x]) * v[x];}
int ccalc(int x, int L, int R) {return bigger_sum(L, R, pos[x]) + bigger_cnt(L, R, pos[x]) * v[x];}
void Swap(int x, int y)
{
	if (x > y) swap(x, y);
	ans -= calc(x, x+1, y);
	ans -= ccalc(y, x+1, y - 1);
	//ans -= calc(y, x, y);
//	if (pos[x] > pos[y]) ans += v[x] + v[y];
	update(root, 1, n, x, y);
	update(root, 1, n, y, x);
	swap(pos[x], pos[y]);
	swap(v[x], v[y]);
	ans += calc(x,x+1,y);
	ans += ccalc(y, x+1, y - 1);
	//ans += calc(x, x, y);ans += calc(y, x, y);
//	if (pos[x] > pos[y]) ans -= v[x] + v[y];
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("2639.in", "r", stdin);
	freopen("2639.out", "w", stdout);
	freopen("2639.err", "w", stderr);
#endif
	srand(time(0));
	cin >> n >> m;
	REP(i, 1, n) pos[i] = read<int>(), v[i] = read<int>();
	build(root, 1, n);
	ans = 0;
	REP(i, 1, n) ans += calc(i, i + 1, n), ans %= MOD;
#ifdef CraZYali
	/*
	REP(i, 1, n)
		REP(j, i, n)
		{
			REP(k, i, j) fprintf(stderr,"%lld %lld\n", pos[k],v[k]);
			REP(k, 1, 5) fprintf(stderr,"%lld %lld %lld %lld %lld\n", k, smaller_cnt(i, j, k), smaller_sum(i, j, k), bigger_cnt(i, j, k), bigger_sum(i, j, k));
			fputs("-------\n",stderr);
		}*/
#endif
	while (m--)
	{
		Swap(read<int>(), read<int>());
		/*
#ifdef CraZYali
		REP(i, 1, n)
			REP(j, i, n)
			{
				REP(k, i, j) fprintf(stderr,"%lld %lld\n", pos[k],v[k]);
				REP(k, 1, 5) fprintf(stderr,"%lld %lld %lld %lld %lld\n", k, smaller_cnt(i, j, k), smaller_sum(i, j, k), bigger_cnt(i, j, k), bigger_sum(i, j, k));
				fputs("-------\n",stderr);
			}
		cerr<<"===============\n";
		cerr <<"Test Start\n";
		cerr << pos[3] << ' ' << v[3] << endl;
		REP(i, 1, n) fprintf(stderr, "%lld%c", calc(i), i == n ? '\n' : ' ');
		cerr << "Test End\n";
#endif*/
		printf("%lld\n", ((ans % MOD) + MOD) % MOD);
	}
	return 0;
}
