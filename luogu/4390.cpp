/*
 * File Name:	4390.cpp
 * Author	:	CraZYali
 * Year		:	2019.09.22 21:03
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 160000 + 5;

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

bool type;
int n;

struct point
{
	int x, y, v;
	inline bool operator < (point B)
	{
		return type ? x < B.x : y < B.y;
	}
	point() : v(0) {}
}store[maxn];
int cur;

const double alpha = .7;

struct node
{
	int ch[2], lx, rx, ly, ry, s;
	long long sum;
	point info;
	node() {}
	node(point _info) : info(_info)
	{
		lx = rx = info.x;
		ly = ry = info.y;
		s = 1;
		sum = info.v;
		ch[0] = ch[1] = 0;
	}
}t[maxn];

#define ls(p) t[p].ch[0]
#define rs(p) t[p].ch[1]

inline int pushup(int p)
{
	t[p].s = t[ls(p)].s + t[rs(p)].s + 1;
	t[p].sum = t[ls(p)].sum + t[rs(p)].sum + t[p].info.v;
	t[p].lx = t[p].rx = t[p].info.x;
	t[p].ly = t[p].ry = t[p].info.y;

	if (ls(p))
	{
		chkmin(t[p].lx, t[ls(p)].lx);
		chkmin(t[p].ly, t[ls(p)].ly);
		chkmax(t[p].rx, t[ls(p)].rx);
		chkmax(t[p].ry, t[ls(p)].ry);
	}
	if (rs(p))
	{
		chkmin(t[p].lx, t[rs(p)].lx);
		chkmin(t[p].ly, t[rs(p)].ly);
		chkmax(t[p].rx, t[rs(p)].rx);
		chkmax(t[p].ry, t[rs(p)].ry);
	}
	return p;
}

#define mid (l + r >> 1)

int mem[maxn], top;
inline void init(const int N = 160000)
{
	REP(i, 1, top = N) mem[i] = i;
}

inline int newnode(point _info)
{
	int p = mem[top--];
	t[p] = node(_info);
	return p;
}

int rebuild(int l, int r, bool type)
{
	::type = type;
	nth_element(store + l, store + mid, store + r + 1);
	int p = newnode(store[mid]);
	if (l < mid) ls(p) = rebuild(l, mid - 1, type ^ 1);
	if (mid < r) rs(p) = rebuild(mid + 1, r, type ^ 1);
	return pushup(p);
}
void pia(int p)
{
	if (ls(p)) pia(ls(p));
	store[++cur] = t[p].info;
	mem[++top] = p;
	if (rs(p)) pia(rs(p));
}
void check(int &p, bool type)
{
	if (t[p].s * alpha + 1 < max(t[ls(p)].s, t[rs(p)].s))
	{
		cur = 0;
		pia(p);
		p = rebuild(1, cur, type);
	}
}
int root;
void insert(int &p, point _info, bool type)
{
	::type = type;
	if (!p) return p = newnode(_info), void();
	if (t[p].info.x == _info.x && t[p].info.y == _info.y)
	{
		t[p].info.v += _info.v;
		t[p].sum += _info.v;
		return pushup(p), void();
	}
	if (_info < t[p].info) insert(ls(p), _info, type ^ 1);
	else insert(rs(p), _info, type ^ 1);
	pushup(p);
	if (p != root) check(p, type);
}
inline bool inside(int x1, int y1, int x2, int y2, int X1,int Y1,int X2,int Y2)
{
	return x1 <= X1 && X2 <= x2 && y1 <= Y1 && Y2 <= y2;
}

inline bool outside(int x1, int y1, int x2, int y2, int X1, int Y1, int X2, int Y2)
{
	return x1 > X2 || x2 < X1 || y1 > Y2 || y2 < Y1;
}

int query(int p, int x1, int y1, int x2, int y2)
{
	if (!p) return 0;
	if (inside(x1, y1, x2, y2, t[p].lx, t[p].ly, t[p].rx, t[p].ry)) return t[p].sum;
	if (outside(x1, y1, x2, y2, t[p].lx, t[p].ly, t[p].rx, t[p].ry)) return 0;

	long long res(0);
	if (inside(x1, y1, x2, y2, t[p].info.x, t[p].info.y, t[p].info.x, t[p].info.y))
		res += t[p].info.v;
	return res + query(ls(p), x1, y1, x2, y2) + query(rs(p), x1, y1, x2, y2);
}

int main()
{
#ifdef CraZYali
	file("4390");
#endif
	init();
	read<int>();
	n = read<int>();
	while (1)
	{
		int opt(read<int>());
		if (opt == 3) return 0;
		else if (opt == 1)
		{
			point qaq;
			qaq.x = read<int>();
			qaq.y = read<int>();
			qaq.v = read<int>();
			insert(root, qaq, 0);
		}
		else
		{
			int x1(read<int>()), y1(read<int>()), x2(read<int>()), y2(read<int>());
			printf("%lld\n", query(root, x1, y1, x2, y2));
		}
	}
	return 0;
}
