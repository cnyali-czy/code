/*
	Problem:	3827.cpp
	Time:		2020-08-10 23:16
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
#define int long long
using namespace std;
const int maxn = 1e5 + 10;

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

struct Vector
{
	int x, y;
	Vector() {}
	Vector(int x, int y) : x(x), y(y) {}
	inline Vector operator + (Vector B) {return Vector(x + B.x, y + B.y);}
	inline Vector operator - (Vector B) {return Vector(x - B.x, y - B.y);}
	inline int operator * (Vector B) {return x * B.y - y * B.x;}
}p[maxn], stk[maxn];
int n, m, top, N, id[maxn], pick;
bool del[maxn];
inline int sqr(int x) {return x * x;}
inline bool cmp(int x, int y)
{
	int qaq = (p[x] - p[pick]) * (p[y] - p[pick]);
	if (qaq < 0) return 0;
	if (qaq > 0) return 1;
	return	sqr(p[x].x - p[pick].x) + sqr(p[x].y - p[pick].y) >
			sqr(p[y].x - p[pick].x) + sqr(p[y].y - p[pick].y);
}

signed main()
{
#ifdef CraZYali
	file("3827");
#endif
	n = read<int>();m = read<int>();
	REP(i, 1, n) p[i].x = read<int>(), p[i].y = read<int>();
	int S = -1;
	while (m--)
	{
		int k = read<int>();
		REP(i, 1, n) del[i] = 0;
		REP(i, 1, k) del[(S + read<int>()) % n + 1] = 1;
		pick = 0;
		REP(i, 1, n) if (!del[i])
			if (!pick || p[i].x < p[pick].x || p[i].x == p[pick].x && p[i].y < p[pick].y) pick = i;
		id[N = 1] = pick;
		REP(i, 1, n) if (!del[i] && i != pick) id[++N] = i;
		sort(id + 2, id + 1 + N, cmp);
		stk[top = 1] = p[pick];
		REP(i, 2, N)
		{
			while (top > 1 && (stk[top] - stk[top - 1]) * (p[id[i]] - stk[top]) < 0) top--;
			stk[++top] = p[id[i]];
		}
		S = 0;
		REP(i, 3, top) S += (stk[i - 1] - stk[1]) * (stk[i] - stk[1]);
		if (S < 0) S = -S;
		printf("%lld\n", S);
	}
	return 0;
}
