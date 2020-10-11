/*
	Problem:	G.cpp
	Time:		2020-10-11 16:17
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
#include <set>
#include <bitset>

using namespace std;
const int maxn = 2000 + 10;

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

#define BIT bitset <maxn>

int n, m, q, cnt[maxn];
BIT b[maxn], all;

struct cmp
{
	inline bool operator () (int x, int y)
	{
		return make_pair(cnt[x], x) < make_pair(cnt[y], y);
	}
};
set <int, cmp> S;
struct zzz
{
	int fir, sec;
	zzz(int x = 0, int y = 0)
	{
		if (x > y) swap(x, y);
		fir = x;sec = y;
	}
	inline bool operator < (const zzz &B) const {return make_pair(fir, sec) < make_pair(B.fir, B.sec);}
};
set <zzz> P;
int cur;

bool ok(int x, int y) {return (b[x] & b[y]) != b[x];}

void ins(int x)
{
	auto it = S.emplace(x).first, itl = it, itr = it;
	itl--;itr++;
	if (cnt[*itl])
	{
		if (itr != S.end() && ok(*itl, *itr)) P.erase(zzz(*itl, *itr));
		if (ok(*itl, *it)) P.emplace(*itl, *it);
	}
	if (itr != S.end() && ok(*it, *itr)) P.emplace(*it, *itr);
}
void del(int x)
{
	auto it = S.find(x), itl = it, itr = it;
	itl--;itr++;
	if (itr != S.end() && ok(*it, *itr)) P.erase(zzz(*it, *itr));
	if (cnt[*itl])
	{
		if (ok(*itl, *it)) P.erase(zzz(*itl, *it));
		if (itr != S.end() && ok(*itl, *itr)) P.emplace(*itl, *itr);
	}
	S.erase(x);
}

BIT get(int l, int r)
{
	return (all >> (maxn - (r - l + 1))) << l;
}


int main()
{
#ifdef CraZYali
	file("G");
#endif
	all.set();
	n = read<int>();m = read<int>();q = read<int>();
	REP(i, 0, n) ins(i);
	while (q--)
	{
		int x = read<int>(), l = read<int>(), r = read<int>();
		del(x);
		b[x] ^= get(l, r);
		cnt[x] = b[x].count();
		ins(x);
		if (!P.size()) puts("-1");
		else
		{
			auto ans = *P.begin();
			int x1 = ans.fir, x2 = ans.sec;
			auto tmp = b[x1] ^ b[x2];
			int y1 = (tmp & b[x1])._Find_first();
			int y2 = (tmp & b[x2])._Find_first();
			if (x1 > x2) swap(x1, x2);
			if (y1 > y2) swap(y1, y2);
			printf("%d %d %d %d\n", x1, y1, x2, y2);
		}
	}
	return 0;
}
