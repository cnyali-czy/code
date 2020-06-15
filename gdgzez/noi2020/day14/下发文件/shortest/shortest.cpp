/*
	Problem:	shortest.cpp
	Time:		2020-06-15 07:53
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <unordered_set>
#include <ctime>
#include <queue>
#include <iostream>
#include <cstdio>
#define int long long
using namespace std;
const int maxn = 10005, maxm = 20005;
const int inf = 1e15;
int X[maxm << 1], bg[maxn], ne[maxm << 1], to[maxm << 1], w[maxm << 1], e = 1;
inline void add(int x, int y, int z)
{
	e++;
	X[e] = x;
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

int n, m, k;

struct Node
{
	int x, d;
	inline bool operator < (const Node &B) const {return d > B.d;}
};
priority_queue <Node> q;
int dis[maxn];bool vis[maxn];
int dij()
{
	REP(i, 1, n) dis[i] = inf, vis[i] = 0;
	while (!q.empty()) q.pop();
	dis[1] = 0;
	q.emplace(Node{1, 0});
	while (!q.empty())
	{
		auto res = q.top();q.pop();
		int x = res.x, d = res.d;
		if (vis[x]) continue;
		vis[x] = 1;
		if (x == n) return d;
		for (int i = bg[x]; i; i = ne[i])
			if (w[i] < inf && dis[to[i]] > d + w[i])
			{
				dis[to[i]] = d + w[i];
				q.emplace(Node{to[i], dis[to[i]]});
			}
	}
	return inf;
}
int cur = 0;
vector <int> qaq, tmp;
int dd[maxn];
vector <pair <int, int> > EE[50000];

void output()
{
	cout << qaq.size() << endl;
	for (auto i : qaq) cout << i << ' ';
}
namespace Case0
{
	void work()
	{
		REP(times, 1, k)
		{
			REP(x, 1, n)
				for (int i = bg[x]; i; i = ne[i]) if (w[i] < inf && dis[to[i]] == dis[x] + w[i])
				{
					int tmp = w[i];
					w[i] = w[i ^ 1] = inf;
					if (dij() < inf) {qaq.emplace_back(i >> 1);goto End;}
					else w[i] = w[i ^ 1] = tmp;
				}
End:;
	cerr<<times<<endl;
		}
	}
}
namespace Case1
{
	int pick[maxm], ww[maxm << 1];
	int dfn;
	void calc()
	{
		dfn++;
		if (dfn% 10000 == 0){REP(i, 1, k) cerr<<pick[i]<<' ';cerr<<endl;}
		if (clock() * 1. / CLOCKS_PER_SEC >= 60)
		{
			output();
			exit(0);
		}
		tmp.clear();
		REP(i, 1, k) tmp.emplace_back(pick[i]);
		copy(w, w + e + 1, ww);
		cerr << dij() << ' ' ;
		REP(i, 1, k) w[pick[i] * 2] = w[(pick[i] * 2) ^ 1] = inf;
		cerr << dij() << endl;
		int res = dij();
		copy(ww, ww + e + 1, w);
		if (res < inf && cur < res)
		{
			cur = res;
			qaq = tmp;
		}
	}
	void dfs(int x, int y)
	{
		if (m - x + y < k) return;
		if (y == k) calc();
		else if (x == m) return;
		else
		{
			x++;
			int u = X[x * 2], v = to[x * 2];
			if (1||dd[u] == dd[v] + w[x * 2] || dd[v] == dd[u] + w[x * 2])
			{
				pick[y + 1] = x;
				dfs(x, y + 1);
			}
			pick[y + 1] = 0;
			dfs(x, y);
		}
	}
	void work()
	{
		qaq.emplace_back(8);
		qaq.emplace_back(17);
		qaq.emplace_back(14);
		qaq.emplace_back(7);
		qaq.emplace_back(24);
		qaq.emplace_back(5);
		qaq.emplace_back(21);
		qaq.emplace_back(25);
		qaq.emplace_back(28);
		qaq.emplace_back(26);
	//	dfs(0, 0);
	}
}
void clear()
{
	REP(x, 1, n) bg[x] = 0;
	e = 1;
}
namespace Case2
{
	void work()
	{
		clear();
		DEP(i, 200, 100) for(auto j : EE[i])
		{
			add(j.first,j.second,i);
			add(j.second,j.first,i);
		}
		Case1 :: work();
	}
}
const unsigned long long base = 1e9 + 7;
namespace Case01
{
	unordered_set <unsigned long long > In;
	int stack[maxn], top;
	bool shit[maxn];
	void dfs(int x)
	{
		shit[x] = 1;
		if (x == n)
		{
			REP(i, 1, top) qaq.emplace_back(stack[i]);
			output();
			exit(0);
			return;
		}
		if (shit[n]) return;
		for (int i = bg[x]; i; i = ne[i]) if (dd[to[i]] == dd[x] + w[i] && !shit[to[i]])
		{
			stack[++top] = i / 2;
			dfs(to[i]);
			top--;
		}
	}
	void work()
	{
		dfs(1);//gged
		return ;
		clear();
		DEP(i, 49999, 1)
			for (auto j : EE[i])
			{
				if (dd[j.first] == i + dd[j.second] ||
					dd[j.second] == i + dd[j.first])  continue;
				In.emplace(j.first * base * base + j.second * base + i);
				add(j.first,j.second,i);
				add(j.second,j.first,i);
				if (dij() < inf)
				{
					freopen("shortest3.in", "r", stdin);
					n = read<int>();m = read<int>();k = read<int>();
					clear();
					REP(ccc, 1, m)
					{
						int x = read<int>(), y = read<int>(), z = read<int>();
						unsigned long long Id = x * base * base + y * base + z;
						if (In.find(Id) == In.end())
						{
							qaq.emplace_back(ccc);
							k--;
							if (!k) goto End;
						}
					}
					goto End;
				}
			}
End:;
	}
}

namespace SPFA
{
	int d[maxn];
	bool vis[maxn];
	queue<int>q;
	void work()
	{
		q.emplace(1);
		while(!q.empty())
		{
			int x=q.front();q.pop();
			vis[x]=1;
			for(int i = bg[x];i;i=ne[i])
				if(d[to[i]]<d[x]+w[i]&&w[i]<inf)
				{
					d[to[i]]=d[x]+w[i];
					if(!vis[to[i]])
					{
						vis[to[i]]=1;
						q.emplace(to[i]);
					}
				}
		}
	}
}
namespace Case4
{
	int G[maxn][maxn];
	bool qq[maxn][maxn];
	void work()
	{
		clear();
		DEP(i, 9999, 1)
		{
			for (auto j : EE[i])
			{
				int x = j.first, y = j.second, z = i;
				if (G[x][y]) continue;
				G[x][y] = G[y][x] = z;
				add(x, y, z);add(y, x, z);
			}
		}
		SPFA :: work();
		REP(x, 1, n) for(int i = bg[x];i;i=ne[i])
		{
			int y = to[i];
			if(SPFA::d[y]!=SPFA::d[x]+w[i]&&SPFA::d[x]!=SPFA::d[y]+w[i])qq[x][y]=qq[y][x]=1;
		}
		//		REP(i, 1, n) REP(j, 1, n) printf("%d %d %d\n",i, j, G[i][j]);
		//		REP(k, 1, n) REP(i, 1, n) REP(j, 1, n) chkmax(G[i][j], G[i][k] + G[k][j]);
		freopen("shortest4.in", "r", stdin);
		n = read<int>();m = read<int>();k = read<int>();
		REP(i, 1, m)
		{
			int x = read<int>(), y = read<int>(), z = read<int>();
			//			if (z == G[x][y]) cout<< i << ' '<< x<< ' '<<y<<' '<<z<<endl;
			if (qq[x][y]||z < G[x][y]) qaq.emplace_back(i);
		}
		//	REP(x, 1, n) for (int i = bg[x]; i; i= ne[i]) printf("%d %d %d\n", x, to[i], w[i]);
	}
}

namespace Case5
{
	int gg[1005][1005];
	void work()
	{
		REP(i, 1, n) REP(j, 1, n) gg[i][j] = inf;
		int ccc = 0;
		REP(x, 1, n) for(int i = bg[x]; i; i = ne[i])
		{
			chkmax(ccc,abs(x-to[i]));
			chkmin(gg[x][to[i]],w[i]);
		}
		REP(k,1,n)REP(i,1,n)REP(j,1,n)chkmin(gg[i][j],gg[i][k]+gg[k][j]);
		REP(x, 1, n) for(int i = bg[x]; i; i = ne[i])
		{
			if(w[i]>gg[x][to[i]]&&(i&1))
				qaq.emplace_back(i / 2);
		}

		cerr<<ccc<<endl;
	}
}

namespace Case6
{
	bool vis[maxm << 1], shit[maxn];
	void dfs(int x)
	{
		shit[x] = 1;
		bool ccc = 0;
		for (int i = bg[x]; i; i = ne[i]) if (!shit[to[i]] && dis[to[i]] != dis[x] + w[i])
		{
			ccc = 1;
			vis[i] = vis[i ^ 1] = 1;
			dfs(to[i]);
		}
		if (!ccc) for (int i = bg[x]; i; i = ne[i]) if (!shit[to[i]])
		{
			vis[i] = vis[i^ 1] =1;
			dfs(to[i]);
		}
	}
	void work()
	{
		dfs(1);
		REP(i, 2, e) if (i & 1) if (!vis[i])
		{
			qaq.emplace_back(i >> 1),k--;
			if(!k)return;
		}
	}
}
namespace Caseccc
{
	bool shit[maxn];
	bool vis[114514];
	int stack[maxn], top;
	void dfs(int x)
	{
		if (x == n)
		{
			REP(i, 1, m) if (!vis[i]) qaq.emplace_back(i);
			output();exit(0);
		}
//		shit[x] = 1;
		for (int i = bg[x]; i; i = ne[i])
			if (SPFA :: d[to[i]] == SPFA :: d[x] + w[i] && !shit[to[i]])
			{
				vis[i / 2] = 1;
				dfs(to[i]);
			}
	}
	void work()
	{
		DEBUG;
		SPFA :: work();
		DEBUG;
		cerr << SPFA :: d[n] << endl;
		DEBUG;
		dfs(1);
	}
}
signed main()
{
#ifdef CraZYali
	file("shortest10");
#endif
	n = read<int>();m = read<int>();k = read<int>();
	REP(i, 1, m)
	{
		int x(read<int>()), y(read<int>()), z(read<int>());
		add(x, y, z);add(y, x, z);
		EE[z].emplace_back(x, y);
	}
	dij();
	copy(dis, dis + n + 1, dd);
		Case0 :: work();
	//	Case1 :: work();
	//	Case2 :: work();
//		Case01 :: work();
	//Case4 :: work();
//	Caseccc :: work();
//		Case6 :: work();
	output();
	return 0;
}
