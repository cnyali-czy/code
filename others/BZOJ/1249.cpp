/*
	Problem:	1249.cpp
	Time:		2020-03-28 14:47
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cmath>
#include <set>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e5 + 10;
const double eps = 1e-8;
#define i64 long long
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

namespace run
{
#define si set <point> :: iterator
	struct point
	{
		int x, y;
		inline point() {}
		inline point(int x, int y) : x(x), y(y) {}
		inline point operator - (const point &B) const {return point(x - B.x, y - B.y);}
		inline i64 operator * (const point &B) const {return (i64)x * B.y - (i64)y * B.x;}
		inline i64 operator ^ (const point &B) const {return (i64)x * B.x + (i64)y * B.y;}
	}a[4], x, st[maxn], A;
	inline i64 cross(point a, point b, point c) {return (b - a) * (c - a);}
	inline i64 cross(point a, point b) {return a * b;}
	inline i64 dis2(point a) {return (a - A) ^ (a - A);}
	inline bool operator < (const point &a, const point &b) 
	{
		double d1 = atan2(a.y - A.y, a.x - A.x), d2 = atan2(b.y - A.y, b.x - A.x);
		if (abs(d1 - d2) > eps) return d1 < d2;
		else return dis2(a) < dis2(b);
	}
	int n, top;
	i64 ans;

	set <point> s;
	si it, jt;
	inline si pre(si x) {return x == s.begin() ? --s.end() : --x;}
	inline si suf(si x) {return x == --s.end() ? s.begin() : ++x;}

	void insert(point x)
	{
		jt = s.lower_bound(x);
		if (jt == s.end()) jt = s.begin();
		it = pre(jt);
		if (cross(*it, x, *jt) <= 0) return;
		ans += cross(*it, x) + cross(x, *jt) - cross(*it, *jt);
		while (1)
		{
			jt = suf(it = jt);
			if (cross(x, *it, *jt) > 0) break;
			st[++top] = *it;
			ans -= cross(x, *it) + cross(*it, *jt) - cross(x, *jt);
		}
		it = pre(s.lower_bound(x));
		while(1)
		{
			it = pre(jt = it);
			if (cross(*it, *jt, x) > 0) break;
			st[++top] = *jt;
			ans -= cross(*it, *jt) + cross(*jt, x) - cross(*it, x);
		}
		while (top) s.erase(st[top--]);
		s.emplace(x);
	}
	int main()
	{
		REP(i, 1, 3)
		{
			a[i].x = read<int>();
			a[i].y = read<int>();
			A.x += a[i].x;A.y += a[i].y;
		}
		A.x /= 3;A.y /= 3;
		REP(i, 1, 3)
		{
			s.insert(a[i]);
			ans += a[i] * a[i % 3 + 1];
		}
		ans = abs(ans);
		n = read<int>();
		REP(i, 1, n)
		{
			int x = read<int>(), y = read<int>();
			insert(point(x, y));
			cout << ans << '\n';
		}
		return 0;
	}
}

int main()
{
#ifdef CraZYali
	file("1249");
#endif
	return run::main();
}
