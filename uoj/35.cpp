#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;
const int maxn = 1e5 + 10, maxnode = maxn << 1;

const int siz = 26;

int Max[maxnode], id[maxnode], ch[maxnode][siz], ne[maxnode], start, last, cur;
int newnode(int _Max = 0, int _id = 0)
{
	++cur;
	id[cur] = _id;
	Max[cur] = _Max;
	return cur;
}
void init() {start = last = newnode();}

int n;
char s[maxn];

void extend(int c, int _id)
{
	int u = newnode(Max[last] + 1, _id), v = last;
	for (; v && !ch[v][c]; v = ne[v]) ch[v][c] = u;
	if (!v) ne[u] = start;
	else if (Max[v] + 1 == Max[ch[v][c]]) ne[u] = ch[v][c];
	else
	{
		int Old = ch[v][c], New = newnode(Max[v] + 1);
		copy(ch[Old], ch[Old] + siz, ch[New]);
		ne[New] = ne[Old];
		ne[u] = ne[Old] = New;
		for (; v && ch[v][c] == Old; v = ne[v]) ch[v][c] = New;
	}
	last = u;
}
bool vis[maxnode];
struct state{int x, y, z;}q[maxnode];int top;
int cnt[siz], rk[maxnode];

int bg[maxnode], nex[maxnode], to[maxnode], e;
void add(int x, int y)
{
	e++;
	to[e] = y;
	nex[e] = bg[x];
	bg[x] = e;
}
int sa[maxn], _rank[maxn], height[maxn], h[maxn], dfn;
void dfs(int x)
{
	if (id[x]) sa[++dfn] = id[x];
	for (int i = bg[x]; i ;i = nex[i]) dfs(to[i]);
}
int main()
{
#ifdef CraZYali
	freopen("35.in", "r", stdin);
	freopen("35.out", "w", stdout);
#endif
	init();
	scanf("%s", s + 1);n = strlen(s + 1);
	DREP(i, n, 1) extend(s[i] - 'a', i);
	vis[1] = 1;
	REP(i, 2, cur)
		if (!vis[i] && id[i])
			for (int j = i, pos = n; !vis[j]; vis[j] = 1, j = ne[j], --pos)
			{
				pos = pos - Max[j] + Max[ne[j]] + 1;
				q[++top] = state{ne[j], j, s[pos] - 'a'};
			}
	REP(i, 1, top) cnt[q[i].z]++;
	REP(i, 1, siz-1) cnt[i] += cnt[i-1];
	DREP(i, top, 1) rk[cnt[q[i].z]--] = i;
	DREP(i, top, 1) add(q[rk[i]].x, q[rk[i]].y);
	dfs(start);
	REP(i, 1, n) printf("%d%c", sa[i], i == n ? '\n' : ' ');
	REP(i, 1, n) _rank[sa[i]] = i;
	REP(i, 1, n)
	{
		h[i] = max(0, h[i-1] - 1);
		int maxlen = min(n - i + 1, n - sa[_rank[i]-1] + 1);
		while (h[i] < maxlen && s[i + h[i]] == s[sa[_rank[i]-1] + h[i]]) h[i]++;
	}
	REP(i, 1, n) height[_rank[i]] = h[i];
	REP(i, 2, n) printf("%d%c", height[i], i == n ? '\n' : ' ');
	return 0;
}
