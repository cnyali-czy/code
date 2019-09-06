#define DREP(i, s, e) for(int i(s), end_##i(e); i >= end_##i ;i--)
#define  REP(i, s, e) for(int i(s), end_##i(e); i <= end_##i ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <tr1/unordered_map>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>

using namespace std;
const int maxn = 1e3 + 10, maxq = 5e5 + 10, maxN = maxn << 1;

template <typename T> inline T read()
{
	T ans(0), p(1);
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}

int n, m, q, a[maxn], b[maxn];

tr1::unordered_map <int, int> ch[maxN];
int cur, start, last, id[maxN], Max[maxN], ne[maxN], beg[maxN];
inline int newnode(int _Max, int _beg = 0, int _id = 0)
{
	ch[++cur].clear();
	Max[cur] = _Max;
	beg[cur] = _beg;
	id[cur] = _id;
	return cur;
}
inline void extend(int c, int _id)
{
	int v(last), u(newnode(Max[v] + 1, _id, _id));
	for (; v && ch[v].find(c) == ch[v].end(); v = ne[v]) ch[v][c] = u;
	if (!v) ne[u] = start;
	else if (Max[v] + 1 == Max[ch[v][c]]) ne[u] = ch[v][c];
	else
	{
		int Old(ch[v][c]), New(newnode(Max[v] + 1, _id));
		ch[New] = ch[Old];
		ne[New] = ne[Old];
		ne[u] = ne[Old] = New;
		for (; v && ch[v][c] == Old;v = ne[v]) ch[v][c] = New;
	}
	last = u;
}

int sa[maxn], dfn;

int bg[maxN], nex[maxN], to[maxN], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	nex[e] = bg[x];
	bg[x] = e;
}

vector <pair <int, int> > v[maxN];

inline void init()
{
	e = 0;
	ch[start = last = cur = 1].clear();
	dfn = 0;
}
void dfs(int x)
{
	if (id[x]) sa[++dfn] = id[x];
	for (int i = bg[x]; i ; i = nex[i]) dfs(to[i]);
	bg[x] = 0;
}

inline void build_tree()
{
	REP(i, 1, cur)
		v[ne[i]].push_back(make_pair(-b[beg[i] + Max[ne[i]]], i));
	REP(i, 1, cur)
		if (!v[i].empty())
		{
			sort(v[i].begin(), v[i].end());
			REP(j, 0, v[i].size() - 1)
				add(i, v[i][j].second);
			v[i].clear();
		}
}

inline void get_sa()
{
	init();
	DREP(i, n, 1) extend(b[i], i);
	build_tree();
	dfs(start);
}

int hh[maxn];

int ans[maxq];
pair <pair <int, int>, int> que[maxq];
bool cmp(pair <pair <int, int>, int> A, pair<pair <int, int>, int> B) {return A.first.first > B.first.first;}

int main()
{
#ifdef CraZYali
	freopen("C.in", "r", stdin);
	freopen("C.out", "w", stdout);
#endif
	cin >> n >> m >> q;
	const int mod = m;
	REP(i, 1, n) hh[i] = a[i] = read<int>();
	sort(hh + 1, hh + 1 + n);hh[0] = unique(hh + 1, hh + 1 + n) - hh - 1;
	REP(i, 1, q)
	{
		int d(read<int>()), k(read<int>());
		que[i] = make_pair(make_pair(d, k), i);
	}
	sort(que + 1, que + 1 + q);//, cmp);
	REP(i, 1, n) b[i] = a[i];
	get_sa();
	int last = hh[0];
	REP(i, 1, q)
	{
		int d(que[i].first.first), k(que[i].first.second), pos(que[i].second);
		bool flag = 0;
		while (hh[last] + d >= mod)
		{
			last--;
			flag = 1;
		}
		if (flag)
		{
			REP(j, 1, n) b[j] = (a[j] + d) % mod;
			get_sa();
		}
		ans[pos] = sa[k];
//		REP(i, 1, n) printf("%d%c", sa[i], i == n ? '\n' : ' ');
	}
	REP(i, 1, q) printf("%d\n", ans[i]);
	return 0;
}
