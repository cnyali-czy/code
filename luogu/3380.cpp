#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;
const int maxn = 5e4 + 10, maxnode = 785000, inf = 2147483647;

template <typename T> T read()
{
	T ans(0), flag(1);
	char c(getchar());
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

struct balance
{
	vector <int> v;
	int siz;
	balance() {v.clear();siz = -1;}
	int Min() {return v[0];}
	int Max() {return v[siz];}
	void insert(int val)
	{
		siz++;
		v.insert(lower_bound(v.begin(), v.end(), val), val);
	}
	void output()
	{
		int siz = (int)v.size() - 1;
		REP(i, 0, siz) printf("%d%c", v[i], i == siz ? '\n' : ' ');
	}
	int get_rank(int val)
	{
		if (val < Min()) return 1;
		return lower_bound(v.begin(), v.end(), val) - v.begin() + 1;
	}
	void erase(int val)
	{
		siz--;
		v.erase(lower_bound(v.begin(), v.end(), val));
	}
	void update(int pre, int now)
	{
		erase(pre);
		insert(now);
	}
	int pre(int val)
	{
		if (Min() >= val) return -inf;
		return *(lower_bound(v.begin(), v.end(), val) - 1);
	}
	int nxt(int val)
	{
		if (Max() <= val) return inf;
		return *upper_bound(v.begin(), v.end(), val);
	}
	int small(int val) {return get_rank(val) - 1;}
	bool exsit(int val) {return lower_bound(v.begin(), v.end(), val) != v.end() && *lower_bound(v.begin(), v.end(), val) == val;}
	int cnt(int val)
	{
		if (!exsit(val)) return 0;
		return upper_bound(v.begin(), v.end(), val) - lower_bound(v.begin(), v.end(), val);
	}
};
int m, n, a[maxn];
balance t[maxnode];
#define mid (l + r >> 1)
#define lson ls[p], l, mid
#define rson rs[p], mid + 1, r
int root, ls[maxnode], rs[maxnode], cur;
void build(int &p, int l, int r)
{
	p = ++cur;
	REP(i, l, r) t[p].insert(a[i]);
}
int small(int &p, int l, int r, int L, int R, int val)
{
	if (!p) build(p, l, r);
	if (L <= l && r <= R) return t[p].small(val);
	else
	{
		if (L >  mid) return small(rson, L, R, val);
		if (R <= mid) return small(lson, L, R, val);
		return small(lson, L, R, val) + small(rson, L, R, val);
	}
}
int cnt(int &p, int l, int r, int L, int R, int val)
{
	if (!p) build(p, l, r);
	if (L <= l && r <= R) return t[p].cnt(val);
	else
	{
		if (L >  mid) return cnt(rson, L, R, val);
		if (R <= mid) return cnt(lson, L, R, val);
		return cnt(lson, L, R, val) + cnt(rson, L, R, val);
	}
}
int cnt(int L, int R, int val) {return cnt(root, 1, n, L, R, val);}
bool exsit(int &p, int l, int r, int L, int R, int val)
{
	if (!p) build(p, l, r);
	if (L <= l && r <= R) return t[p].exsit(val);
	else
	{
		if (L >  mid) return exsit(rson, L, R, val);
		if (R <= mid) return exsit(lson, L, R, val);
		return exsit(lson, L, R, val) | exsit(rson, L, R, val);
	}
}
bool exsit(int L, int R, int val) {return exsit(root, 1, n, L, R, val);}
int get_rank(int L, int R, int val) {return small(root, 1, n, L, R, val) + 1;}
void update(int &p, int l, int r, int pos, int val)
{
	if (!p) build(p, l, r);
	t[p].update(a[pos], val);
	if (l == r) return;
	if (pos <= mid) update(lson, pos, val);
	else update(rson, pos, val);
}
void update(int pos, int val)
{
	update(root, 1, n, pos, val);
	a[pos] = val;
}
int Min(int &p, int l, int r, int L, int R)
{
	if (!p) build(p, l, r);
	if (L <= l && r <= R) return t[p].Min();
	else
	{
		if (L >  mid) return Min(rson, L, R);
		if (R <= mid) return Min(lson, L, R);
		return min(Min(lson, L, R), Min(rson, L, R));
	}
}
int Max(int &p, int l, int r, int L, int R)
{
	if (!p) build(p, l, r);
	if (L <= l && r <= R) return t[p].Max();
	else
	{
		if (L >  mid) return Max(rson, L, R);
		if (R <= mid) return Max(lson, L, R);
		return max(Max(lson, L, R), Max(rson, L, R));
	}
}
int Min(int L, int R) {return Min(root, 1, n, L, R);}
int Max(int L, int R) {return Max(root, 1, n, L, R);}
int pre(int &p, int l, int r, int L, int R, int val)
{
	if (!p) build(p, l, r);
	if (L <= l && r <= R) return t[p].pre(val);
	else
	{
		if (L >  mid) return pre(rson, L, R, val);
		if (R <= mid) return pre(lson, L, R, val);
		return max(pre(lson, L, R, val), pre(rson, L, R, val));
	}
}
int nxt(int &p, int l, int r, int L, int R, int val)
{
	if (!p) build(p, l, r);
	if (L <= l && r <= R) return t[p].nxt(val);
	else
	{
		if (L >  mid) return nxt(rson, L, R, val);
		if (R <= mid) return nxt(lson, L, R, val);
		return min(nxt(lson, L, R, val), nxt(rson, L, R, val));
	}
}
int pre(int L, int R, int val) {return pre(root, 1, n, L, R, val);}
int nxt(int L, int R, int val) {return nxt(root, 1, n, L, R, val);}
int kth(int L, int R, int k)
{
	int l = 0, r = 1e8, ans;
	while (l <= r)
	{
		int x = get_rank(L, R, mid);
		if (exsit(L, R, mid))
		{
			int y = x + cnt(L, R, mid);
			if (x <= k && k <= y - 1) return mid;
			else if (x < k) l = mid + 1;
			else r = mid - 1;
//			else l = mid + 1;
		}
		else if (x >= k)
		{
			ans = mid;
			r = mid - 1;
		}
		else l = mid + 1;
	}
	return exsit(L, R, ans) ? ans : nxt(L, R, ans);
}

int main()
{
#ifdef CraZYali
	file("3380");
#endif
	cin >> n >> m;
	REP(i, 1, n) a[i] = read<int>();
	while (m--)
	{
		//		REP(i, 1, n) printf("%d%c", a[i], i == n ? '\n' : ' ');
		int opt = read<int>(), l, r, pos, k;
		switch (opt)
		{
			case 1:l = read<int>(), r = read<int>(), k = read<int>();printf("%d\n", get_rank(l, r, k));break;
			case 2:l = read<int>(), r = read<int>(), k = read<int>();printf("%d\n", kth(l, r, k));break;
			case 3:pos = read<int>(), k = read<int>();update(pos, k);break;
			case 4:l = read<int>(), r = read<int>(), k = read<int>();printf("%d\n", pre(l, r, k));break;
			case 5:l = read<int>(), r = read<int>(), k = read<int>();printf("%d\n", nxt(l, r, k));break;
		}
	}
	return 0;
}
