#define  REP(i, s, e) for (int i(s), end_##i(e); i <= end_##i; i++)
#define DREP(i, s, e) for (int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <ctime>
#include <iostream>
#include <cstdio>
#include <set>

using namespace std;
const int maxn = 200000 + 10;

int n, m;

struct node
{
	int l, r;
	mutable bool v;
	node(int _l = 0, int _r = -1, bool _v = 0) : l(_l), r(_r), v(_v) {}
	inline bool operator < (node B) const {return l < B.l;}
};
set <node> S;
using IT = set <node> :: iterator;

IT split(int pos)
{
	auto it = S.lower_bound(node(pos));
	if (it != S.end() && it -> l == pos) return it;
	it--;
	int l(it -> l), r(it -> r);
	bool v(it -> v);
	S.erase(it);
	if (l < pos) S.emplace(l, pos - 1, v);
	return S.emplace(pos, r, v).first;
}
inline void assign(int l, int r, bool v)
{
	auto itr = split(r + 1), itl = split(l);
	S.erase(itl, itr);
	S.emplace(l, r, v);
}
inline int sum(int l, int r)
{
	auto itr = split(r + 1), itl = split(l);
	int res(0);
	while (itl != itr)
	{
		res += itl -> v * (itl -> r - itl -> l + 1);
		itl++;
	}
	return res;
}
inline int Max(int l, int r)
{
	auto itr = split(r + 1), itl = split(l);
	int res(0), tmp(0);
	while (itl != itr)
	{
		if (itl -> v)
		{
			chkmax(res, tmp);
			tmp = 0;
		}
		else tmp += itl -> r - itl -> l + 1;
		itl++;
	}
	return max(res, tmp);
}
inline void move(int l0, int r0, int l1, int r1)
{
	int qaq(sum(l0, r0));
	assign(l0, r0, 0);
	auto itr = split(r1 + 1), itl = split(l1);
	while (itl != itr)
	{
		if (!qaq) return;
		if (!itl -> v)
		{
			int l(itl -> l), r(itl -> r), len = r - l + 1;
			if (qaq >= len)
			{
				qaq -= len;
				itl -> v = 1;
			}
			else
			{
				int able = qaq, L = l + able;
				assign(l, L - 1, 1);
				return;
			}
		}
		itl++;
	}
}

int main()
{
#ifdef CraZYali
	freopen("4344.in", "r", stdin);
	freopen("4344.out", "w", stdout);
#endif
	cin >> n >> m;
	S.emplace(1, n, 1);
	while (m--)
	{
		int opt, l, r, L, R;
		scanf("%d%d%d", &opt, &l, &r);
		if (!opt) assign(l, r, 0);
		else if (opt == 1)
		{
			scanf("%d%d", &L, &R);
			move(l, r, L, R);
		}
		else printf("%d\n", Max(l, r));
	}
	return 0;
}
