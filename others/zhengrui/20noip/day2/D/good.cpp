#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <cassert>
#include <algorithm>
#include <iostream>
#include <cstdio>
#define int long long
using namespace std;
const int maxn = 5000 + 10;
const int inf = 1e15;

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

inline bool chkmax(int &x, int y)
{
	if (x < y)
	{
		x = y;
		return 1;
	}
	return 0;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, a[maxn], s[maxn];
int dp[maxn][maxn], g[maxn], f[maxn];
int sum(int l, int r) {return s[r] - s[l - 1];}

struct Vector
{
	int x, y;
	Vector(int x = 0, int y = 0) : x(x), y(y) {}
	inline Vector operator - (Vector B) {return Vector(x - B.x, y - B.y);}
	inline int operator * (Vector B) {return x * B.y - y * B.x;}
	inline int dis2() {return x * x;}
	inline bool operator == (const Vector &B) const {return x == B.x && y == B.y;}
};
Vector stk[maxn], p[maxn];
int top, N;

inline bool cmp_vec(Vector x, Vector y)//顺时针
{
	x = x - p[1], y = y - p[1];
	auto res = x * y;
	if (res < 0) return 1;
	if (res > 0) return 0;
	return x.dis2() < y.dis2();
}
inline bool cmp_pos(int x, int y) {return s[x] > s[y];}
int M;
void maintain(int i, int j)
{
	int sj = stk[j].x, gj = stk[j].y - M * sj;
	chkmax(f[i], gj + (M - sj) * (s[i] - M));
}
void solve(int m)
{
	REP(i, m, n) f[i] = -inf;
	M = s[m - 1];
	REP(j, 1, m - 1)
	{
		p[j] = Vector(s[j - 1], g[j] + M * s[j - 1]);
		if (make_pair(p[j].x, p[j].y) < make_pair(p[1].x, p[1].y)) swap(p[1], p[j]);
	}
	sort(p + 2, p + m, cmp_vec);
	stk[top = 1] = p[1];
	REP(i, 2, m - 1)
	{
		while (top > 1 && (p[i] - stk[top]) * (stk[top] - stk[top - 1]) < 0) top--;
		if (p[i].x <= stk[top].x) continue;
		stk[++top] = p[i];
	}
	top = unique(stk + 1, stk + 1 + top) - stk - 1;
	static int todo[maxn];
	REP(i, m, n) todo[i - m + 1] = i;
	sort(todo + 1, todo + 1 + (n - m + 1), cmp_pos);
	/*
	   REP(j, 1, m - 1)
	   REP(i, m, n)
	   chkmax(f[i], g[j] + sum(j, m - 1) * sum(m, i));
	   */
	int j = 1;
	REP(I, 1, n - m + 1)
	{
		int i = todo[I];
		while (j < top && (stk[j + 1].y - stk[j].y) > s[i] * (stk[j + 1].x - stk[j].x))
			maintain(i, j++);
		maintain(i, j);
		//		REP(j, 1, top)
		//		{
		//		}
	}
}

signed main()
{
#ifdef CraZYali
	file("D");
#endif
	n = read<int>();
	REP(i, 1, n) s[i] = s[i - 1] + (a[i] = read<int>());
	int ans = 0;
	REP(i, 2, n)
	{
		REP(j, 1, i - 1) g[j] = dp[j][i - 1];
		solve(i);
		REP(j, i, n) dp[i][j] = f[j];
		chkmax(ans, f[n]);
	}
	cout << ans << endl;
	return 0;
}
