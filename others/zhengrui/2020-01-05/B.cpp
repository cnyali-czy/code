/*
	Problem:	B.cpp
	Time:		2020-02-21 20:22
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 2e5 + 10;

inline int min(int x, int y) {return x < y ? x : y;}
inline int max(int x, int y) {return x > y ? x : y;}

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

struct node
{
	int l, r;
	node(int l = 0, int r = 0) : l(l), r(r) {}
	inline node operator + (const node &B) const {return node(min(l, B.l), max(r, B.r));}
}f[20][20][maxn];
int lg[maxn];
struct __init__
{
	__init__(const int n = maxn - 10)
	{
		REP(i, 2, n) lg[i] = lg[i >> 1] + 1;
	}
}__INIT__;

int n;
node A[maxn], B[maxn];

inline node query(int L, int l, int r)
{
	int k = lg[r - l + 1];
	return f[L][k][l] + f[L][k][r - (1 << k) + 1];
}
inline node query(int L, node B) {return query(L, B.l, B.r);}

void build(node f[20][maxn])
{
	REP(j, 1, 19)
		REP(i, 1, n - (1 << j) + 1) f[j][i] = f[j-1][i] + f[j-1][i + (1 << j-1)];
}

int pre[maxn];
bool check(int L)
{
	REP(i, 1, n) B[i] = query(L, A[i]);
	pre[0] = n;
	REP(i, 1, n) pre[i] = min(pre[i - 1], B[i].r);
	REP(i, 1, n) if (pre[B[i].l - 1] < i) return 1;
	return 0;
}

int main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read<int>();
	REP(i, 1, n)
	{
		int x = read<int>();
		f[0][0][i] = node(max(1, i - x), min(n, i + x));
		A[i] = node(i, i);
	}
	build(f[0]);
	REP(j, 1, 19)
	{
		REP(i, 1, n) f[j][0][i] = query(j - 1, f[j-1][0][i]);
		build(f[j]);
	}
	int ans = 0;
	DEP(i, 19, 0) if (check(i))
	{
		ans |= (1 << i);
		copy(B, B + 1 + n, A);
	}
	cout << ans + 1 << endl;
	return 0;
}
