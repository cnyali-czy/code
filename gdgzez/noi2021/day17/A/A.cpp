/*
	Problem:	A.cpp
	Time:		2021-03-25 14:33
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 1e6 + 10;
inline char nc()
{
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
#define getchar nc
	template <typename T>
inline T read()
{
	T ans = 0;
	char c = getchar();
	while (!isdigit(c)) c = getchar();
	while (isdigit(c))
	{
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, m[maxn], b[maxn], M;

int pos[maxn];
vector <int> v[maxn];

int q;pair <int, pair <int, int> > qry[maxn];

namespace SMT
{
	i64 s[maxn << 2], t[maxn << 2];
#define ls p << 1
#define rs p << 1 | 1
#define mid (l + r >> 1)
#define lson ls, l, mid
#define rson rs, mid + 1, r
	void update(int p, int l, int r, int L, int R)
	{
		s[p] += R - L + 1;
		if (L <= l && r <= R) return void(t[p]++);
		else
		{
			if (L <= mid) update(lson, L, min(R, mid));
			if (R >  mid) update(rson, max(L, mid + 1), R);
		}
	}
	i64 query(int p, int l, int r, int L, int R, i64 ard = 0)
	{
		if (L <= l && r <= R) return ard * (r - l + 1) + s[p];
		else
		{
			ard += t[p];
			if (R <= mid) return query(lson, L, R, ard);
			if (L >  mid) return query(rson, L, R, ard);
			return query(lson, L, R, ard) + query(rson, L, R, ard);
		}
	}
}
i64 ans[maxn];

namespace PQ
{
	int r[maxn], d[maxn], t1, t2;
	void clear() {t1 = t2 = 0;}
	void ins(int x) {r[++t1] = x;}
	void del(int x) {d[++t2] = x;}
	int top()
	{
		while (t2 && r[t1] == d[t2]) t1--, t2--;
		return r[t1];
	}
}
int prime[maxn], mi[maxn], p_cnt;
bool notp[maxn];
void init(int n)
{
	REP(i, 2, n)
	{
		if (!notp[i])
		{
			prime[++p_cnt] = i;
			mi[i] = i;
		}
		REP(j, 1, p_cnt)
		{
			int t = i * prime[j];
			if (t > n) break;
			notp[t] = 1;
			if (i % prime[j]) mi[t] = prime[j];
			else {mi[t] = mi[i];break;}
		}
	}
}
namespace fenwick
{
	i64 s1[maxn], s2[maxn];
	void add(int x, int y)
	{
		for (int z = x; z <= n; z += z & -z)
		{
			s1[z] += y;
			s2[z] += 1ll * x * y;
		}
	}
	void add(int l, int r, int v)
	{
		add(l, v);
		add(r + 1, -v);
	}
	i64 sum(int x)
	{
		i64 y = 0;
		for (int z = x; z > 0; z &= (z - 1))
		{
			y += (x + 1ll) * s1[z];
			y -= s2[z];
		}
		return y;
	}
	i64 sum(int l, int r) {return sum(r) - sum(l - 1);}
}
#define fi first
#define se second

int main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();
	REP(i, 1, n) m[i] = read<int>(), b[i] = read<int>(), M = max(M, m[i]);
	init(M);

	REP(i, 1, n)
	{
		int x = m[i];
		while (x > 1)
		{
			const int p = mi[x];int pk = 1;
			while (x % p == 0)
			{
				x /= p;
				pk *= p;
				v[pk].emplace_back(i);
			}
		}
	}

	REP(i, 1, n) pos[i] = 1;
	REP(G, 2, M) if (v[G].size())
	{
		const int g = G;

		static int A[maxn];
		PQ :: clear();
		for (int i : v[G])
		{
			int val = b[i] % g;
			if (A[val]) PQ :: del(A[val]);
			pos[i] = max(pos[i], PQ :: top() + 1);
			PQ :: ins(A[val] = i);
		}
		for (int i : v[G]) A[b[i] % g] = 0;
	}
	REP(i, 1, n) pos[i] = max(pos[i], pos[i - 1]);

	q = read<int>();
	REP(i, 1, q)
	{
		int l = read<int>(), r = read<int>();
		qry[i] = make_pair(r, make_pair(l, i));
	}
	sort(qry + 1, qry + 1 + q);

	int j = 1;
	REP(i, 1, n)
	{
		fenwick :: add(pos[i], i, 1);
		if (qry[j].fi != i) continue;
		i64 si = fenwick :: sum(i);
		while (j <= q && qry[j].fi == i)
		{
			ans[qry[j].se.se] = si - fenwick :: sum(qry[j].se.fi - 1);
			j++;
		}
	}
	REP(i, 1, q) printf("%lld\n", ans[i]);
	return 0;
}
