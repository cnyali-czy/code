#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>
#define int long long

using namespace std;
const int MOD = 1000000, maxn = 80000 + 10, inf = 1e10;

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

int n, ans;

struct fhq
{
	struct node
	{
		int l, r, s, val, order;
		node() : l(0), r(0), s(0) {}
		node(int _val) : val(_val), l(0), r(0), s(1), order(rand()){};
	}t[maxn];
	int cnt, root;
	int newnode(int val)
	{
		t[++cnt] = node(val);
		return cnt;
	}
	void maintain(int x) {t[x].s = t[t[x].l].s + t[t[x].r].s + 1;}
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
		split(root, x, y, val-1);
		split(y, y, z, val);
		merge(y, t[y].l, t[y].r);
		merge(y, y, z);
		merge(root, x, y);
	}
	int kth(int k, int now)
	{
		while (t[t[now].l].s + 1 != k)
			if (k <= t[t[now].l].s) now = t[now].l;
			else
			{
				k -= t[t[now].l].s + 1;
				now = t[now].r;
			}
		return t[now].val;
	}
	int pre(int val)
	{
		int x(0), y(0);
		split(root, x, y, val);
		int ans = t[x].s ? kth(t[x].s, x) : inf;
		merge(root, x, y);
		return ans;
	}
	int nxt(int val)
	{
		int x(0), y(0);
		split(root, x, y, val);
		int ans = t[y].s ? kth(1, y) : inf;
		merge(root, x, y);
		return ans;
	}
}pet, men;

signed main()
{
#ifdef CraZYali
	freopen("D.in", "r", stdin);
	freopen("D.out", "w", stdout);
#endif
	srand((unsigned long long)new char);
	cin >> n;
	while (n--)
	{
		int type(read<int>()), x(read<int>());
		if (type == 0)
			if (men.t[men.root].s)
			{
				int A = men.nxt(x);
				int B = men.pre(x);
				if (B == inf || (A != inf && A - x < x - B))
				{
					ans += A - x;
					men.del(A);
				}
				else
				{
					ans += x - B;
					men.del(B);
				}
			}
			else pet.insert(x);
		else
			if (pet.t[pet.root].s)
			{
				int A = pet.nxt(x);
				int B = pet.pre(x);
				if (B == inf || (A != inf && A - x < x - B))
				{
					ans += A - x;
					pet.del(A);
				}
				else
				{
					ans += x - B;
					pet.del(B);
				}
			}
			else men.insert(x);
		if (ans >= MOD) ans %= MOD;
	}
	cout << ans << endl;
	return 0;
}
