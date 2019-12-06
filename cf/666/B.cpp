#define  REP(i, s, e) for (register int i(s); i <= e; i++)
#define DREP(i, s, e) for (register int i(s); i >= e; i--)

#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>

using namespace std;
const int maxn = 3000 + 10, maxm = 5000 + 10;

int bg[maxn], ne[maxm], to[maxm], e;
int rbg[maxn], rne[maxm], rto[maxm], re;
inline void radd(int x, int y)
{
	re++;
	rto[re] = y;
	rne[re] = rbg[x];
	rbg[x] = re;
}
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	radd(y, x);
}

int n, m, q[maxn], head, tail, rdis[maxn][maxn], dis[maxn][maxn];

int list[maxn][maxn], rlist[maxn][maxn];
#define chkmax(a, b) (a < b ? a = b : a)
int A, B, C, D, ans;
inline void check(int a, int b, int c, int d)
{
	if (a == b || a == c || a == d || b == d || c == d) return;
	if (dis[a][b] == -1 || dis[b][c] == -1 || dis[c][d] == -1) return;
	int tmp = dis[a][b] + dis[b][c] + dis[c][d];
	if (tmp > ans)
	{
		ans = tmp;
		A = a;
		B = b;
		C = c;
		D = d;
	}
}
int main()
{
#ifdef CraZYali
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif
	cin >> n >> m;
	memset(dis, -1, sizeof dis);
	memset(rdis, -1, sizeof rdis);
	while (m--)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		add(x, y);
	}
	REP(i, 1, n)
	{
		REP(j, 1, n) rlist[i][j] = list[i][j] = j;
		dis[i][q[head = tail = 0] = i] = 0;
		while (head <= tail)
		{
			int x = q[head++];
			for (int _i = bg[x]; _i; _i = ne[_i]) if (dis[i][to[_i]] == -1)
				dis[i][q[++tail] = to[_i]] = dis[i][x] + 1;
		}
		rdis[i][q[head = tail = 0] = i] = 0;
		while (head <= tail)
		{
			int x = q[head++];
			for (int _i = rbg[x]; _i; _i = rne[_i]) if (rdis[i][rto[_i]] == -1)
				rdis[i][q[++tail] = rto[_i]] = rdis[i][x] + 1;
		}
		sort(list[i] + 1, list[i] + 1 + n, [&](int x, int y) {return dis[i][x] > dis[i][y];});
		sort(rlist[i] + 1, rlist[i] + 1 + n, [&](int x, int y) {return rdis[i][x] > rdis[i][y];});
	}
	REP(b, 1, n)
		REP(c, 1, n) if (b ^ c)
		REP(A, 1, 3)
		REP(D, 1, 3)
			check(rlist[b][A], b, c, list[c][D]);
#ifdef CraZYali
	cerr<<ans<<endl;
#endif
	cout << A << ' ' << B << ' ' << C << ' ' << D << endl;
	return 0;
}
