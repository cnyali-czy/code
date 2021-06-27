/*
	Problem:	A.cpp
	Time:		2021-06-21 19:08
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <set>
#include <algorithm>
#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 2e5 + 10;

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

const i64 N = 1e18;
inline pair <int, i64> operator + (pair <int, i64> A, pair <int, i64> B)
{
	return make_pair(A.first + B.first, A.second + B.second);
}
namespace SMT
{
	const int maxN = 2e7;
	int ls[maxN], rs[maxN], cur;
	int s1[maxN];i64 s2[maxN];
#define lson ls[p], l, mid
#define rson rs[p], mid + 1, r
#define mid (l + r >> 1)
	void ins(int &p, i64 l, i64 r, i64 pos, int val)
	{
		if (!p) p = ++cur;
		s1[p] += val;
		s2[p] += val * pos;
		if (l == r) return;
		if (pos <= mid) ins(lson, pos, val);
		else ins(rson, pos, val);
	}
	pair <int, i64> query(int p, i64 l, i64 r, i64 L, i64 R)
	{
		if (!p) return make_pair(0, 0);
		if (L <= l && r <= R) return make_pair(s1[p], s2[p]);
		else
		{
			if (R <= mid) return query(lson, L, R);
			if (L >  mid) return query(rson, L, R);
			return query(lson, L, R) + query(rson, L, R);
		}
	}
}
struct seg
{
	int l, r, val;
	seg(int l = 0, int r = 0, int val = 0) : l(l), r(r), val(val) {}
	inline bool operator < (const seg &B) const {return l < B.l;}
};
set <seg> s;
#define IT set <seg> :: iterator
IT split(int pos)
{
	if (pos > n) return s.end();
	auto it = s.lower_bound(seg(pos));
	if (it != s.end() && it -> l == pos) return it;
	--it;
	int L = it -> l, R = it -> r, val = it -> val;
	s.erase(it);
	s.emplace(L, pos - 1, val);
	return s.emplace(pos, R, val).first;
}

signed main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();q = read<int>();
	int rt = 0;
	REP(i, 1, n)
	{
		int x = read<int>();
		s.emplace(i, i, x);
		SMT :: ins(rt, 0, N, x, 1);
	}
	while (q--)
	{
		char c = getchar();
		while (!isalpha(c)) c = getchar();
		if (c == 'Q')
		{
			i64 V = read<i64>(), vv = V;
			i64 l = 0, r = N, flr = 1, p = rt;
			pair <int, i64> had(0, 0);
			while (1)
			{
				auto sb = make_pair(SMT :: s1[SMT :: ls[p]], SMT :: s2[SMT :: ls[p]]) + had;
				__int128 res = (__int128) sb.first * mid - sb.second;
				if (res <= V) flr = mid;
				if (l == r) break;

				if (res <= V)
				{
					had = sb;
					l = mid + 1;
					p = SMT :: rs[p];
				}
				else r = mid, p = SMT :: ls[p];
			}
			V = vv;
			i64 up = V, down = 0;
			/*
			REP(i, 1, n) if (a[i] <= flr)
			{
				up += a[i];
				down++;
			}*/
			auto sb = SMT :: query(rt, 0, N, 0, flr);
			up += sb.second;
			down += sb.first;
			i64 g = __gcd(up, down);
			printf("%lld/%lld\n", up / g, down / g);
		}
		else
		{
			int l = read<int>(), r = read<int>(), v = read<int>();
			auto itr = split(r + 1), itl = split(l);
			for (auto it = itl; it != itr; it++)
				SMT :: ins(rt, 0, N, it -> val, -(it -> r - it -> l + 1));
			s.erase(itl, itr);
			s.emplace(l, r, v);
			SMT :: ins(rt, 0, N, v, r - l + 1);
//			REP(i, l, r) a[i] = v;
		}
	}
	return 0;
}
