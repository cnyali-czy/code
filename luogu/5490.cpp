#define REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>
#define i64 long long
using namespace std;
const int maxn = 1e5 + 10, maxN = (maxn * 3) << 2;

template <typename T> T read()
{
	T ans(0), flag(1);
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

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

int m, n, k, N;

struct Seg
{
	int x, l, r, flag;
	inline bool operator < (const Seg &B) const {return x < B.x;}
}S[maxn * 2];

int s[maxN];
i64 len[maxN];
#define ls p << 1
#define rs p << 1 | 1
#define lson ls, l, mid
#define rson rs, mid + 1, r
#define mid (l + r >> 1)
int mem[maxn * 3];

void pushup(int p, int l, int r)
{
	if (s[p]) len[p] = mem[r] - mem[l - 1];
	else len[p] = (l == r ? 0 : len[ls] + len[rs]);
}

void update(int p, int l, int r, int L, int R, int val)
{
	if (L <= l && r <= R)
		s[p] += val;
	else
	{
		if (L <= mid) update(lson, L, R, val);
		if (R >  mid) update(rson, L, R, val);
	}
	pushup(p, l, r);
}

int main()
{
#ifdef CraZYali
	file("5490");
#endif
	n = read<int>();
	REP(i, 1, n)
	{
		i64 x1(read<i64>()), y1(read<i64>()), x2(read<i64>()), y2(read<i64>());
		S[i] = (Seg){x1, y1, y2 - 1, 1};
		S[i + n] = (Seg){x2, y1, y2 - 1, -1};
		mem[++N] = y1;mem[++N] = y2 - 1;
		mem[++N] = y1 - 1;
	}
	sort(mem + 1, mem + 1 + N);
	N = unique(mem + 1, mem + 1 + N) - mem - 1;
	REP(i, 1, n + n)
	{
		S[i].l = lower_bound(mem + 1, mem + 1 + N, S[i].l) - mem;
		S[i].r = lower_bound(mem + 1, mem + 1 + N, S[i].r) - mem;
	}
	sort(S + 1, S + 1 + n + n);
	i64 ans = 0;
	REP(i, 1, n + n)
	{
		ans += (S[i].x - S[i - 1].x) * len[1];
		update(1, 1, N, S[i].l, S[i].r, S[i].flag);
	}
	cout << ans << endl;
	return 0;
}
