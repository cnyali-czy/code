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
#include <map>
using namespace std;
const int maxn = 2e5 + 10;

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

int q, n, k, N;
int blg[maxn], R[maxn], block;

struct Query
{
	int l, r, id;
	Query(){}
	Query(int l, int r, int id) : l(l), r(r), id(id) {}
	inline bool operator < (const Query &B) const {return r < B.r;}
};
vector <Query> v[maxn];
int lmost[maxn], rmost[maxn], ans[maxn], res, a[maxn], b[maxn];
void bf(int l, int r, int id)
{
	static int lmost[maxn];
	DEP(i, r, l) lmost[a[i]] = i;
	int ans = 0;
	REP(i, l, r) chkmax(ans, i - lmost[a[i]]);
	::ans[id] = ans;
}
int Lower_Bound(int x)
{
	int l = 1, r = N;
	while (l <= r)
	{
		int mid = l + r >> 1;
		if (b[mid] == x) return mid;
		else if (b[mid] > x) r = mid - 1;
		else l = mid + 1;
	}
}
int main()
{
#ifdef CraZYali
	file("5906");
#endif
	n = read<int>();
	REP(i, 1, n) a[i] = b[i] = read<int>();
	sort(b + 1, b + 1 + n);N = unique(b + 1, b + 1 + n) - b - 1;
	REP(i, 1, n) a[i] = Lower_Bound(a[i]);
	q = read<int>();
	block = max(5., n / sqrt(q));
	REP(i, 1, n) R[blg[i] = (i - 1) / block + 1] = i;
	int tot = blg[n];
	REP(i, 1, q)
	{
		int l(read<int>()), r(read<int>());
		if (r - l + 1 <= block) bf(l, r, i);
		else v[blg[l]].emplace_back(l, r, i);
	}
	REP(i, 1, tot) if (v[i].size())
	{
		sort(v[i].begin(), v[i].end());
		int r = R[i];
		res = 0;
		for (auto j : v[i])
		{
			while (r < j.r)
			{
				r++;
				if (!rmost[a[r]]) lmost[a[r]] = r;
				rmost[a[r]] = r;
				chkmax(res, r - lmost[a[r]]);
			}
			ans[j.id] = res;
			REP(k, j.l, R[i]) chkmax(ans[j.id], rmost[a[k]] - k);
			if (ans[j.id] < R[i] - j.l + 1)
			{
				bf(j.l, R[i], 0);
				chkmax(ans[j.id], ans[0]);
			}
		}
		REP(j, R[i], r) rmost[a[j]] = 0;
	}
	REP(i, 1, q) cout << ans[i] << '\n';
	return 0;
}
