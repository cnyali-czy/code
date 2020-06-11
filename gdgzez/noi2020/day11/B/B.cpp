/*
	Problem:	B.cpp
	Time:		2020-06-11 08:18
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <ctime>
#include <cassert>
#include <algorithm>
#include <queue>
#include <iostream>
#include <cstdio>
#define i64 long long
using namespace std;
const int maxn = 5e5 + 10, maxm = 5e5 + 10;

#ifndef CraZYali
#define getchar getchar_unlocked
#endif
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

int n, m, a[maxn], k[maxm];

namespace bf
{
	priority_queue <int> q, tmp;
	void work()
	{
		while (!q.empty()) q.pop();
		REP(i, 1, n) q.push(a[i]);
		i64 ans = 0;
		REP(i, 1, m)
		{
			REP(j, 1, k[i])
			{
				int x = q.top();q.pop();
				ans += x;tmp.push(--x);
			}
			while (!tmp.empty()) q.push(tmp.top()), tmp.pop();
		}
		printf("%lld\n", ans);
	}
}

namespace shit
{
	struct 
	{
		int l, r, val, tag, s, order, sum;
	}Node[maxn];
#define ls(x) Node[x].l
#define rs(x) Node[x].r
#define val(x) Node[x].val
#define tag(x) Node[x].tag
#define s(x) Node[x].s
#define order(x) Node[x].order
#define sum(x) Node[x].sum
#define pushup(x)\
	{\
		s(x) = 1 + s(ls(x)) + s(rs(x));\
		sum(x) = val(x) + sum(ls(x)) + sum(rs(x));\
	}
	inline void maintain(int x, int v)
	{
		val(x) += v;
		sum(x) += s(x) * v;
		tag(x) += v;
	}
	inline void pushdown(int x)
	{
		if (ls(x)) maintain(ls(x), tag(x));
		if (rs(x)) maintain(rs(x), tag(x));
		tag(x) = 0;
	}
	void split(int x, int &a, int &b, int siz)
	{
		if (!x) a = b = 0;
		else
		{
			if (tag(x)) pushdown(x);
			if (s(ls(x)) >= siz) split(ls(b = x), a, ls(x), siz);
			else split(rs(a = x), rs(x), b, siz - s(ls(x)) - 1);
			pushup(x);
		}
	}
	void merge(int &x, int a, int b)
	{
		if (!a || !b) x = a | b;
		else
		{
			if (order(a) > order(b))
			{
				if (tag(b)) pushdown(b);
				merge(ls(x = b), a, ls(b));
			}
			else
			{
				if (tag(a)) pushdown(a);
				merge(rs(x = a), rs(a), b);
			}
			pushup(x);
		}
	}
	int get(int p, int k)
	{
		if (tag(p)) pushdown(p);
		if (k <= s(ls(p))) return get(ls(p), k);
		else if (k == s(ls(p)) + 1) return val(p);
		else return get(rs(p), k - s(ls(p)) - 1);
	}
	void splitl(int x, int &a, int &b, const int &v)
	{
		if (!x) a = b = 0;
		else
		{
			if (tag(x)) pushdown(x);
			if (val(x) < v)	splitl(ls(b = x), a, ls(x), v);
			else			splitl(rs(a = x), rs(x), b, v);
			pushup(x);
		}
	}
	void splitr(int x, int &a, int &b, const int &v)
	{
		if (!x) a = b = 0;
		else
		{
			if (tag(x)) pushdown(x);
			if (val(x) <= v)	splitr(ls(b = x), a, ls(x), v);
			else				splitr(rs(a = x), rs(x), b, v);
			pushup(x);
		}
	}

	void work()
	{
		sort(a + 1, a + 1 + n, greater <int> ());
		sort(k + 1, k + 1 + m);
		int rt = 0;
		ls(0) = rs(0) = s(0) = 0;
		REP(i, 1, n)
		{
			val(i) = sum(i) = a[i];
			ls(i) = rs(i) = 0;
			s(i) = 1;
			order(i) = rand();
			merge(rt, rt, i);
		}
		i64 ans = 0;
		int lst;
		bool first = 0;
		REP(i, 1, m)
		{
			int x(0), y(0), z(0), w(0);
			split(rt, x, y, k[i]);
			ans += sum(x);
			maintain(x, -1);
			if (k[i] == n) merge(rt, x, y);
			else
			{
				int qaq = get(x, s(x));
				if (i == 1 || first || k[i] ^ k[i - 1]) lst = get(y, 1), first = 0;
				int aqa = lst;
				if (qaq < aqa)
				{
					first = 1;
					int gd;
					splitl(y, y, z, aqa);
//					gd = splitl(y, aqa);
//					split(y, y, z, gd);
//					splitr(x, w, x, qaq);
					splitr(x, x, w, qaq);
//					gd = s(x) - splitr(x, qaq);
//					split(x, x, w, gd);
					merge(x, x, y);merge(w, w, z);
					merge(rt, x, w);
				}
				else merge(rt, x, y);
			}
		}
		printf("%lld\n", ans);
	}
}

int main()
{
#ifdef CraZYali
	file("B");
#endif
	srand(time(0));
	n = read<int>();
	REP(i, 1, n) a[i] = read<int>();
	m = read<int>();
	REP(i, 1, m) k[i] = read<int>();
	shit :: work();
	//	bf :: work();
	return 0;
}
