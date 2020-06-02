#define REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <stack>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;
const int maxn = 1e5 + 10;

int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}
#define getchar getchar_unlocked
int read()
{
	int ans(0);
	char c(getchar());
	while (!isdigit(c)) c = getchar();
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans;
}

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}
#define i64 long long
int n, q;

int rt, w[maxn];
i64 Ans[maxn];

int blg[maxn], block;
i64 sum[maxn];
void getsum(int x, int fa = 0)
{
	sum[x] = w[x];
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
	{
		getsum(to[i], x);
		sum[x] += sum[to[i]];
	}
}
bool need[maxn];

struct SHIT
{
	int l, r, v, id;
	SHIT(int l = 0, int r = 0, int v = 0, int id = 0) : l(l), r(r), v(v), id(id) {}
};
vector <SHIT> Qry[maxn];
namespace dog
{
	int blg[maxn], L[maxn], R[maxn], s[maxn], sp[maxn], ss[maxn], tot;
	void init()
	{
		const int block = sqrt(n);
		REP(i, 1, n) blg[i] = (i - 1) / block + 1;
		REP(i, 1, n) R[blg[i]] = i;
		DEP(i, n, 1) L[blg[i]] = i;
		tot = blg[n];
	}
	void add(int x, int y = 1)
	{
		int b = blg[x];
		REP(i, b, tot) s[i] += y;
		REP(i, L[b], x) ss[i] += y;
		REP(i, x, R[b]) sp[i] += y;
	}
	int sum(int l, int r)
	{
		int bl = blg[l], br = blg[r];
		if (bl == br) return sp[r] - (l == L[bl] ? 0 : sp[l - 1]);
		else return ss[l] + sp[r] + s[br - 1] - s[bl];
	}
}
void dfs(int x, int fa = 0)
{
	dog :: add(x);
	for (auto i : Qry[x])
		Ans[i.id] += 1ll * dog :: sum(i.l, i.r) * i.v;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
		dfs(to[i], x);
	dog :: add(x, -1);
}
int Top;
pair <int, int> tmp[maxn];

int main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read();q = read();
	dog::init();
	REP(i, 1, n) w[i] = read();
	REP(i, 1, n)
	{
		int x(read()), y(read());
		if (!x) rt = y;
		else add(x, y), add(y, x);
	}
	block = 2 * sqrt(n);
//	cerr<<block<<endl;
	REP(i, 1, q)
	{
		blg[i] = (i - 1) / block + 1;
		if (blg[i] ^ blg[i - 1])
		{
			Top = 0;
			getsum(rt);
			REP(j, 2, n) sum[j] += sum[j - 1];
		}
		int opt = read(), l = read(), r = read();
		if (opt == 1)
		{
			r -= w[l];
			w[l] += r;
			tmp[++Top] = make_pair(l, r);
		}
		else
		{
			need[i] = 1;
			Ans[i] = sum[r] - sum[l - 1];
			REP(k, 1, Top) Qry[tmp[k].first].emplace_back(l, r, tmp[k].second, i);
		}
	}
	dfs(rt);
	REP(i, 1, q) if (need[i]) printf("%lld\n", Ans[i]);
	return 0;
}
