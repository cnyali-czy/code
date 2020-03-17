#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passng [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cstdio>
#include <iostream>

using namespace std;
const int inf = 1e9, N = 1e5 + 5;
	
	template <typename T>
inline T read()
{
	T ans = 0, flag = 1;
	char c = getchar();
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
struct seg_tree
{
	int a[N << 2], s[N << 2];
#define lson ls, l, mid
#define rson rs, mid + 1, r
#define mid (l + r >> 1)
#define ls p << 1
#define rs p << 1 | 1
	void add(int p, int l, int r, int pos, int val)
	{
		if (l == r)
		{
			a[p] = val;
			return;
		}
		if (pos <= mid) add(lson, pos, val);
		else			add(rson, pos, val);
		a[p] = max(a[ls], a[rs]);
	}
	void Add(int p, int l, int r, int pos, int val)
	{
		if (l == r)
		{
			s[p] = val;
			return;
		}
		if (pos <= mid) Add(lson, pos, val);
		else			Add(rson, pos, val);
		s[p] = s[ls] + s[rs];
	}
	int query(int p, int l, int r, int L, int R)
	{
		if (L <= l && r <= R) return s[p];
		else
		{
			if (R <= mid) return query(lson, L, R);
			if (L >  mid) return query(rson, L, R);
			return query(lson, L, R) + query(rson, L, R);
		}
	}
	int get(int p, int l, int r, int val)
	{
		if (l == r) return l;
		if (val <= s[ls])	return get(lson, val);
		else				return get(rson, val - s[ls]);
	}
	int get(int p, int l, int r, int z, int pos, int opt)
	{
		if (a[p] <= z) return opt ? r - max(l, pos) + 1 : min(r, pos) - l + 1;
		else
		{
			if (l == r) return 0;
			if (opt)
			{
				if (pos > mid) return get(rson, z, pos, opt);
				int k = get(lson, z, pos, opt);
				if (k == mid - max(l, pos) + 1) return k + get(rson, z, pos, opt);
				else return k;
			}
			else
			{
				if (pos <= mid) return get(lson, z, pos, opt);
				int k = get(rson, z, pos, opt);
				if (k == min(r, pos) - mid) return k + get(lson, z, pos, opt);
				else return k;
			}
		}
	}
}T[2];
int n, m, q, p, t, mi, lastans;
int a[N], vis[N];
bool check(int x)
{
	int l = T[p].get(1, 1, n, x, mi, 0), r = T[p].get(1, 1, n, x, mi, 1);
	return T[p].query(1, 1, n, mi - l + 1, mi + r - 1) <= (m >> 1);
}
int solve()
{
	p = m & 1;
	mi = T[p].get(1, 1, n, (m >> 1) + 1);
	int l = p ? inf - a[mi] : a[mi], r = inf;
	while (l < r)
		if (check(mid)) l = mid + 1;
		else r = mid;
	return p ? inf - l : l;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read<int>();m = read<int>();q = read<int>();t = read<int>();
	REP(i, 1, n)
	{
		a[i] = read<int>();
		T[0].add(1, 1, n, i, a[i]);
		T[1].add(1, 1, n, i, inf - a[i]);
	}
	REP(i, 1, m) vis[read<int>()] = 1;
	REP(i, 1, n) if (vis[i])
	{
		T[0].Add(1, 1, n, i, 1);
		T[1].Add(1, 1, n, i, 1);
	}
	cout << (lastans = solve()) << '\n';
	while (q --> 0)
	{
		int opt(read<int>()), x(read<int>());
		if (t) x = (x - 1 + lastans) % n + 1;
		if (opt == 1)
			if (vis[x])
			{
				T[1].Add(1, 1, n, x, 0);
				T[0].Add(1, 1, n, x, 0);
				vis[x] = 0;
				m--;
			}
			else
			{
				T[1].Add(1, 1, n, x, 1);
				T[0].Add(1, 1, n, x, 1);
				m++;
				vis[x] = 1;
			}
		else
		{
			T[0].add(1, 1, n, x, a[x] = read<int>());
			T[1].add(1, 1, n, x, inf - a[x]);
		}
		cout << (lastans = solve()) << '\n';
	}
	return 0;
}
