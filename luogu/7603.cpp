#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <ext/pb_ds/priority_queue.hpp>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>
#define int long long

using namespace std;
const int maxn = 1e5 + 10;

inline int read() {int x;scanf("%lld", &x);return x;}

int n, q;
vector <int> p[maxn];

int m, h[maxn], a[maxn], b[maxn], c[maxn];
vector <int> ans;

int lstans;
inline void output()
{
	sort(ans.begin(), ans.end());
	cout << (lstans = ans.size());
	for (auto i : ans) cout << ' ' << i;
	puts("");
	ans.clear();
}
//__gnu_pbds :: tree <pair <int, int>, __gnu_pbds :: null_type > s[maxn];
struct pii
{
	int fi, se;
	inline bool operator < (const pii &B) const {return fi > B.fi;}
};
__gnu_pbds :: priority_queue <pii> s[maxn];
__gnu_pbds :: priority_queue <pii> :: point_iterator it[maxn][6];

int cnt[maxn], tot, mx;
void ins(int id)
{
	tot++;
	mx = max(mx, ++cnt[id]);
	int x = a[id], y = b[id], z = 0;
	for (int d : p[x]) y -= h[d];
	z = 0;
	if (y > 0)
	{
		int lim = (y + c[id] - 1) / c[id];
		for (int d : p[x])
			s[d].modify(it[id][z++], {lim + h[d], id});
	}
	else
	{
		for (int d : p[x]) s[d].erase(it[id][z++]);
		ans.emplace_back(id);
	}
}
void modify(int x, int y)
{
	h[x] += y;
	while (s[x].size() && h[x] >= s[x].top().fi)
		ins(s[x].top().se);
}
signed main()
{
#ifdef CraZYali
	freopen("7603.in", "r", stdin);
	freopen("7603.out", "w", stdout);
#endif
	n = read();q = read();
	REP(i, 2, n) if (!p[i].size()) REP(j, 1, n / i) p[i * j].emplace_back(i);
	REP(Case, 1, q)
	{
		int opt = read(), x = read(), y = read() ^ lstans;
		if (opt == 1)
		{
			++m;
			if (!y) ans.emplace_back(m);
			else
			{
				a[m] = x;
				b[m] = y;
				c[m] = p[x].size();
				int z = 0;
				for (int d : p[x]) b[m] += h[d], it[m][z++] = s[d].push({0, m});
				ins(m);
			}
		}
		else
		{
			for (int d : p[x]) modify(d, y);
			output();
		}
	}
	return 0;
}
