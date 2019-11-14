#define REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>

using namespace std;
const int maxn = 2000 + 10, maxm = 3000 + 10;

int bg[maxn], ne[maxm << 1], to[maxm << 1], w[maxm << 1], e;
inline void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
}

template <typename T> T read()
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

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

int m, n, k;

const int inf = 1e9;
int cnt[maxn], dis[maxn];
struct cmp
{
	inline bool operator () (int x, int y) {return cnt[x] < cnt[y];}
};
priority_queue <int, vector <int>, cmp> q;
bool vis[maxn];

int main()
{
#ifdef CraZYali
	file("3385");
#endif
	register int T(read<int>());
	while (T--)
	{
		n = read<int>();
		m = read<int>();
		e = 0;
		REP(i, 1, n) vis[i] = bg[i] = cnt[i] = 0, dis[i] = inf;
		while (m--)
		{
			int x(read<int>()), y(read<int>()), z(read<int>());
			add(x, y, z);
			if (z >= 0) add(y, x, z);
		}
		while (!q.empty()) q.pop();
		dis[1] = 0; 
		q.push(1);
		bool flag(0);
		while (!q.empty())
		{
			int x = q.top();
			q.pop();
			if (cnt[x] >= n)
			{
				flag = 1;
				break;
			}
			vis[x] = 0;
			cnt[x]++;
			for (int i = bg[x]; i; i = ne[i])
				if (dis[to[i]] > dis[x] + w[i])
				{
					dis[to[i]] = dis[x] + w[i];
					if (!vis[to[i]])
					{
						vis[to[i]] = 1;
						q.push(to[i]);
					}
				}
		}
		puts(flag ? "YE5" : "N0");
	}
	return 0;
}
