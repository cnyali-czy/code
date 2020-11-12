#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 1e6 + 10;

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

int n, m, a[maxn], v[maxn];
vector <int> vec[maxn];

struct Opt
{
	int l, r, v;
	Opt() {}
	Opt(int l, int r, int v) : l(l), r(r), v(v) {}
};
vector <Opt> dog[maxn];
inline void add(int x1, int x2, int y1, int y2, int v)
{
	dog[x1].emplace_back(y1, y2, v);
	dog[x2 + 1].emplace_back(y1, y2, -v);
}
inline void work(int l, int mid, int r, int v)
{
	add(l + 1, mid, mid, r - 1, v);
}

namespace SMT
{
	i64 Max[maxn << 2], tag[maxn << 2];
#define lson ls, l, mid
#define rson rs, mid + 1, r
#define mid (l + r >> 1)
#define ls p << 1
#define rs p << 1 | 1
	void update(int p, int l, int r, int L, int R, int v)
	{
		if (L <= l && r <= R)
		{
			Max[p] += v;
			tag[p] += v;
		}
		else
		{
			if (L <= mid) update(lson, L, R, v);
			if (R >  mid) update(rson, L, R, v);
			Max[p] = max(Max[ls], Max[rs]) + tag[p];
		}
	}
}

int main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();m = read<int>();
	static int cnt[maxn];
	REP(i, 1, n)
	{
		a[i] = read<int>();
		cnt[a[i]]++;
	}
	REP(i, 1, m) v[i] = read<int>();
	
	REP(i, 1, m) vec[i].resize(cnt[i] + 2), cnt[i] = 0;
	REP(i, 1, n) vec[a[i]][++cnt[a[i]]] = i;
	REP(i, 1, m) vec[i][++cnt[i]] = n + 1;

	REP(c, 1, m)
		REP(i, 1, vec[c].size() - 2)
			work(vec[c][i - 1], vec[c][i], vec[c][i + 1], v[c]);

	i64 ans = 0;
	REP(i, 1, n)
	{
		for (auto j : dog[i])
			SMT :: update(1, 1, n, j.l, j.r, j.v);
		ans = max(ans, SMT :: Max[1]);
	}
	cout << ans << endl;
	return 0;
}
