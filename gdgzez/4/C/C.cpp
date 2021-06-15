/*
	Problem:	C.cpp
	Time:		2021-06-15 16:58
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <set>
#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 5e4 + 10, inf = 2e9;

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
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, q;
char s[maxn];
int a[maxn], L[maxn], R[maxn], F[maxn], M[maxn], stk[maxn], top;

namespace ST
{
	int st[17][maxn], lg[maxn];
	void init()
	{
		REP(i, 1, n) st[0][i] = a[i];
		REP(j, 1, 16) REP(i, 1, n - (1 << j) + 1)
			st[j][i] = max(st[j - 1][i], st[j - 1][i + (1 << j - 1)]);
		REP(i, 2, n) lg[i] = lg[i >> 1] + 1;
	}
	inline int query(int l, int r)
	{
		int k = lg[r - l + 1];
		return max(st[k][l], st[k][r - (1 << k) + 1]);
	}
}

struct func
{
	int k, b;
	func() {k = b = 0;}
	func(int k, int b) : k(k), b(b) {}
	inline int operator [] (int x) {return k * x + b;}
};
namespace LCT
{
	const int maxN = 3e7;
	struct node
	{
		int ls, rs;
		func f;
		node() {ls = rs = 0;}
	}t[maxN];
	int cur;
#define lson t[p].ls, l, mid
#define rson t[p].rs, mid + 1, r
#define mid (l + r >> 1)
	void ins(int pre, int &p, int l, int r, int L, int R, func f)
	{
		t[p = ++cur] = t[pre];
		if (L <= l && r <= R)
		{
			if (!pre) {t[p].f = f;return;}
			int New = f[mid], Old = t[p].f[mid];
			if (New > Old)
			{
				swap(New, Old);
				swap(f, t[p].f);
			}
			if (l == r) return;
			if (f.k > t[p].f.k && f[r] > t[p].f[r]) ins(t[pre].rs, rson, L, R, f);
			if (f.k < t[p].f.k && f[l] > t[p].f[l]) ins(t[pre].ls, lson, L, R, f);
		}
		else
		{
			if (L <= mid) ins(t[pre].ls, lson, L, R, f);
			if (R >  mid) ins(t[pre].rs, rson, L, R, f);
		}
	}
	int query(int p, int l, int r, int pos)
	{
		if (!p) return 0;
		return max(t[p].f[pos], l == r ? 0 : pos <= mid ? query(lson, pos) : query(rson, pos));
	}
}

#define fi first
#define se second
int rt[maxn];

namespace SAM
{
	const int maxn = ::maxn << 1;
	int ch[maxn][26], len[maxn], fail[maxn], lst = 1, cur = 1;
	
	//vector <int> vec[maxn];
	set <int> pos[maxn];

	void extend(int c)
	{
		int u = ++cur, v = lst;lst = u;
		len[u] = len[v] + 1;
		for (; v && !ch[v][c]; v = fail[v]) ch[v][c] = u;
		if (!v) fail[u] = 1;
		else if (len[ch[v][c]] == len[v] + 1) fail[u] = ch[v][c];
		else
		{
			int New(++cur), Old(ch[v][c]);
			copy(ch[Old], ch[Old] + 26, ch[New]);
			len[New] = len[v] + 1;
			fail[New] = fail[Old];
			fail[Old] = fail[u] = New;
			for (; v && ch[v][c] == Old; v = fail[v]) ch[v][c] = New;
		}
	}
	vector <pair <func, pair <int, int> > > toins[maxn];
	inline void orz(int s, int t, int l)
	{
		toins[t].emplace_back(func(-1, s + 1), make_pair(max(1, s - l + 1), s));
		if (s - l >= 1) toins[t].emplace_back(func(0, l), make_pair(1, s - l));
	}

	int bg[maxn], ne[maxn], to[maxn], e;
	inline void add(int x, int y)
	{
		e++;
		to[e] = y;
		ne[e] = bg[x];
		bg[x] = e;
	}
	inline void merge(int x, int y)
	{
		if (pos[x].size() < pos[y].size()) swap(pos[x], pos[y]);
		for (auto i : pos[y])
		{
			auto it = pos[x].emplace(i).first;
			if (it != pos[x].begin())
			{
				auto pre = it;pre--;
				orz(*pre, i, len[x]);
			}
			if (it != --pos[x].end())
			{
				auto nxt = it;nxt++;
				orz(i, *nxt, len[x]);
			}
		}
	}
	void dfs(int x)
	{
		for (int i = bg[x]; i; i = ne[i])
		{
			dfs(to[i]);
			merge(x, to[i]);
		}
	}

	void init()
	{
		REP(i, 1, n) extend(s[i] - 'a');
		REP(i, 2, cur) add(fail[i], i);
		int p = 1;
		REP(i, 1, n)
		{
			p = ch[p][s[i] - 'a'];
			pos[p].emplace(i);
//			for (int x = p; x; x = fail[x]) vec[x].emplace_back(i);
		}
		dfs(1);
		/*
		REP(i, 2, cur)
			REP(j, 1, (int)vec[i].size() - 1)
			{
				int s = vec[i][j - 1], t = vec[i][j];
				orz(s, t, len[i]);
			}
			*/
		REP(i, 1, n)
		{
			rt[i] = rt[i - 1];
			for (auto j : toins[i])
				LCT :: ins(rt[i], rt[i], 1, n, j.se.fi, j.se.se, j.fi);
		}
	}
}
inline int query(int l, int r)
{
	return LCT :: query(rt[r], 1, n, l);
}

