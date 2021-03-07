/*
	Problem:	C.cpp
	Time:		2021-03-07 10:55
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <iostream>
#include <cstdio>
#define i64 long long
#define u64 unsigned i64

using namespace std;
const int maxn = 2500 + 10, MOD = 998244353;

int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
string w[maxn << 1];
inline void add(int x, int y, string z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
}

	template <typename T>
inline T read()
{
	T ans = 0, flag = 1;
	char c = getchar();
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

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, m, q;

int ch[233][26], fail[233], End[233], cur = 1;
void ins(string s, int id)
{
	int p = 1;
	REP(i, 0, (int)s.size() - 1)
	{
		int c = s[i] - 'a';
		if (!ch[p][c]) ch[p][c] = ++cur;
		p = ch[p][c];
	}
	End[p] = 1;
}
void build()
{
	static int que[233];int head, tail;
	que[head = tail = 0] = 1;
	REP(i, 0, 25) ch[0][i] = 1;
	while (head <= tail)
	{
		int x = que[head++];
		REP(i, 0, 25)
			if (ch[x][i])
			{
				fail[ch[x][i]] = ch[fail[x]][i];
				que[++tail] = ch[x][i];
			}
			else ch[x][i] = ch[fail[x]][i];
	}
}
int fa[maxn], ifa[maxn], T;
bool flg = 0;
void dfs(int x)
{
	if (x == T) flg = 1;
	if (flg) return;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa[x])
	{
		fa[to[i]] = x;
		ifa[to[i]] = i;
		dfs(to[i]);
	}
}

int main()
{
#ifdef CraZYali
	file("C");
#endif
	cin >> n >> m >> q;
	REP(i, 2, n)
	{
		int x = read<int>(), y = read<int>();string z;cin >> z;
		add(x, y, z);add(y, x, z);
	}
	REP(i, 1, m)
	{
		string z;
		cin >> z;
		ins(z, i);
	}
	build();
	while (q--)
	{
		int u = read<int>(), v = read<int>();
		REP(i, 1, n) fa[i] = 0;
		flg = 0;T = u;dfs(v);

		static u64 f[42][2], g[42][2];
		REP(i, 1, cur) f[i][0] = f[i][1] = 0;
		f[1][0] = 1;
		for (int x = u; x != v; x = fa[x])
		{
			REP(i, 1, cur)
			{
				g[i][0] = f[i][0] % MOD;f[i][0] = 0;
				g[i][1] = f[i][1] % MOD;f[i][1] = 0;
			}
			REP(i, 1, cur) for (register auto c : w[ifa[x]])
			{
				int nxt = ch[i][c - 'a'];
				f[nxt][End[nxt]] += g[i][0];
				f[nxt][1] += g[i][1];
			}
		}
		u64 ans = 0;
		REP(i, 1, cur) ans += f[i][1];
		cout << ans % MOD << '\n';
	}
	return 0;
}
