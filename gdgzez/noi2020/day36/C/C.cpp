/*
	Problem:	C.cpp
	Time:		2020-07-31 10:20
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <cstdio>
#define int long long
using namespace std;
const int maxn = 3e5 + 10;

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

int q, w;

#define Vector pair <int, int>
#define x first
#define y second

inline int operator * (Vector A, Vector B) {return A.x * B.y - B.x * A.y;}
Vector stk[maxn];int n;

void fix()
{
	DEP(i, n, 2)
		if (stk[i] * stk[i - 1] >= w)
			swap(stk[i], stk[i - 1]);
}

namespace bf
{
	void work()
	{
		while (q--)
		{
			int opt = read<int>();
			if (opt == 1)
			{
				int h = read<int>(), m = read<int>();
				stk[++n] = make_pair(h, m);
				fix();
			}
			else
			{
				int k = read<int>();
				printf("%lld %lld\n", stk[k].x, stk[k].y);
			}
		}
	}
}

namespace cheat
{
	int h[maxn], m[maxn];
	int rt, cur;
	const double eps = 1e-9;
	struct node
	{
		double angle;
		int id, s, l, r, order;
		node(double angle = 0, int id = 0, int s = 0, int l = 0, int r = 0) : angle(angle), id(id), s(s), l(l), r(r), order(rand()) {}
		inline bool operator < (const node &B) const
		{
			if (angle + eps < B.angle) return 1;
			if (B.angle + eps < angle) return 0;
			return id > B.id;
		}
	}t[maxn];
#define angle(x) t[x].angle
#define id(x) t[x].id
#define s(x) t[x].s
#define l(x) t[x].l
#define r(x) t[x].r
#define order(x) t[x].order
	inline int newnode(int id)
	{
		t[++cur] = node(atan2(m[id], h[id]), id, 1);
		return cur;
	}
	inline void maintain(int x) {s(x) = s(l(x)) + s(r(x)) + 1;}
	void merge(int &x, int a, int b)
	{
		if (!a || !b) x = a + b;
		else
		{
			if (order(a) > order(b))	merge(l(x = b), a, l(b));
			else						merge(r(x = a), r(a), b);
			maintain(x);
		}
	}
	void split(int x, int &a, int &b, int New)
	{
		if (!x) a = b = 0;
		else
		{
			if (t[New] < t[x])	split(l(b = x), a, l(x), New);
			else				split(r(a = x), r(x), b, New);
			maintain(x);
		}
	}
	int kth(int k, int x = rt)
	{
		while (1)
		{
			int sl = s(l(x));
			if (sl + 1 == k) return id(x);
			else if (sl >=k) x = l(x);
			else k -= sl + 1, x = r(x);
		}
	}
	void dfs(int x)
	{
		if (l(x)) dfs(l(x));
		printf("(%lld, %lld) ", h[id(x)], m[id(x)]);
		if (r(x)) dfs(r(x));
	}
	void work()
	{
#ifdef CraZYali
		DEBUG;
#endif
		while (q--)
		{
			int opt = read<int>();
			if (opt == 1)
			{
				++n;
				h[n] = read<int>();
				m[n] = read<int>();
				int x(0), y(0);
				split(rt, x, y, newnode(n));
				merge(x, x, cur);
				merge(rt, x, y);
			}
			else
			{
				int real = kth(read<int>());
				printf("%lld %lld\n", h[real], m[real]);
			}
		}
	}
}

signed main()
{
#ifdef CraZYali
	file("C");
#endif
	q = read<int>();w = read<int>();
	if (w == 1) cheat :: work();
	else bf :: work();
	return 0;
}
