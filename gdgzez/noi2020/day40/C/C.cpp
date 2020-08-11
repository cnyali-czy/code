/*
	Problem:	C.cpp
	Time:		2020-08-11 11:21
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

int n, q;

struct Vector
{
	int x, y;
	Vector() {}
	Vector(int x, int y) : x(x), y(y) {}
	inline Vector operator + (Vector B) {return Vector(x + B.x, y + B.y);}
	inline Vector operator - (Vector B) {return Vector(x - B.x, y - B.y);}
	inline int operator * (Vector B) {return x * B.y - y * B.x;}
}p[maxn];

signed main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>(), q = read<int>();
	REP(i, 1, n) p[i].x = read<int>(), p[i].y = read<int>();
	while (q--)
	{
		p[0].x = read<int>(), p[0].y = read<int>();
		int ans = -1e18, res = 0;
		REP(i, 1, n)
		{
			res += p[0] * p[i];
			if (ans < res) ans = res;
			if (res < 0) res = 0;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
