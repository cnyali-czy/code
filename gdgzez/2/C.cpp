#define DREP(i, s, e) for(int i(s), end_##i(e); i >= end_##i ;i--)
#define  REP(i, s, e) for(int i(s), end_##i(e); i <= end_##i ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <map>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;
const int maxn = 2e5 + 10, maxq = 5e5 + 10;

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

int n, m, q, a[maxn];

map <int, int> ch[maxn];
int cur, start, last, id[maxn], Max[maxn], ne[maxn];
bool ok[maxn];
inline int newnode(int _Max, int _id)
{
	ch[++cur].clear();
	Max[cur] = _Max;
	id[cur] = _id;
	return cur;
}
inline void extend(int c, int _id)
{
	int v(last), u(newnode(Max[v] + 1, _id));
	ok[u] = 1;
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
vector <int> v[maxn];

inline void init() {start = last = cur = 1;}
int siz[maxn];
void dfs(int x)
{
	siz[x] = 1;
	sa[++dfn] = x;
	for (int i : v[x])
	{
		dfs(i);
		siz[x] += siz[i];
	}
}

int ans[maxq];
pair <pair <int, int>, int> que[maxq];

namespace fhq
{
	int fa[maxn], ch[maxn][2], s[maxn], v[maxn], order[maxn], root;
#define ls(p) ch[p][0]
#define rs(p) ch[p][1]
	inline int pushup(int x)
	{
		s[x] = s[ls(x)] + s[rs(x)] + 1;
		v[x] = v[ls(x)] + v[rs(x)] + ok[x];
		return x;
	}
	/*
	pair <int, int> split(int x, int siz)
	{
		if (!x || !siz)		return make_pair(0, x);
		if (siz == s[x])	return make_pair(x, 0);
		pair <int, int> res;
		fa[ls(x)] = fa[rs(x)] = 0;
		if (siz <= s[ls(x)])
		{
			res = split(ls(x), siz);
			ls(x) = res.second;
			res.second = x;
		}
		else
		{
			res = split(rs(x), siz - s[ls(x)] - 1);
			rs(x) = res.first;
			res.first = x;
		}
		pushup(x);
		return res;
	}
	*/
	inline auto split(int x,int key)
	{
		if(!x||!key) return make_pair(0,x);
		if(key==siz[x]) return make_pair(x,0);
		if(key<siz[ch[x][0]]+1)
		{
			fa[ch[x][0]]=0;
			auto res=split(ch[x][0],key);
			ch[x][0]=res.second;
			if(ch[x][0]) fa[ch[x][0]]=x;
			pushup(x);res.second=x;return res;
		}
		else
		{
			fa[ch[x][1]]=0;
			auto res=split(ch[x][1],key-siz[ch[x][0]]-1);
			ch[x][1]=res.first;
			if(ch[x][1]) fa[ch[x][1]]=x;
			pushup(x);res.first=x;return res;
		}
	}
/*	
	int merge(int a, int b)
	{
		if (!a || !b) return a + b;
		int x;
		if (order[a] > order[b])
		{
			fa[ls(x = b)] = 0;
			ls(b) = merge(a, ls(b));
		}
		else
		{
			fa[rs(x = a)] = 0;
			rs(a) = merge(rs(a), b);
		}
		return pushup(x);
	}
*/
	inline int merge(int a,int b)
	{
		if(!a||!b) return a|b;
		if(order[a]<order[b])
		{
			fa[ch[a][1]]=0;
			ch[a][1]=merge(ch[a][1],b);
			fa[ch[a][1]]=a;pushup(a);return a;
		}
		else
		{
			fa[ch[b][0]]=0;ch[b][0]=merge(a,ch[b][0]);
			fa[ch[b][0]]=b;pushup(b);return b;
		}
	}
	
#define mid (l + r >> 1)
	inline int build(int l, int r)
	{
		if (l == r)
		{
			order[sa[l]] = rand();
			return pushup(sa[l]);
		}
		else return merge(build(l, mid), build(mid + 1,r));
	}
	inline void init() {root = build(1, dfn);}
#define get(x) (x == ch[fa[x]][1])
	inline int rank(int x)
	{
		int res(s[ls(x)] + 1);
		while (fa[x])
		{
			res += get(x) * (s[ls(fa[x])] + 1);
			x = fa[x];
		}
		return res;
	}
	inline int kth(int k)
	{
		int x = root;
		while (1)
			if (k <= v[ls(x)]) x = ls(x);
			else if (ok[x] && k == v[ls(x)] + ok[x]) return id[x];
			else k -= v[ls(x)] + ok[x], x = rs(x);
		return 19260817;
	}
	inline void move(int l,int r,int pos)
	{
		auto r1 = split(root, r);
		auto r2 = split(r1.first, l - 1);
		auto r3 = split(r2.first, pos);
		swap(r2.second, r3.second);
		r2.first = merge(r3.first, r3.second);
		r1.first = merge(r2.first, r2.second);
		root = merge(r1.first, r1.second);
	}
}
int val[maxn], temp[maxn];
const auto cmp_val_less		= [&](int x, int y) {return val[x] > val[y];};
const auto cmp_val_greater	= [&](int x, int y) {return val[x] < val[y];};

int main()
{
#ifdef CraZYali
	freopen("C.in", "r", stdin);
	freopen("C.out", "w", stdout);
#endif
	cin >> n >> m >> q;
	const int mod = m;
	REP(i, 1, n) a[i] = read<int>();
	init();
	DREP(i, n, 1) extend(a[i], i);
	REP(i, 2, cur)
	{
		val[i] = a[id[i] + Max[ne[i]]];
		v[ne[i]].push_back(i);
	}
	REP(i, 1, cur)
		if (!v[i].empty()) sort(v[i].begin(), v[i].end(), cmp_val_greater);
	dfs(1);
	fhq::init();
	REP(i, 1, cur - 1) temp[i] = i;
	sort(temp + 1, temp + cur, cmp_val_less);

	REP(i, 1, q)
	{
		int d(read<int>()), k(read<int>());
		que[i] = make_pair(make_pair(d, k), i);
	}
	sort(que + 1, que + 1 + q);
	int j(1);
	REP(i, 1, q)
	{
		for (;j < cur && mod <= val[temp[j]] + que[i].first.first; j++)
		{
			int x(temp[j]), f(ne[x]), pos(fhq::rank(f)), l(pos + siz[f] - siz[x]), r(pos + siz[f] - 1);
			fhq::move(l, r, pos);
		}
		ans[que[i].second] = fhq::kth(que[i].first.second);
	}
	REP(i, 1, q) printf("%d\n", ans[i]);
	return 0;
}
