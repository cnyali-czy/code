#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <set>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 2e5 + 10;

	template <typename T>
inline T read()
{
	register T ans(0), flag(1);
	register char c(getchar());
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
/*
   int n, m, p, t[maxn], a[maxn], ans; 

   inline void chkmax(int &x, int y) {if (x < y) x = y;}
   inline void chkmin(int &x, int y) {if (x > y) x = y;}

   int Max[maxn];

   set <pair <pair <int, int>, int> > s;
   multiset <int> anss;
   inline void init()
   {
   Max[n + n] = a[n + n];
   DREP(i, n + n - 1, 1)
   {
   Max[i] = Max[i+1];
   chkmax(Max[i], a[i]);
   }
   REP(i, 1, n + n)
   {
   int j(i);
   while (j < n + n && Max[i] == Max[j+1]) j++;
   s.emplace(make_pair(i, j), Max[i]);
   }
   ans = 1e9;
   for (auto i : s) anss.emplace(i.second + i.first.first + n - 1);
   ans = *anss.begin();
   }
   */
namespace run
{
	using namespace std;
	const int maxn = 1e5 + 10, inf = 1e9;
	int n, m, p, ans, a[maxn];

	int tr[maxn << 2], Max[maxn << 2];
#define ls p << 1
#define rs p << 1 | 1
#define mid (l + r >> 1)
#define lson ls, l, mid
#define rson rs, mid + 1, r
	int query(int p, int l, int r, int x)
	{
		if (l == r) return Max[p] > x ? x + l : inf;
		if (Max[rs] > x)	return min(tr[p], query(rson, x));
		else				return query(lson, x);
	}
	inline void pushup(int p, int l, int r)
	{
		Max[p] = max(Max[ls], Max[rs]);
		tr[p] = query(lson, Max[rs]);
	}
	void build(int p, int l, int r)
	{
		if (l == r) return void(Max[p] = a[l] - l);
		build(lson);
		build(rson);
		pushup(p, l, r);
	}
	void modify(int p, int l, int r, int x, int y)
	{
		if (l == r) return void(Max[p] = y - l);
		if (x <= mid)	modify(lson, x, y);
		else			modify(rson, x, y);
		pushup(p, l, r);
	}
	int main()
	{
		cin >> n >> m >> p;
		REP(i, 1, n) a[i] = read<int>();
		build(1, 1, n);
		int x, y;
		printf("%d\n", ans = query(1, 1, n, Max[1] - n) + n);
		while (m--)
		{
			int x(read<int>() ^ (ans * p));
			int y(read<int>() ^ (ans * p));
			modify(1, 1, n, x, y);
			printf("%d\n", ans = query(1, 1, n, Max[1] - n) + n);
		}
		return 0;
	}	
}

int main()
{
#ifdef CraZYali
	freopen("4425.in", "r", stdin);
	freopen("4425.out", "w", stdout);
#endif
	return run::main();
	/*
	   cin >> n >> m >> p;
	   REP(i, 1, n) t[i] = t[i + n] = read<int>();
	   REP(i, 1, n + n) a[i] = t[i] - i;
	   init();
	   printf("%d\n", ans = solve());
	   while (m--)
	   {
	   int x(read<int>() ^ (ans * p)), y(read<int>() ^ (ans * p));
	   modify(x + n, y - (x + n));
	   modify(x, y - x);
	   printf("%d\n", ans);
	   }
	   return 0;
	   */
}
