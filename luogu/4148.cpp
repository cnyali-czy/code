/*
	Problem:	4148.cpp
	Time:		2020-02-26 17:54
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cstdio>

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
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

namespace KDT
{
	struct node
	{
		int x, y, z;
		node(int x = 0, int y = 0, int z = 0) : x(x), y(y), z(z) {}
	};
	int s[maxn], ch[maxn][2], lx[maxn], rx[maxn], ly[maxn], ry[maxn], sv[maxn], rt;
	node v[maxn];
#define xx(p) v[p].x
#define yy(p) v[p].y
#define ls(p) ch[p][0]
#define rs(p) ch[p][1]
	int stack[maxn], top;
	struct __init__
	{
		__init__()
		{
			REP(i, 1, maxn - 1) stack[++top] = i;
		}
	}__INIT__;
	inline int newnode(node x)
	{
		int cur = stack[top--];
		s[cur] = 1;
		sv[cur] = x.z;
		v[cur] = x;
		lx[cur] = rx[cur] = x.x;
		ly[cur] = ry[cur] = x.y;
		return cur;
	}
	node mem[maxn];
	int ccc;
	void pia(int &p)
	{
		mem[++ccc] = v[p];
		stack[++top] = p;
		if (ls(p)) pia(ls(p));
		if (rs(p)) pia(rs(p));
		p = 0;
	}
	inline bool cmp1(const node &A, const node &B) {return A.x < B.x;}
	inline bool cmp0(const node &A, const node &B) {return A.y < B.y;}
	int build(int l, int r, bool flag)
	{
		if (l == r) return newnode(mem[l]);
		int mid = l + r >> 1;
		nth_element(mem + l, mem + mid, mem + r + 1, flag ? cmp1 : cmp0);
		int p = newnode(mem[mid]);
		if (l < mid)
		{
			ls(p) = build(l, mid - 1, !flag);
			chkmin(lx[p], lx[ls(p)]);chkmax(rx[p], rx[ls(p)]);
			chkmin(ly[p], ly[ls(p)]);chkmax(ry[p], ry[ls(p)]);
			s[p] += s[ls(p)];sv[p] += sv[ls(p)];
		}
		if (mid < r)
		{
			rs(p) = build(mid + 1, r, !flag);
			chkmin(lx[p], lx[rs(p)]);chkmax(rx[p], rx[rs(p)]);
			chkmin(ly[p], ly[rs(p)]);chkmax(ry[p], ry[rs(p)]);
			s[p] += s[rs(p)];sv[p] += sv[rs(p)];
		}
		return p;
	}
	const double alpha = .75;
	int *lst;bool Flag;
	inline void check(int &p, bool flag)
	{
		if (s[p] * alpha <= max(s[ls(p)], s[rs(p)])) 
		{
			lst = &p;
			Flag = flag;
		}
	}

	void insert(int &p, node i, bool flag = 1)
	{
		if (!p)
		{
			p = newnode(i);
			return;
		}
		chkmin(lx[p], i.x);chkmax(rx[p], i.x);
		chkmin(ly[p], i.y);chkmax(ry[p], i.y);
		sv[p] += i.z;
		s[p]++;
		insert(ch[p][flag ? xx(p) > i.x : yy(p) > i.y], i, !flag);
		if (p != rt) check(p, flag);
	}
	int query(const int &p, int x1, int y1, int x2, int y2)
	{
		if (!p) return 0;
		if (lx[p] > x2 || rx[p] < x1 || ly[p] > y2 || ry[p] < y1) return 0;
		if (x1 <= lx[p] && rx[p] <= x2 && y1 <= ly[p] && ry[p] <= y2) return sv[p];
		int res = (x1 <= xx(p) && xx(p) <= x2 && y1 <= yy(p) && yy(p) <= y2) * v[p].z;
		if (ls(p)) res += query(ls(p), x1, y1, x2, y2);
		if (rs(p)) res += query(rs(p), x1, y1, x2, y2);
		return res;
	}
}
int ans;
int main()
{
#ifdef CraZYali
	file("4148");
#endif
	int n = read<int>();
	while (1)
	{
		int opt = read<int>();
		if (opt == 1)
		{
			int x(read<int>() ^ ans), y(read<int>() ^ ans), z(read<int>() ^ ans);
			KDT::insert(KDT::rt, KDT::node(x, y, z));
		}
		else if (opt == 2)
		{
			int x1(read<int>() ^ ans), y1(read<int>() ^ ans), x2(read<int>() ^ ans), y2(read<int>() ^ ans);
			printf("%d\n", ans = KDT::query(KDT::rt, x1, y1, x2, y2));
		}
		else return 0;
	}
	return 0;
}
