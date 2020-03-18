/*
 * File Name:	C.cpp
 * Author	:	CraZYali
 * Time		:	2020.02.03 20:26
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <random>
#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 2e5 + 10;

int bg[maxn], ne[maxn << 1], to[maxn << 1], w[maxn << 1], e = 1;
inline void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
}

template <typename T> inline T read()
{
	T ans(0), flag(1);
	char c(getchar());
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

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout);

int n, k;

long long dep[maxn];
int blg[maxn];
void dfs(int x, int fa = 0)
{
	if (!dep[fa]) blg[x] = x;
	else blg[x] = blg[fa];
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
	{
		dep[to[i]] = dep[x] + w[i];
		dfs(to[i], x);
	}
}
mt19937 R;
int Rand(int l, int r) {return R() % (r - l + 1) + l;}
int cnt[maxn], id[maxn];
inline bool cmp(int x, int y) {return dep[x] > dep[y];}
long long ans;

int Max[maxn], siz[maxn], rt, all;
bool vis[maxn];
void dfs1(int x, int fa = -1)
{
	siz[x] = 1;
	Max[x] = 0;
	for (int i = bg[x]; i; i = ne[i]) if (!vis[to[i]] && to[i] ^ fa)
	{
		dfs1(to[i], x);
		siz[x] += siz[to[i]];
		chkmax(Max[x], siz[to[i]]);
	}
	chkmax(Max[x], all - siz[x]);
	if (Max[x] < Max[rt] || !rt) rt = x;
}
int get(int x, int fa = -1)
{
	int res = 1;
	for (int i = bg[x]; i; i = ne[i]) if (!vis[to[i]] && to[i] ^ fa)
		res += get(to[i], x);
	return res;
}
int findrt(int x)
{
	rt = 0;
	all = get(x);
	dfs1(x);
	return rt;
}

int ccc;
void solve(int rt)
{
	bool flag = 1;
	int Try = 0;
	vis[rt] = 1;
	dep[rt] = 0;
	dfs(rt);
	sort(id + 1, id + 1 + n, cmp);
	REP(i, 1, n) cnt[i] = 0;
	long long res = 0;
	int ard = 0;
	REP(i, 1, n)
	{
		if (cnt[blg[id[i]]] < k / 2)
		{
			cnt[blg[id[i]]]++;
			ard++;
			res += dep[id[i]];
		}
		else
		{
			flag = 0;
			Try = blg[id[i]];
			break;
		}
		if (ard >= k) break;
	}
	if (!vis[Try] && Try) solve(findrt(Try));
	else
	{
		res = ard = 0;
		REP(i, 1, n) cnt[i] = 0;
		REP(i, 1, n)
		{
			if (cnt[blg[id[i]]] < k / 2)
			{
				cnt[blg[id[i]]]++;
				ard++;
				res += dep[id[i]];
			}
			if (ard >= k) break;
		}
		chkmax(ans, res + res);
		cout << ans << endl;
		exit(0);
	}
}

int main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();
	k = read<int>();
	REP(i, 2, n)
	{
		int x(read<int>()), y(read<int>()), z(read<int>());
		add(x, y, z);add(y, x, z);
	}
	REP(i, 1, n) id[i] = i;
	solve(1);
	cout << ans << endl;
	return 0;
}
