/*
 * File Name:	B.cpp
 * Author	:	CraZYali
 * Year		:	2019.10.26 14:04
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 3e5 + 10;

template <typename T> inline T read()
{ T ans(0), flag(1);
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

pair <long long, long long> p[maxn]; 
long long line, ans;
struct node
{
	long long x, l, r;
	inline bool operator < (const node &B) const {return l < B.l || l == B.l && r < B.r;}
}a[maxn << 3];
int n, N;
inline void _unique()
{
	sort(a + 1, a + 1 + N);
	int _n = 1;
	REP(i, 2, N)
		if (a[i].l <= a[_n].r + 1) chkmax(a[_n].r, a[i].r);
		else a[++_n] = a[i];
	N = _n;
}

inline void pushup()
{
	int _n = 0;
	REP(i, 1, N)
		if ((++a[i].l) <= (--a[i].r)) a[++_n] = a[i];
	N = _n;
}

int main()
{
#ifdef CraZYali
	file("B");
#endif
	cin >> n;
	REP(i, 1, n)
	{
		register int l(read<int>()), r(read<int>());
		p[i] = make_pair(l, r);
	}
	sort(p + 1, p + 1 + n);
	for (int cur = 1;;pushup(), line++)
	{
		if (!N)
		{
			if (cur > n) break;
			line = p[cur].first;
		}
		for (;cur <= n && p[cur].first == line; cur++) a[++N] = node{p[cur].first, p[cur].second, p[cur].second + 1};
		_unique();
		REP(i, 1, N) ans += (a[i].r - a[i].l + 1 >> 1);
	}
	cout << ans << endl;
	return 0;
}
