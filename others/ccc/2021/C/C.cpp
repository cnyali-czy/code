#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)

#include <algorithm>
#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 2e5 + 10;

int n, N, p[maxn], w[maxn], d[maxn];
inline int read()
{
	char c = getchar();
	while (!isdigit(c)) c = getchar();
	int res = 0;
	while (isdigit(c)) res = res * 10 + (c - 48), c = getchar();
	return res;
}

int a[maxn << 1];
#define pii pair <i64, i64>

pii operator + (const pii &A, const pii &B) {return make_pair(A.first + B.first, A.second + B.second);}

namespace SMT
{
	const int maxN = 2e7;
	int ls[maxN], rs[maxN], cur;
	pair <i64, i64> s[maxN];
#define lson ls[p], l, mid
#define rson rs[p], mid + 1, r
#define mid (((i64)l + r) >> 1)
	void update(int &p, int l, int r, int pos, pair <i64, i64> v)
	{
		if (!p) p = ++cur;
		s[p] = s[p] + v;
		if (l == r) return;
		if (pos <= mid) update(lson, pos, v);
		else update(rson, pos, v);
	}
	pair <i64, i64> query(int p, int l, int r, int L, int R)
	{
		if (!p) return make_pair(0, 0);
		if (L <= l && r <= R) return s[p];
		else
		{
			if (R <= mid) return query(lson, L, R);
			if (L >  mid) return query(rson, L, R);
			return query(lson, L, R) + query(rson, L, R);
		}
	}
}

int main()
{
#ifdef CraZYali
	freopen("C.in", "r", stdin);
	freopen("C.out", "w", stdout);
#endif
	n = read();
	REP(i, 1, n)
	{
		p[i] = read(), w[i] = read(), d[i] = read();
		a[++N] = p[i] + d[i];
		a[++N] = p[i] - d[i];
	}
	sort(a + 1, a + 1 + N);
	int L = a[1], R = a[N];
	int rt1 = 0, rt2 = 0;
	REP(i, 1, n)
	{
		SMT :: update(rt1, L, R, p[i] + d[i], make_pair(w[i], 1ll * w[i] * (p[i] + d[i])));
		SMT :: update(rt2, L, R, p[i] - d[i], make_pair(w[i], 1ll * w[i] * (p[i] - d[i])));
	}
	i64 ans = 9e18;
	REP(i, 1, N)
	{
		i64 res = 0, x = a[i];
		auto info = SMT :: query(rt1, L, R, L, x);
		res += info.first * x;res -= info.second ;
		info = SMT :: query(rt2, L, R, x, R);
		res -= info.first * x;res += info.second ;
		/*
		   if (x >= p[j] + d[j])
		   res += (x - p[j] - d[j]) * w[j];
		   if (x <= p[j] - d[j])
		   res += (p[j] - x - d[j]) * w[j];
		   */
		ans = min(ans, res);
	}
	cout << ans << endl;

	return 0;
}
