#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;
const int maxn = 3e5 + 10, maxN = maxn << 1, inf = 1e9+1;

const int siz = 26;
int ch[maxN][siz], Max[maxN], id[maxN], nex[maxN];
int start, last, cur;
inline int newnode(int _Max = 0, int _id = 0)
{
	++cur;
	Max[cur] = _Max;
	id[cur] = _id;
	return cur;
}
inline void init() {start = last = newnode();}
inline void extend(int c, int _id)
{
	int u(newnode(Max[last] + 1, _id)), v(last);
	for (; v && !ch[v][c]; v = nex[v]) ch[v][c] = u;
	if (!v) nex[u] = start;
	else if (Max[v] + 1 == Max[ch[v][c]]) nex[u] = ch[v][c];
	else
	{
		int New(newnode(Max[v] + 1)), Old(ch[v][c]);
		copy(ch[Old], ch[Old] + siz, ch[New]);
		nex[New] = nex[Old];
		nex[u] = nex[Old] = New;
		for (; v && ch[v][c] == Old; v = nex[v]) ch[v][c] = New;
	}
	last = u;
}
bool vis[maxN];
struct state{int x, y, z;}q[maxN];int top;
int rk[maxN], dfn, sa[maxn], h[maxn], height[maxn], c[siz];

int n, a[maxn];
char s[maxn];

int bg[maxN], ne[maxN], to[maxN], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}
void dfs(int x)
{
	if (id[x]) sa[++dfn] = id[x];
	for (int i = bg[x]; i ; i = ne[i]) dfs(to[i]);
}

int lg[maxn];
struct st_Min
{
	int Min[maxn][20];
	void init(int a[], int n)
	{
		REP(i, 1, n) Min[i][0] = a[i];
		REP(j, 1, 19)
			REP(i, 0, n)
			if (i + (1 << j) -1 <= n) Min[i][j] = min(Min[i][j-1], Min[i + (1 << j - 1)][j-1]);

	}
	int query(int l, int r)
	{
		int k = lg[r-l+1];
		return min(Min[l][k], Min[r - (1<<k) + 1][k]);
	}
}table;
struct st_Max
{
	int Maxa[maxn][20], Maxb[maxn][20];
	st_Max()
	{
		memset(Maxa, -63, sizeof(Maxa));
		memset(Maxb, -63, sizeof(Maxb));
	}
	void init(int a[], int n)
	{
		REP(i, 1, n) Maxa[i][0] = a[sa[i]] >= 0 ? a[sa[i]] : -inf;
		REP(i, 1, n) Maxb[i][0] = a[sa[i]] < 0 ? -a[sa[i]] : -inf;
		REP(j, 1, 19)
			REP(i, 0, n)
			if (i + (1 << j) -1 <= n)
			{
				Maxa[i][j] = max(Maxa[i][j-1], Maxa[i + (1 << j - 1)][j-1]);
				Maxb[i][j] = max(Maxb[i][j-1], Maxb[i + (1 << j - 1)][j-1]);
			}
			else break;
	}
	int querya(int l, int r)
	{
		int k = lg[r-l+1];
		return max(Maxa[l][k], Maxa[r - (1<<k) + 1][k]);
	}
	int queryb(int l, int r)
	{
		int k = lg[r-l+1];
		return max(Maxb[l][k], Maxb[r - (1<<k) + 1][k]);
	}
}Table;
int query(int l, int r)
{
	if (l > r) swap(l, r);
	return table.query(l+1, r);
}

int Left[maxn], Right[maxn];
long long ans[2][maxn];

int main()
{
#ifdef CraZYali
	freopen("131.in", "r", stdin);
	freopen("131.out", "w", stdout);
#endif
	init();
	scanf("%d\n%s\n", &n, s + 1);
	REP(i, 2, n) lg[i] = lg[i >> 1] + 1;
	REP(i, 1, n) scanf("%d", a + i);
	DREP(i, n, 1) extend(s[i] - 'a', i);
	vis[1] = 1;
	REP(i, 2, cur)
		if (!vis[i] && id[i])
			for (int j = i, pos = n; !vis[j]; vis[j] = 1, j = nex[j], pos--)
			{
				pos -= Max[j] - Max[nex[j]] - 1;
				q[++top] = state{nex[j], j, s[pos] - 'a'};
			}
	REP(i, 1, top) c[q[i].z]++;
	REP(i, 1, siz-1) c[i] += c[i-1];
	DREP(i, top, 1) rk[c[q[i].z]--] = i;
	DREP(i, top, 1) add(q[rk[i]].x, q[rk[i]].y);
	dfs(start);
	REP(i, 1, n) rk[sa[i]] = i;
	REP(i, 1, n)
	{
		h[i] = max(0, h[i-1] - 1);
		int maxlen = min(n - i + 1, n - sa[rk[i]-1] + 1);
		while (h[i] < maxlen && s[i+h[i]] == s[sa[rk[i]-1]+h[i]]) h[i]++;
	}
	REP(i, 1, n) height[rk[i]] = h[i];
#ifdef CraZYali
	REP(i, 1, n) fprintf(stderr,"%d%c", sa[i], i == n ? '\n' : ' ');
	REP(i, 1, n) fprintf(stderr,"%d%c", rk[i], i == n ? '\n' : ' ');
	REP(i, 1, n) fprintf(stderr,"%d%c", height[i], i == n ? '\n' : ' ');
#endif
	table.init(height, n);
	Table.init(a, n);
	REP(i, 1, n)
	{
		int pos;
		for (pos = i-1;pos;pos = Left[pos]-1)
			if (height[i] > height[pos]) break;
		Left[i] = pos + 1;
	}
	DREP(i, n, 1)
	{
		int pos;
		for (pos = i+1;pos;pos = Right[pos]+1)
			if (height[i] >= height[pos]) break;
		Right[i] = pos - 1;
	}
#ifdef CraZYali
	REP(i, 1, n) fprintf(stderr,"%d %d %d\n", height[i], Left[i],Right[i]);
#endif
	REP(i, 1, n) ans[0][height[i]] += 1ll*(Right[i]-i+1)*(i-Left[i]+1);
	memset(ans[1], -63, sizeof(ans[1]));
	REP(i, 1, n)
	{
		int Max1(Table.querya(i, Right[i]));
		int Max2(Table.querya(Left[i]-1, i-1));
		int negaMax1(Table.queryb(i, Right[i]));
		int negaMax2(Table.queryb(Left[i]-1, i-1));
#ifdef CraZYali
		printf("%d %d %d %d %d %d %d\n",height[i],Left[i],Right[i],Max1,Max2,negaMax1,negaMax2);
#endif
		if (Max1 > -inf && Max2 > -inf) chkmax(ans[1][height[i]], 1ll * Max1 * Max2);
		if (negaMax1 > -inf && negaMax2 > -inf) chkmax(ans[1][height[i]], 1ll * negaMax1 * negaMax2);
		if (negaMax1 > -inf && Max2 > -inf) chkmax(ans[1][height[i]], -1ll * negaMax1 * Max2);
		if (Max1 > -inf && negaMax2 > -inf) chkmax(ans[1][height[i]], -1ll * Max1 * negaMax2);
	}
	DREP(i, n-1, 0)
	{
		ans[0][i] += ans[0][i+1];
		if (ans[0][i+1]) chkmax(ans[1][i], ans[1][i+1]);
	}
	ans[0][0] -= n;
	REP(i, 0, n-1) printf("%lld %lld\n", ans[0][i], ans[0][i]==0?0:ans[1][i]);
	return 0;
}
