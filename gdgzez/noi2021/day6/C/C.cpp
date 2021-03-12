/*
	Problem:	C.cpp
	Time:		2021-03-06 14:49
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
const int maxn = 2e5 + 10;

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
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, x[maxn], a[maxn], b[maxn];

namespace SMT
{
	int siz[maxn << 2], s[maxn << 2];
#define ls p << 1
#define rs p << 1 | 1
#define lson ls, l, mid
#define rson rs, mid + 1, r
#define mid (l + r >> 1)
	inline void pushup(int p)
	{
		siz[p] = siz[ls] ^ siz[rs];
		s[p] = s[rs] + (siz[rs] & 1 ? -1 : 1) * s[ls];
	}
	void ins(int p, int l, int r, int pos, int val)
	{
		if (l == r)
		{
			siz[p] = 1;
			s[p] = val;
		}
		else
		{
			if (pos <= mid) ins(lson, pos, val);
			else ins(rson, pos, val);
			pushup(p);
		}
	}
}
int s[maxn], pos[maxn];

signed main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();
	static pair <int, int> q[maxn];int N = 0;
	REP(i, 1, n)
	{
		x[i] = read<int>(), a[i] = read<int>(), b[i] = read<int>();
		x[i] %= (a[i] + b[i]);
		s[i] = s[i - 1];
		if (x[i] < a[i] && x[i] < b[i]) continue;
		else if (x[i] < a[i]) s[i] -= (x[i] / b[i]) * 2;
		else if (x[i] < b[i]) s[i] += (x[i] / a[i]) * 2;
		else
		{
			q[++N] = make_pair(a[i] < b[i] ? x[i] / a[i] + 1 : x[i] / b[i] + 1, i);
			s[i] += x[i] / a[i] - x[i] / b[i];
		}
	}
	sort(q + 1, q + 1 + N);
	REP(i, 1, N) pos[q[i].second] = i;
	REP(i, 1, n)
	{
		if (pos[i]) SMT :: ins(1, 1, N, pos[i], q[pos[i]].first);
		int ao = s[i] + SMT :: s[1], bo = s[i] - SMT :: s[1];
		if (ao > 0 && bo >= 0)		puts("Alice");
		else if (ao <= 0 && bo < 0)	puts("Bob");
		else if (ao >  0 && bo < 0) puts("First");
		else puts("Second");
	}
	return 0;
}
