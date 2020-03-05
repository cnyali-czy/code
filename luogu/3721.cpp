/*
	Problem:	3721.cpp
	Time:		2020-03-05 15:07
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

using namespace std;
const int maxn = 3e5 + 10, inf = 1e9;

int n, m, rt;

namespace LCT
{
	int ch[maxn][2], fa[maxn], s[maxn], cur;
	bool rev[maxn];
#define ls(x) ch[x][0]
#define rs(x) ch[x][1]
#define get(x) (rs(fa[x]) == x)
#define notroot(x) (ls(fa[x]) == x || rs(fa[x]) == x)
	inline void pushup(int x) {s[x] = s[ls(x)] + s[rs(x)] + 1;}
	inline void rotate(int x)
	{
		int y(fa[x]), z(fa[y]), k(get(x));
		fa[x] = z;
		if (notroot(y)) ch[z][get(y)] = x;
		ch[y][k] = ch[x][k ^ 1];
		fa[ch[x][k ^ 1]] = y;
		ch[x][k ^ 1] = y;
		fa[y] = x;
		pushup(y);pushup(x);
	}
	inline void pushdown(int x)
	{
		swap(ls(x), rs(x));
		if (ls(x)) rev[ls(x)] ^= 1;
		if (rs(x)) rev[rs(x)] ^= 1;
		rev[x] = 0;
	}
	void pushall(int x)
	{
		if (notroot(x)) pushall(fa[x]);
		if (rev[x]) pushdown(x);
	}
	void splay(int x)
	{
		pushall(x);
		while (notroot(x))
		{
			int y = fa[x];
			if (notroot(y)) rotate(get(x) == get(y) ? y : x);
			rotate(x);
		}
	}
	void access(int x)
	{
		for (int y = 0; x; x = fa[y = x])
		{
			splay(x);
			rs(x) = y;
			pushup(x);
		}
	}
	void makeroot(int x)
	{
		access(x);
		splay(x);
		rev[x] ^= 1;
	}
	void link(int x, int y)
	{
		if (!x || !y) return;
		makeroot(x);
		fa[x] = y;
	}
	void cut(int x, int y)
	{
		if (!x || !y) return;
		makeroot(x);
		access(y);
		splay(y);
		ls(y) = fa[x] = 0;
		pushup(x);pushup(y);
	}
	int getdep(int x)
	{
		makeroot(rt);
		access(x);
		splay(x);
		return s[x];
	}
}

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

int opt[maxn], key[maxn], b[maxn], N, ch[maxn][2], fa[maxn];
set <int> S;
int main()
{
#ifdef CraZYali
	file("3721");
#endif
	m = read<int>();
	REP(i, 1, m)
	{
		opt[i] = read<int>();
		if (opt[i] == 1) b[++N] = key[i] = read<int>();
	}
	sort(b + 1, b + 1 + N);N = unique(b + 1, b + 1 + N) - b - 1;
	S.emplace(-inf);S.emplace(inf);
	REP(i, 1, m)
	{
		int opt = ::opt[i];
		if (opt == 1)
		{
			n++;
			int val = lower_bound(b + 1, b + 1 + N, key[i]) - b;
			if (n == 1) {S.emplace(rt = val);cout << "1\n";continue;}
			auto it = S.upper_bound(val);
			int nxt = *it, dep = 0, fa = 0, pre = *(--it);
			if (-inf < pre)
			{
				int tmp = LCT::getdep(pre);
				if (tmp > dep)
				{
					dep = tmp;
					fa = pre;
				}
			}
			if (nxt < inf)
			{
				int tmp = LCT::getdep(nxt);
				if (tmp > dep)
				{
					dep = tmp;
					fa = nxt;
				}
			}
			cout << dep + 1 << '\n';
			S.emplace(val);
			ch[fa][val > fa] = val;
			::fa[val] = fa;
			LCT::link(fa, val);
		}
		else if (opt == 2)
		{
			if (n == 1) {cout << "1\n";continue;}
			auto it = ++S.begin();
			int x = *it, y = rs(x), z = fa[x], k = LCT::getdep(x);
			if (x ^ rt)
			{
				LCT::cut(x, z);LCT::cut(x, y);
				LCT::link(x, rt);LCT::link(z, y);
				fa[x] = 0;
				fa[rs(x) = rt] = x;
				rt = x;
				fa[ls(z) = y] = z;
			}
			cout << k << '\n';
		}
		else if (opt == 3)
		{
			if (n == 1) {cout << "1\n";continue;}
			auto it = --(--S.end());
			int x = *it, y = ls(x), z = fa[x], k = LCT::getdep(x);
			if (x ^ rt)
			{
				LCT::cut(x, z);LCT::cut(x, y);
				LCT::link(x, rt);LCT::link(z, y);
				fa[x] = 0;
				fa[ls(x) = rt] = x;
				rt = x;
				fa[rs(z) = y] = z;
			}
			cout << k << '\n';
		}
		else if (opt == 4)
		{
			--n;
			if (!n) {cout << "1\n";S.erase(rt);rt = 0;continue;}
			auto it = ++S.begin();
			int x = *it, y = rs(x), z = fa[x], k = LCT::getdep(x);
			LCT::cut(x, z);LCT::cut(x, y);
			LCT::link(y, z);
			S.erase(x);
			if (x == rt) rt = y;
			ls(x) = rs(x) = fa[x] = 0;
			fa[ls(z) = y] = z;
			cout << k << '\n';
		}
		else if (opt == 5)
		{
			--n;
			if (!n) {cout << "1\n";S.erase(rt);rt = 0;continue;}
			auto it = --(--S.end());
			int x = *it, y = ls(x), z = fa[x], k = LCT::getdep(x);
			LCT::cut(x, z);LCT::cut(x, y);
			LCT::link(y, z);
			S.erase(x);
			if (x == rt) rt = y;
			ls(x) = rs(x) = fa[x] = 0;
			fa[rs(z) = y] = z;
			cout << k << '\n';
		}
	}
	return 0;
}
