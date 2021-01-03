/*
	Problem:	C.cpp
	Time:		2020-12-27 09:36
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cassert>
#include <set>
#include <queue>
#include <iostream>
#include <cstdio>
#define int long long

using namespace std;
const int maxn = 1e5 + 10;

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

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, m, k;
int a[maxn];

int bg[maxn], ne[maxn << 1], to[maxn << 1], w[maxn << 1], e;
inline void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
}
void Add(int x, int y, int z)
{
	add(x, y, -z);
}
queue <int> q;
bool vis[maxn];
void link(int x, int y)
{
	Add(x, y, k + a[x] - a[y]);
}

namespace SMT
{
	int s[maxn << 2], t[maxn << 2];
#define ls p << 1
#define rs p << 1 | 1
#define lson ls, l, mid
#define rson rs, mid + 1, r
#define mid (l + r >> 1)
	void maintain(int p, int l, int r, int val)
	{
		t[p] += val;
		s[p] += (r - l + 1) * val;
	}
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
			if (t[p]) pushdown(p, l, r);
			if (L <= mid) update(lson, L, R, val);
			if (R >  mid) update(rson, L, R, val);
			s[p] = s[ls] + s[rs];
		}
	}
	int query(int p, int l, int r, int L, int R)
	{
		if (L <= l && r <= R) return s[p];
		else
		{
			if (t[p]) pushdown(p, l, r);
			int res = 0;
			if (L <= mid) res += query(lson, L, R);
			if (R >  mid) res += query(rson, L, R);
			return res;
		}
	}
	void build(int p, int l, int r)
	{
		if (l == r) s[p] = a[l];
		else
		{
			build(lson);
			build(rson);
			s[p] = s[ls] + s[rs];
		}
	}
	void dfs(int p, int l, int r, int L, int R)
	{
		if (l == r) a[l] = s[p];
		else
		{
			if (t[p]) pushdown(p, l, r);
			if (L <= mid) dfs(lson, L, R);
			if (R >  mid) dfs(rson, L, R);
		}
	}
}
int b[maxn];

namespace bf
{
	void fix(int l, int r)
	{
		if (l == r) return;
		SMT :: dfs(1, 1, n, l, r);
		REP(i, l, r) bg[i] = 0;e = 0;
		REP(i, l, r - 1)
		{
			Add(i, i + 1, k + (a[i] - a[i + 1]));
			Add(i + 1, i, k - (a[i] - a[i + 1]));
		}
		REP(i, l, r) b[i] = 0;
		REP(i, l, r) vis[i] = 1, q.push(i);
		while (q.size())
		{
			int x = q.front();q.pop();
			vis[x] = 0;
			for (int i = bg[x]; i; i = ne[i])
				if (b[to[i]] < b[x] + w[i])
				{
					b[to[i]] = b[x] + w[i];
					if (!vis[to[i]]) vis[to[i]] = 1, q.push(to[i]);
				}
		}
		REP(i, l, r) a[i] -= b[i];
		REP(i, l, r) SMT :: update(1, 1, n, i, i, -b[i]);
	}
	void work()
	{
		REP(Case, 1, m)
		{
			int opt = read<int>(), l = read<int>(), r = read<int>();
			if (opt == 1) printf("%lld\n", SMT :: query(1, 1, n, l, r));
			else if (opt == 2) SMT :: update(1, 1, n, l, r, read<int>());
			else
			{
				fix(l, r);
			}
		}
	}
}

/*
namespace wa
{
	struct node
	{
		int l, r;
		node() {}
		node(int l = 0, int r = 0) : l(l), r(r) {}
		inline bool operator < (const node &B) const {return l < B.l;}
	};
	set <node> S;
#define IT set <node> :: iterator
	IT split(int pos)
	{
		if (pos > n) return S.end();
		auto it = S.lower_bound(node(pos));
		if (it -> l == pos) return it;
		--it;
		int L = it -> l, R = it -> r;
		S.erase(it);
		S.emplace(L, pos - 1);
		return S.emplace(pos, R).first;
	}
	void modify_add(int l, int r, int val)
	{
		split(r + 1);split(l);
		SMT :: update(1, 1, n, l, r, val);
	}
	int A(int x) {return SMT :: query(1, 1, n, x);}
	void fix(int l, int r)
	{
		auto itr = split(r + 1), itl = split(l);
		static int L[maxn], R[maxn], pl[maxn], pr[maxn];int N = 0;
		REP(i, l, r)
//		for (auto it = itl; it != itr; it++)
		{
			++N;
			auto itt = (node(i,i));
			auto it = &itt;
			pl[N] = it -> l;pr[N] = it -> r;
			L[N] = A(l);R[N] = A(r);
		}
		if (N == 1) return;
		REP(i, 1, N) bg[i] = 0;e = 0;
		REP(i, 1, N - 1)
		{
			Add(i, i + 1, k + (R[i] - L[i + 1]));
			Add(i + 1, i, k - (R[i] - L[i + 1]));
		}
		REP(i, 1, N) b[i] = 0;
		REP(i, 1, N) vis[i] = 1, q.push(i);
		while (q.size())
		{
			int x = q.front();q.pop();
			vis[x] = 0;
			for (int i = bg[x]; i; i = ne[i])
				if (b[to[i]] < b[x] + w[i])
				{
					b[to[i]] = b[x] + w[i];
					if (!vis[to[i]]) vis[to[i]] = 1, q.push(to[i]);
				}
		}
		static pair <int, int> stk[maxn];int top = 0 ;
		int lst = b[1], cnt = 0;
		REP(i, 1, N - 1)
		{
			int lst = SMT :: query(1, 1, n, pl[i]), most = pl[i];
			while (
			while (most < pr[i] && abs(SMT :: query(1, 1, n, most) - SMT :: query(1, 1, n, most + 1)) == k) most++;
			SMT :: update(1, 1, n, pl[i], most, -b[i]);
			most = pr[i];
			while (most > pl[i] && abs(SMT :: query(1, 1, n, most) - SMT :: query(1, 1, n, most - 1)) == k) most--;
			SMT :: update(1, 1, n, most, pr[i], -b[i]);
		}
		S.erase(itl, itr);
		S.emplace(l, r);
	}
	void work()
	{
		REP(i, 1, n) S.emplace(i, i);
		while (m--)
		{
			int opt = read<int>(), l = read<int>(), r = read<int>();
			if (opt == 1)
			{
				printf("%lld\n", SMT :: query(1, 1, n, l, r));
			}
			else if (opt == 2)
			{
				modify_add(l, r, read<int>());
			}
			else
			{
				fix(l, r);
			}
		}
	}
}
*/
signed main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();m = read<int>();k = read<int>();
	REP(i, 1, n) a[i] = read<int>();
	SMT :: build(1, 1, n);
	//wa :: work();
	bf :: work();
	return 0;
}
