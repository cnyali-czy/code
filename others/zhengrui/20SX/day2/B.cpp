/*
	Problem:	B.cpp
	Time:		2020-02-18 09:35
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
#define i64 long long
#define y1 hhakioi
using namespace std;
const int maxn = 1e5 + 10, MOD = 998244353;

inline int add(int x, int y) {register int res = x + y;return res >= MOD ? res - MOD : res;}
inline int sub(int x, int y) {register int res = x - y;return res <    0 ? res + MOD : res;}
inline int mul(i64 x, int y) {register i64 res = x * y;return res >= MOD ? res % MOD : res;}
inline void inc(int &x, int y) {x += y;if (x >= MOD) x -= MOD;}
inline void dec(int &x, int y) {x -= y;if (x <    0) x += MOD;}

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

int n, x1[maxn], y1[maxn], x2[maxn], y2[maxn], dp[maxn], ans;

int B[maxn << 1], N, By[maxn << 1], Ny;

struct Bit
{
	int N, c[maxn << 2];
	void init(int n)
	{
		N = n + 1;
		REP(i, 0, N) c[i] = 0;
	}
	void Add(int x, int y)
	{
		x++;
		while (x <= N)
		{
			inc(c[x], y);
			x += x & -x;
		}
	}
	int Sum(int x)
	{
		x++;
		int res = 0;
		while (x > 0)
		{
			inc(res, c[x]);
			x &= (x - 1);
		}
		return res;
	}
}one, ay, bx, ab;

struct opt
{
	int t, x, y, v;
	//t = 1 : add val
	//t = 2 : qry val, here v = id
	opt(int t = 0, int x = 0, int y = 0, int v = 0) : t(t), x(x), y(y), v(v) {}
	inline bool operator < (const opt& B) const {return y < B.y || y == B.y && t < B.t;}
}stk[maxn << 3];
int Q;

void cdq(int l, int r)
{
	if (l == r)
	{
		inc(ans, ++dp[l]);
		return;
	}
	int mid = l + r >> 1;
	cdq(l, mid);
	Q = N = 0;
	REP(i, l, mid)
	{
		B[++N] = x1[i];B[++N] = x2[i] + 1;

		stk[++Q] = opt(1, x1[i], y1[i], dp[i]);
		stk[++Q] = opt(1, x2[i] + 1, y1[i], MOD - dp[i]);
		stk[++Q] = opt(1, x1[i], y2[i] + 1, MOD - dp[i]);
		stk[++Q] = opt(1, x2[i] + 1, y2[i] + 1, dp[i]);
	}
	REP(i, mid + 1, r)
	{
		B[++N] = x1[i] - 1;B[++N] = x2[i];

		stk[++Q] = opt(2, x2[i], y2[i], i);
		stk[++Q] = opt(2, x1[i] - 1, y2[i], -i);
		stk[++Q] = opt(2, x2[i], y1[i] - 1, -i);
		stk[++Q] = opt(2, x1[i] - 1, y1[i] - 1, i);
	}
	sort(B + 1, B + 1 + N);N = unique(B + 1, B + 1 + N) - B - 1;
	sort(stk + 1, stk + 1 + Q);
	one.init(N);ay.init(N);bx.init(N);ab.init(N);
	REP(i, 1, Q)
		if (stk[i].t == 1)
		{
			int a = lower_bound(B + 1, B + 1 + N, stk[i].x) - B, v = stk[i].v;
			one.Add(a, v);ay.Add(a, mul(stk[i].x, v));bx.Add(a, mul(stk[i].y, v));ab.Add(a, mul(v, mul(stk[i].x, stk[i].y)));
		}
		else
		{
			int x = lower_bound(B + 1, B + 1 + N, stk[i].x) - B, id = stk[i].v;
			//			int x = stk[i].x, id = stk[i].v;
			int One = one.Sum(x), A = ay.Sum(x), B = bx.Sum(x), AB = ab.Sum(x);
			int delta = 0;
			inc(delta, mul(One, mul(stk[i].x + 1, stk[i].y + 1)));
			dec(delta, mul(A, stk[i].y + 1));
			dec(delta, mul(B, stk[i].x + 1));
			inc(delta, AB);
			//			printf("(%d %d %d) :  %d %d %d %d %d\n", stk[i].x, stk[i].y, stk[i].v, One, A, B, AB, delta);
			if (id > 0) inc(dp[id], delta);
			else dec(dp[-id], delta);
		}
	cdq(mid + 1, r);
}

signed main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read<int>();
	REP(i, 1, n) x1[i] = read<int>(), y1[i] = read<int>(), x2[i] = read<int>(), y2[i] = read<int>();
	cdq(1, n);
	//	REP(i, 1, n) printf("%d%c", dp[i], i == n ? '\n': ' ');
	cout << ans << endl;
	return 0;
}
