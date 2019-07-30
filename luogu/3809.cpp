#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <bits/extc++.h>

using namespace std;
const int maxlen = 1e6 + 10, maxN = 1.5 * maxlen, siz = 125;

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}
int m, n, k;
char s[maxlen];

int start, last;
__gnu_pbds::gp_hash_table <char, int> ch[maxN];
int ne[maxN], Max[maxN], cur, id[maxN];
int newnode(int _Max = 0, int _id = 0)
{
	Max[++cur] = _Max;
	id[cur] = _id;
	return cur;
}
void init() {start = last = newnode();}
int extend(char c, int _id)
{
	int u = newnode(Max[last] + 1, _id), v = last;
	for (;v && !ch[v][c]; v = ne[v]) ch[v][c] = u;
	if (!v) ne[u] = start;
	else if (Max[v] == Max[ch[v][c]] - 1) ne[u] = ch[v][c];
	else
	{
		int n(newnode(Max[v] + 1)), o = ch[v][c];
		ch[n] = ch[o];
		ne[n] = ne[o];
		ne[o] = ne[u] = n;
		for (; v && ch[v][c] == o; v = ne[v]) ch[v][c] = n;
	}
	return last = u;
}
bool vis[maxN];
struct state{int x, y, z;}q[maxN];int top;
int c[siz + 5], rk[maxN];

int bg[maxN], nex[maxN], to[maxN], e;
void add(int x, int y)
{
	e++;
	to[e] = y;
	nex[e] = bg[x];
	bg[x] = e;
}

void dfs(int x)
{
	if (id[x]) printf("%d ", id[x]);
	for (int i = bg[x]; i ; i = nex[i]) dfs(to[i]);
}

int main()
{
#ifdef CraZYali
	file("3809");
#endif
	scanf("%s", s + 1);
	n = strlen(s + 1);
	init();
	DREP(i, n, 1) extend(s[i], i);
	vis[1] = 1;
	REP(i, 0, cur)
		if (!vis[i] && id[i])
			for (int pos = n, j = i; !vis[j]; vis[j] = 1, j = ne[j], pos--)
			{
				pos = pos - Max[j] + Max[ne[j]] + 1;
				q[++top] = (state){ne[j], j, s[pos]};
			}
	REP(i, 1, top) c[q[i].z]++;
	REP(i, 1, siz) c[i] += c[i-1];
	DREP(i, top, 1) rk[c[q[i].z]--] = i;
	DREP(i, top, 1) add(q[rk[i]].x, q[rk[i]].y);
	dfs(1);
	return 0;
}
