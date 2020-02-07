/*
 * File Name:	B.cpp
 * Author	:	CraZYali
 * Time		:	2020.02.06 17:16
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdio>
#define y1 hhakioi
using namespace std;
const int maxn = 1e5 + 10, maxN = 2e7, MOD = 998244353;
//const long long llim = MOD * 1ll;
template <typename T> inline T read()
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

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout);
#define mid (l + r >> 1)
#define lson ls[p], l, mid
#define rson rs[p], mid + 1, r
int ls[maxN], rs[maxN], cur, rt[maxN], top;
long long tag[maxN], s[maxN];

int n, x1[maxn], y1[maxn], x2[maxn], y2[maxn], b[maxn << 1], m;
long long dp[maxn];

inline int newnode()
{
	++cur;
	s[cur] = tag[cur] = rt[cur] = 0;
	return cur;
}
void maintain(int &p, int l, int r, int val)
{
	if (!p) p = newnode();
	s[p] += 1ll * (r - l + 1) * val % MOD;
	tag[p] += val;
	if (tag[p] >= MOD) tag[p] -= MOD;
	if (s[p] >= MOD) s[p] -= MOD;
}
void pushdown(int p, int l, int r)
{
	maintain(lson, tag[p]);
	maintain(rson, tag[p]);
	tag[p] = 0;
}
void insert(int &p, int l, int r, const int &L, const int &R, const int &val)
{
	if (!p)
	{
		p = newnode();
		tag[p] = s[p] = 0;
	}
//	printf("In insert %d %d %d %d %d %d\n", p, l, r, L, R, val);
	if (L <= l && r <= R) maintain(p, l, r, val);
	else
	{
		if (tag[p]) pushdown(p, l, r);
		if (L <= mid) insert(lson, L, R, val);
		if (R >  mid) insert(rson, L, R, val);
		s[p] = s[ls[p]] + s[rs[p]];
	}
}

vector <int> V[maxN];
void Maintain(int &p, int id)
{
	if (!p) p = newnode();
	insert(rt[p], 1, 1e9, y1[id], y2[id], dp[id]);
	V[p].emplace_back(id);
}
void Pushdown(int p)
{
	for (auto i : V[p])
	{
		Maintain(ls[p], i);
		Maintain(rs[p], i);
	}
	V[p].clear();
}
void insert(int &p, int l, int r, const int &id)
{
	if (!p) p = newnode();
//	printf("Out insert %d %d %d %d %lld\n", p, l, r, id, dp[id]);
	if (x1[id] <= l && r <= x2[id]) Maintain(p, id);
	else
	{
		if (V[p].size()) Pushdown(p);
		insert(rt[p], 1, 1e9, y1[id], y2[id], dp[id]);
		if (x1[id] <= mid) insert(lson, id);
		if (x2[id] >  mid) insert(rson, id);
	}
}

long long query(int &p, int l, int r, const int &L, const int &R)
{
	if (!p) return 0;
//	printf("In query %d %d %d %d %d\n", p, l, r, L, R);
	if (L <= l && r <= R) return s[p];
	else
	{
		if (tag[p]) pushdown(p, l, r);
		if (R <= mid) return query(lson, L, R);
		if (L >  mid) return query(rson, L, R);
		long long res = query(lson, L, R) + query(rson, L, R);
		if (res >= MOD) res -= MOD;
		return res;
	}
}
long long query(int &p, int l, int r, const int &id)
{
	if (!p) return 0;
//	printf("Out query %d %d %d %d\n", p, l, r, id);
	if (x1[id] <= l && r <= x2[id]) return query(rt[p], 1, 1e9, y1[id], y2[id]);
	else
	{
		if (V[p].size()) Pushdown(p);
		if (x2[id] <= mid) return query(lson, id);
		if (x1[id] >  mid) return query(rson, id);
		long long res = query(lson, id) + query(rson, id);
		if (res >= MOD) res -= MOD;
		return res;
	}
}

int main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read<int>();
	REP(i, 1, n)
	{
		x1[i] = read<int>(), y1[i] = read<int>(), x2[i] = read<int>(), y2[i] = read<int>();
		b[++m] = x1[i];
		b[++m] = x2[i];
	}
	/*
	sort(b + 1, b + 1 + m);
	m = unique(b + 1, b + 1 + m) - b - 1;
	REP(i, 1, n)
	{
		x1[i] = lower_bound(b + 1, b + 1 + m, x1[i]) - b;
		x2[i] = lower_bound(b + 1, b + 1 + m, x2[i]) - b;
	}
	*/
	int ans = 0;
	int rt = 1;
	REP(i, 1, n)
	{
		dp[i] = (1 + query(rt, 1, 1e9, i)) % MOD;
		insert(rt, 1, 1e9, i);
		ans += dp[i];
		if (ans >= MOD) ans -= MOD;
	}
	cout << ans << endl;
	return 0;
}
