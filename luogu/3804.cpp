#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e6 + 10, maxN = maxn << 1, siz = 26;
int n, m, k;

int ch[maxN][siz], ne[maxN], Max[maxN], start, last;

int cur;
inline int newnode(int _Max = 0)
{
	Max[++cur] = _Max;
	return cur;
}
inline void init() {start = last = newnode();}
long long ans, cnt[maxN];
inline int extend(int c)
{
	int u = newnode(Max[last] + 1), v = last;
	cnt[u] = 1;
	for (;v && !ch[v][c]; v = ne[v]) ch[v][c] = u;
	if (!v) ne[u] = start;
	else if (Max[v] + 1 == Max[ch[v][c]]) ne[u] = ch[v][c];
	else
	{
		int n = newnode(Max[v] + 1), o = ch[v][c];
		copy(ch[o], ch[o] + siz, ch[n]);
		ne[n] = ne[o];
		ne[o] = ne[u] = n;
		for(; v && ch[v][c] == o; v = ne[v]) ch[v][c] = n;
	}
	return last = u;
}
int bg[maxN], nex[maxN], to[maxN], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	nex[e] = bg[x];
	bg[x] = e;
}
void dfs(int x)
{
	for (int i = bg[x]; i ; i = nex[i])
	{
		dfs(to[i]);
		cnt[x] += cnt[to[i]];
	}
	if (cnt[x] > 1) chkmax(ans, cnt[x] * Max[x]);
}

int main()
{
#ifdef CraZYali
	freopen("3804.in", "r", stdin);
	freopen("3804.out", "w", stdout);
#endif
	char c;
	init();
	while ((c = getchar()) != EOF && isalpha(c)) extend(c - 'a');
	REP(i, 2, cur) add(ne[i], i);
	dfs(1);
	cout << ans << endl;
	return 0;
}
