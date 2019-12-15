//orzhh
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 2000 + 10, maxm = 40;

	template <typename T>
inline T read()
{
	register T ans(0), flag(1);
	register char c(getchar());
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}
int bg[maxn], ne[maxn], to[maxn], w[maxn], e;
inline void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
}
inline void chkmax(int &a, int b)
{
	if (a < b) a = b;
}

int n, m, p[maxn][maxm], dep[maxn], siz[maxn], mx[maxn], wr[maxm][maxn];
bool vis[maxn];
void dfs(int x, int fa = 0)
{
	siz[x] = 1;
	mx[x] = 0;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa && vis[to[i]])
	{
		dfs(to[i], x);
		siz[x] += siz[to[i]];
		chkmax(mx[x], siz[to[i]]);
	}
}
inline void ins(vector <int> &a, int x, int fa, int A, int B)
{
	a.emplace_back(x);
	p[x][B] = A * dep[x];
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa && vis[to[i]])
	{
		dep[to[i]] = dep[x] + w[i];
		ins(a, to[i], x, A, B);
	}
}
int solve(vector <int> S, int m)
{
	int n(S.size());
	if (n == 1) return m;
	m++;
	if (n == 2)
	{
		if (m != 1) return m - 1;
		for (int i = bg[S[0]]; i; i = ne[i])
			if (to[i] == S[1]) p[to[i]][m] = w[i];
		return m;
	}
	REP(i, 0, n - 1) vis[S[i]] = 1;
	dfs(S[0], 0);
	int rt(S[0]);
	REP(i, 1, n - 1)
		if (max(mx[S[i]], n - siz[S[i]]) < max(mx[rt], n - siz[rt])) rt = S[i];
	dfs(rt, 0);
	vector <int> s, s0, s1;
	vector <int> tosolve0, tosolve1;
	tosolve0.emplace_back(rt);
	tosolve1.emplace_back(rt);
	int W(n >> 1);
	dep[rt] = 0;
	for (int i = bg[rt]; i; i = ne[i]) if (vis[to[i]])
	{
		s.emplace_back(to[i]);
		dep[to[i]] = w[i];
	}
	sort(s.begin(), s.end(), [&](int x, int y) {return w[x] > w[y];});
	for (auto i : s)
		if (W >= siz[i])
		{
			s0.emplace_back(i);
			W -= siz[i];
		}
		else s1.emplace_back(i);
	for (auto i : s0) ins(tosolve0, i, rt, 1,		m);
	for (auto i : s1) ins(tosolve1, i, rt, -1,	m);
	REP(i, 0, n - 1) vis[S[i]] = 0;
	int rm = solve(tosolve0, m);
	memset(wr[m], 0, sizeof wr[m]);
	REP(i, m, rm)
	{
		wr[m][i] = p[rt][i];
		p[rt][i] = 0;
	}
	chkmax(rm, solve(tosolve1, m));
	REP(i, m, rm)
	{
		int D = p[rt][i] - wr[m][i];
		for (auto j : tosolve0) if (j ^ rt)
			p[j][i] += D;
	}
	return rm;
}
int main()
{
#ifdef CraZYali
	freopen("vector-std.in", "r", stdin);
	freopen("vector-std.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 2, n)
	{
		int x(read<int>()), y(read<int>()), z(read<int>());
		add(x, y, z);add(y, x, z);
	}
	vector <int> qaq(n);
	REP(i, 1, n) qaq[i-1] = i;
	m = solve(qaq, 0);
	cout << m << endl;
	REP(i, 1, n)
		REP(j, 1, m)
		printf("%d%c", p[i][j], j == m ? '\n' : ' ');
	return 0;
}
