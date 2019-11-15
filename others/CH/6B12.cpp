/*
 * File Name:	6B12.cpp
 * Author	:	CraZYali
 * Year		:	2019.11.15 09:50
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <cassert>
#include <iostream>
#include <cstdio>
#include <map>
#include <cstring>

using namespace std;
const double eps = 1e-8;
const int maxn = 20 * 50000 + 10;

int bg[maxn], ne[maxn], to[maxn], w[maxn], e;
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

int cur;
map <string, int> id;
int l[300];

#include <queue>
#include <vector>

int cnt[maxn];

double dis[maxn];
struct cmp
{
	inline bool operator () (const int &x, const int &y) const {return cnt[x] < cnt[y];}
};
//queue <int> q;

bool vis[maxn];

const double inf = 1e12;
bool judge(double mid)
{
	static const int N = cur;
	REP(i, 1, N) dis[i] = 0, cnt[i] = 1, vis[i] = 1;
	priority_queue <int, vector <int>, cmp> q;
	REP(i, 1, N) q.push(i);
	while (!q.empty())
	{
		int x = q.top();
		q.pop();
		vis[x] = 0;
		if (cnt[x] >= N) return 1;
		for (int i = bg[x]; i; i = ne[i])
			if (dis[to[i]] < dis[x] + w[i] - mid)
			{
				dis[to[i]] = dis[x] + w[i] - mid;
				if (!vis[to[i]])
				{
					vis[to[i]] = 1;
					cnt[to[i]]++;
					if (cnt[to[i]] >= N) return 1;
					q.push(to[i]);
				}
			}
	}
	return 0;
}

int main()
{
#ifdef CraZYali
	file("6B12");
#endif
	l['S'] = 1000;
	l['G'] = 500;
	l['D'] = 300;
	l['T'] = 200;
	l['K'] = 150;

	register int qaq = read<int>();
	while (qaq--)
	{
		int tot = 0;
		string res = "";
		char c(getchar());
		while (!isalpha(c)) c = getchar();
		bool first(1);
		string a(""), b("");
		while (1)
		{
			if (c == '-' || c == '\n' || c == '\r')
			{
				if (first) first = 0, a = res;
				else b = res;
				tot += l[res[0]];
				res = "";
				if (c == '\n' || c == '\r') break;
			}
			else res += c;
			if ((c = getchar()) == EOF) break;
		}
		if (!id[a]) id[a] = ++cur;
		if (!id[b]) id[b] = ++cur;
		add(id[a], id[b], tot);
	}
	double l(0), r(2.3e9);
	bool flag(0);
	while (r - l > eps)
	{
		double mid = (l + r) / 2;
		if (judge(mid))
		{
			l = mid;
			flag = 1;
		}
		else r = mid;
	}
	if (flag) printf("%.0lf\n", l);
	else puts("-1");
	return 0;
}
