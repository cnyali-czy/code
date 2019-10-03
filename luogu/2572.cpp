#define  REP(i, s, e) for (int i(s), end_##i(e); i <= end_##i; i++)
#define DREP(i, s, e) for (int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>
#include <set>

using namespace std;
const int maxn = 1e5 + 10;

int n, m;

struct node
{
	int l, r;
	mutable bool v;
	node(int _l = 0, int _r = -1, bool _v = 0) : l(_l), r(_r), v(_v) {}
	bool operator < (node B) const {return l < B.l;}
};
set <node> S;
#define IT set <node> :: iterator

inline IT split(int pos)
{
	auto it = S.lower_bound(node(pos));
	if (it != S.end() && it -> l == pos) return it;
	it--;
	int l(it -> l), r(it -> r);
	bool v(it ->v);
	S.erase(it);
	S.emplace(l, pos-1, v);
	return S.emplace(pos, r, v).first;
}
inline void assign(int l, int r, bool v)
{
	auto itr = split(r+1), itl = split(l);
	S.erase(itl, itr);
	S.emplace(l, r, v);
}
inline void reverse(int l, int r)
{
	auto itr = split(r+1), itl = split(l);
	while (itl != itr)
	{
		itl -> v ^= 1;
		itl++;
	}
}
inline int sum(int l, int r)
{
	auto itr = split(r+1), itl = split(l);
	int ans(0);
	while (itl != itr)
	{
		ans += itl -> v * (itl -> r - itl -> l + 1);
		itl++;
	}
	return ans;
}
inline int query(int l, int r)
{
	int res(0), tmp(0);
	auto itr = split(r+1), itl = split(l);
	while (itl != itr)
	{
		if (!itl -> v)
		{
			chkmax(res, tmp);
			tmp = 0;
		}
		else tmp += itl -> r - itl -> l + 1;
		itl++;
	}
	return max(res, tmp);
}

int main()
{
#ifdef CraZYali
	freopen("2572.in", "r", stdin);
	freopen("2572.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 0, n - 1)
	{
		int qaq;
		scanf("%d", &qaq);
		S.emplace(i, i, qaq);
	}
	while (m--)
	{
		int opt, a, b;
		scanf("%d%d%d", &opt, &a, &b);
		switch (opt)
		{
			case 0:
				assign(a, b, 0);
				break;
			case 1:
				assign(a, b, 1);
				break;
			case 2:
				reverse(a, b);
				break;
			case 3:
				printf("%d\n", sum(a, b));
				break;
			case 4:
				printf("%d\n", query(a, b));
				break;
		}
	}
	return 0;
}
