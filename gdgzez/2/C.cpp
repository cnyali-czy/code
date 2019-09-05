#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <tr1/unordered_map>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;
const int maxn = 1e5 + 10, maxnode = maxn << 1;


tr1::unordered_map <int, int> ch[maxnode];
int Max[maxnode], id[maxnode], ne[maxnode], start, last, cur;
int newnode(int _Max = 0, int _id = 0)
{
	++cur;
	id[cur] = _id;
	Max[cur] = _Max;
	return cur;
}
void init() {start = last = newnode();}

const int siz = maxn;
void extend(int c, int _id)
{
	int u = newnode(Max[last] + 1, _id), v = last;
	for (; v && !ch[v][c]; v = ne[v]) ch[v][c] = u;
	if (!v) ne[u] = start;
	else if (Max[v] + 1 == Max[ch[v][c]]) ne[u] = ch[v][c];
	else
	{
		int Old = ch[v][c], New = newnode(Max[v] + 1);
		ch[New] = ch[Old];
		ne[New] = ne[Old];
		ne[u] = ne[Old] = New;
		for (; v && ch[v][c] == Old; v = ne[v]) ch[v][c] = New;
	}
	last = u;
}
bool vis[maxnode];
struct state{int x, y, z;}q[maxnode];int top;

int bg[maxnode], nex[maxnode], to[maxnode], e;
void add(int x, int y)
{
	e++;
	to[e] = y;
	nex[e] = bg[x];
	bg[x] = e;
}
int sa[maxn], rk[maxnode], dfn, cnt[maxn];
void dfs(int x)
{
	if (id[x]) sa[++dfn] = id[x];
	for (int i = bg[x]; i ;i = nex[i]) dfs(to[i]);
}

int n, m, Q;
int a[maxn], b[maxn], c[maxn], k;

int main()
{
#ifdef CraZYali
	freopen("C.in", "r", stdin);
	freopen("C.out", "w", stdout);
#endif
	init();
	cin >> n >> m >> Q;
	REP(i, 1, n) scanf("%d", a + i), b[i] = a[i];//a[i] = b[i] = read<int>();
	sort(b + 1, b + 1 + n);
	k = unique(b + 1, b + 1 + n) - b - 1;
	REP(i, 1, n) c[i] = lower_bound(b + 1, b + 1 + k, a[i]) - b;
	DREP(i, n, 1) extend(c[i], i);
	vis[1] = 1;
	REP(i, 2, cur)
		if (!vis[i] && id[i])
			for (int j = i, pos = n; !vis[j]; vis[j] = 1, j = ne[j], --pos)
			{
				pos = pos - Max[j] + Max[ne[j]] + 1;
				q[++top] = state{ne[j], j, c[pos]};
			}
	REP(i, 1, top) cnt[q[i].z]++;
	REP(i, 1, siz-1) cnt[i] += cnt[i-1];
	DREP(i, top, 1) rk[cnt[q[i].z]--] = i;
	DREP(i, top, 1) add(q[rk[i]].x, q[rk[i]].y);
	dfs(start);
	return 0;
}
