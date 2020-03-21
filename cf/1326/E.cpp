/*
	Problem:	E.cpp
	Time:		2020-03-20 10:04
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
const int maxn = 3e5 + 10, inf = 1e9;

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
struct mat
{
	int a[2][2];
	int *operator [] (int x) {return a[x];}
	void clear() {a[0][0] = a[0][1] = a[1][0] = a[1][1] = -inf;}
	inline mat operator * (mat b)
	{
		mat c;
		c[0][0]=max(a[0][0]+b[0][0],a[0][1]+b[1][0]);
		c[0][1]=max(a[0][0]+b[0][1],a[0][1]+b[1][1]);
		c[1][0]=max(a[1][0]+b[0][0],a[1][1]+b[1][0]);
		c[1][1]=max(a[1][0]+b[0][1],a[1][1]+b[1][1]);
//		mat c;c.clear();
//		REP(i, 0, 1) REP(j, 0, 1) REP(k, 0, 1) chkmax(c[i][j], a[i][k] + b[k][j]);
		return c;
	}
};
mat b;
#define mid (l + r >> 1)
struct smt
{
	mat s;
	smt *ls, *rs;
	int l, r;
	smt(int l, int r) : l(l), r(r)
	{
		if (l == r)
		{
			ls = rs = NULL;
			s[0][0] = s[0][1] = s[1][1] = 0;
			s[1][0] = -inf;
		}
		else
		{
			ls = new smt(l, mid);
			rs = new smt(mid + 1, r);
			s = rs -> s * ls -> s;
		}
	}
	void upd(int x, int y)
	{
		if (l == r) return void(s[0][0] = y);
		if (x <= mid) ls -> upd(x, y);
		else rs -> upd(x, y);
		s = rs -> s * ls -> s;
	}
};
smt *rt;
int n, p[maxn], q[maxn], pos[maxn];

signed main()
{
#ifdef CraZYali
	file("E");
#endif
	n = read<int>();
	rt = new smt(1, n + n);
	REP(i, 1, n) pos[p[i] = read<int>()] = i;
	REP(i, 1, n) q[i] = read<int>();
	int ans = n + 1;
	REP(i, 1, n)
	{
		while (!((rt -> s * b)[0][0]))
		{
			ans--;
			rt->upd((pos[ans] << 1) - 1, 1);
		}
		cout << ans << ' ' ;
		rt -> upd(q[i] << 1, -1);
	}
	return 0;
}
