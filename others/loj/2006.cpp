#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 250 + 5, maxm = 250 + 5, maxN = maxn + maxm, maxE = maxn * maxm;

int bg[maxN], ne[maxE << 1], to[maxE << 1], w[maxE << 1], e = 1;
inline void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
}
#define link(x, y) add((x), (y), 1), add((y), (x), 0)
static char buf[100000], *p1(buf), *p2(buf);
#define Getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
template <typename T> inline T read()
{
	T ans(0);
	char c = Getchar();
	while (!isdigit(c)) c = Getchar();
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = Getchar();
	}
	return ans;
}

int n, m, k, N, S, T;
#define clear()\
{\
	REP(i, 1, N) bg[i] = 0;\
	e = 1;\
}

int a[maxn][maxm];

int q[maxN], head, tail, dis[maxN];
inline bool bfs()
{
	REP(i, 1, N) dis[i] = -1;
	dis[q[head = tail = 1] = T] = 0;
	while (head <= tail)
	{
		int x = q[head++];
		for (int i = bg[x]; i ; i = ne[i])
			if (w[i ^ 1] > 0 && dis[to[i]] == -1) dis[q[++tail] = to[i]] = dis[x] + 1;
	}
	return dis[S] != -1;
}
int cur[maxN];
int dfs(int x = S, int y = 1e9)
{
	if (x == T || !y) return y;
	int res(0), temp;
	for (int &i = cur[x]; i ; i = ne[i])
		if (w[i] > 0 && dis[to[i]] == dis[x] - 1 && (temp = dfs(to[i], min(y, w[i]))) > 0)
		{
			res += temp;
			w[i] -= temp;
			w[i ^ 1] += temp;
			if (!(y -= temp)) goto end;
		}
end:	return res;
}

inline bool judge(int mid)
{
	clear();
	REP(i, 1, n)
		REP(j, 1, m)
		if (a[i][j] <= mid) link(i, j + n);
	REP(i, 1, n) link(S, i);
	REP(i, 1, m) link(i + n, T);
	int res(0);
	while (bfs())
	{
		copy(bg + 1, bg + 1 + N, cur + 1);
		if ((res += dfs()) >= n - k + 1) return 1;
	}
	return 0;
}

#define mid (l + r >> 1)
int main()
{
#ifdef CraZYali
	freopen("2006.in", "r", stdin);
	freopen("2006.out", "w", stdout);
#endif
	n = read<int>();m = read<int>();k = read<int>();
	int l(1e9), r(1);
	REP(i, 1, n)
		REP(j, 1, m)
		{
			a[i][j] = read<int>();
			chkmax(r, a[i][j]);
			chkmin(l, a[i][j]);
		}
	S = n + m + 1;
	N = T = S + 1;
	while (l <= r)
		if (judge(mid)) r = mid - 1;
		else l = mid + 1;
	cout << r + 1 << endl;
	return 0;
}