inline void Tryle(int L, int R, int x, int &ans)
{
//	REP(i, l, r) if (query(l, i) >= x) {ans = min(ans, ST :: query(l, i));break;}
	int l = L, r = R, res = R;
	while (l <= r)
	{
		if (query(L, mid) >= x)
		{
			res = mid;
			r = mid - 1;
		}
		else l = mid + 1;
	}
	ans = min(ans, ST :: query(L, res));
}
inline void Tryri(int L, int R, int x, int &ans)
{
//	DEP(i, r, l) if (query(i, r) >= x) {ans = min(ans, ST :: query(i, r));break;}
	int l = L, r = R, res = L;
	while (l <= r)
	{
		if (query(mid, R) >= x)
		{
			res = mid;
			l = mid + 1;
		}
		else r = mid - 1;
	}
	ans = min(ans, ST :: query(res, R));
}

int ql[maxn], qr[maxn], qx[maxn], Ans[maxn];
vector <int> toins[maxn];

namespace SMT
{
	const int maxN = 3e7;
	struct node
	{
		int ls, rs, mi;
		node() {ls = rs;mi = inf;}
	}t[maxN];
	int cur;
	void ins(int &p, int l, int r, int pos, int val)
	{
		if (!p) p = ++cur;
		t[p].mi = min(t[p].mi, val);
		if (l == r) return;
		if (pos <= mid) ins(lson, pos, val);
		else ins(rson, pos, val);
	}
	int query(int p, int l, int r, int L, int R)
	{
		if (!p) return inf;
		if (L <= l && r <= R) return t[p].mi;
		else
		{
			if (R <= mid) return query(lson, L, R);
			if (L >  mid) return query(rson, L, R);
			return min(query(lson, L, R), query(rson, L, R));
		}
	}
}
int srt[maxn];

int main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();q = read<int>();
	scanf("%s", s + 1);
	SAM :: init();

	REP(i, 1, n) a[i] = read<int>();
	ST :: init();

	REP(i, 1, n)
	{
		while (top && a[stk[top]] <= a[i]) top--;
		L[i] = stk[top] + 1;
		stk[++top] = i;
	}
	stk[top = 0] = n + 1;
	DEP(i, n, 1)
	{
		while (top && a[stk[top]] <= a[i]) top--;
		R[i] = stk[top] - 1;
		stk[++top] = i;
	}
	/*
	REP(i, 1, n) REP(j, i, n)
	{
		REP(k, i, j) putchar(s[k]);
		printf(" : %d\n", query(i, j));
	}
	*/
	REP(i, 1, n)
	{
		F[i] = query(L[i], R[i]);
		M[i] = ST :: query(L[i], R[i]);
		toins[R[i]].emplace_back(i);
	}
	REP(i, 1, q) ql[i] = read<int>(), qr[i] = read<int>(), qx[i] = read<int>();
	static int id[maxn];
	REP(i, 1, q) id[i] = i;sort(id + 1, id + 1 + q, [&](int i, int j) {return qr[i] < qr[j];});
	int j = 0;

	REP(I, 1, q)
	{
		int i = id[I];

		int l = ql[i], r = qr[i], x = qx[i];
		if (query(l, r) < x)
		{
			Ans[i] = -1;
			continue;
		}
		while (j < r)
		{
			j++;
			for (auto c : toins[j])
			{
				for (int k = L[c]; k > 0; k &= (k - 1)) 
					SMT :: ins(srt[k], 0, n, F[c], M[c]);
			}
		}

		int ans = inf;
		for (int k = l; k <= n; k += k & -k)
			ans = min(ans, SMT :: query(srt[k], 0, n, x, n));
//		REP(i, 1, n) if (l <= L[i] && R[i] <= r && F[i] >= x) ans = min(ans, M[i]);

		Tryle(l, r, x, ans);
		Tryri(l, r, x, ans);

		Ans[i] = (ans == inf ? -1 : ans);
	}
	REP(i, 1, q) printf("%d\n", Ans[i]);
	return 0;
}
