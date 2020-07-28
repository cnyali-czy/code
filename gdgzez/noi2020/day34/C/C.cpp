/*
	Problem:	C.cpp
	Time:		2020-07-27 22:57
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <cstring>
#include <queue>
#include <cmath>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 10 + 5, maxm = 10 + 5, maxl = 1500 + 10, maxS = 20050;

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

int n, m, k, l, r[maxl << 1], c[maxl << 1];

int f[maxl][maxS];
bool vis[maxl][maxS];
const int inf = 0x3f3f3f3f;
struct node
{
	int x, st;
	node(int x = 0, int st = 0) : x(x), st(st) {}
};
queue <node> q;

struct status
{
	node x;
	char p;
	status() {}
	status(node x, char p) : x(x), p(p) {}
}g[maxl][maxS];

int bin[maxn];

inline int chkmin(int &x, int y)
{
	if (x > y) {x = y;return 1;}
	return 0;
}

void orzjjs(status jjs, node x, int val)
{
	if (chkmin(f[x.x][x.st], val))
	{
		g[x.x][x.st] = jjs;
		if (!vis[x.x][x.st])
		{
			vis[x.x][x.st] = 1;
			q.emplace(x);
		}
	}
}

vector <int> Find(node x)
{
	if (!f[x.x][x.st])
	{
		vector <int> res(k);
		REP(i, 0, k - 1) res[i] = i + 1;
		return res;
	}
	status u = g[x.x][x.st];
	auto res = Find(u.x);
	if (u.x.x == x.x) return res;
	if (!u.p)
	{
		int pos = res[0];
		res.erase(res.begin());res.emplace_back(pos);
		printf("%d %d\n", pos, f[x.x][x.st]);
	}
	else
	{
		int pos = res.size() - u.p, tmp = res[pos];
		res.erase(res.begin() + pos);
		res.emplace_back(tmp);
		printf("%d %d\n", tmp, f[x.x][x.st]);
	}
	return res;
}

int main()
{
#ifdef CraZYali
	file("C");
#endif
	bin[0] = 1;
	REP(i, 1, 10) bin[i] = 3 * bin[i - 1];
	n = read<int>();m = read<int>();k = read<int>();l = read<int>();
	int b = max(n, m) - 1;
	l += b;
	DEP(i, b, 1)
	{
		r[i] = i - b + 1;
		c[i] = i - b + 1;
	}
	REP(i, b + 1, l)
	{
		r[i] = read<int>();
		c[i] = read<int>();
	}
	int st = 0;
	REP(j, b - k + 1, b) st += bin[j - 1];
	st <<= 1;
	long long ans = inf;ans++;
	memset(f, 0x3f, sizeof f);
	f[b][st] = 0;
	q.emplace(b, st);
	node last;
	while (!q.empty())
	{
		auto u = q.front();q.pop();
		int res = f[u.x][u.st];
		if (res >= ans) continue;
		if (u.x == l)
		{
			last = u;
			ans = res;
			break;
		}
		auto v = node(u.x, u.st / 3);
		orzjjs(status(u, 0), v, res + 1);//p事情都不干
		//放p吧，明明orzjjs
		int next_pos = u.x + 1, cnt = 0;
		DEP(i, b, 1)
		{
			if (u.st / bin[i - 1] % 3) next_pos--;
			if (u.st / bin[i - 1] % 3 != 2) continue;
			cnt++;
			int t = max(abs(r[u.x + 1] - r[next_pos]),
					abs(c[u.x + 1] - c[next_pos]));
			if (t > b - i) continue;
			int x = (u.st - bin[i - 1]) / 3 + 2 * bin[b - 1];
			v = node(u.x + 1, x);
			orzjjs(status(u, cnt), v, res + 1);
		}
		if (cnt < k && res >= b) // 可以调度一个来
		{
			v = node(u.x + 1, u.st / 3 + 2 * bin[b - 1]);
			orzjjs(status(u, 0), v, res + 1);
		}
	}
	cout << ans << endl;
	Find(last);
	return 0;
}
