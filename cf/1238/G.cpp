/*
	Problem:	G.cpp
	Time:		2020-03-15 21:11
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <map>
#include <algorithm>
#include <iostream>
#include <cstdio>
#define i64 long long
using namespace std;
const int maxn = 5e5 + 10;

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

struct person
{
	int t, a, b;
	person(int t = 0, int a = 0, int b = 0) : a(a), b(b), t(t) {}
	inline bool operator < (const person &B) const {return t < B.t;}
}p[maxn];
#define t(i) p[i].t
#define a(i) p[i].a
#define b(i) p[i].b

int n, m, c0, c;
map <int, int> cur;

int main()
{
#ifdef CraZYali
	file("G");
#endif
	register int T = read<int>();
	while (T--)
	{
		n = read<int>();m = read<int>();c = read<int>();c0 = read<int>();
		REP(i, 1, n) t(i) = read<int>(), a(i) = read<int>(), b(i) = read<int>();
		p[++n] = person(m, 0, 0);
		sort(p + 1, p + 1 + n);
		i64 ans = 0;
		cur.clear();cur[0] = c0;
		REP(i, 1, n)
		{
			int delta = t(i) - t(i - 1);
			if (delta > c) {ans = -1;break;}
			while (!cur.empty() && delta)
			{
				int ccc = min(delta, cur.begin() -> second);
				ans += 1ll * ccc * cur.begin() -> first;
				delta -= ccc;
				c0 -= ccc;
				cur.begin() -> second -= ccc;
				if (!cur.begin() -> second) cur.erase(cur.begin());
			}
			if (delta) {ans = -1;break;}
			int Cnt(a(i)), Cost(b(i)), ccc(min(c - c0, Cnt));
			c0 += ccc;
			while (!cur.empty() && ccc < Cnt && Cost < cur.rbegin() -> first)
				if (Cnt - ccc >= cur.rbegin() -> second)
				{
					ccc += cur.rbegin() -> second;
					cur.erase(--cur.end());
				}
				else
				{
					cur.rbegin() -> second -= Cnt - ccc;
					ccc = Cnt;
				}
			cur[Cost] += ccc;
		}
		cout << ans << '\n';
	}
	return 0;
}
