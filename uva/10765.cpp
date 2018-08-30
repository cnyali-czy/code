#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

using namespace std;
const int maxn = 10000 + 10, maxm = 3e5 + 10;

int bg[maxn], ne[maxm << 1], to[maxm << 1], e = 1;

inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

int m, n, k;

bool iscut[maxn];
int pre[maxn], low[maxn], dfs_clock;

stack <pair<int, int> >s;
int bcccnt, bccno[maxn], bcctt[maxn];

void dfs(int u, int fa)
{
	register int child = 0;
	pre[u] = low[u] = ++dfs_clock;
	for (register int i = bg[u]; i ; i = ne[i])
		if (!pre[to[i]])
		{
			s.push(make_pair(u, to[i]));
			dfs(to[i], u);
			child++;
			chkmin(low[u], low[to[i]]);
			if (pre[u] <= low[to[i]])
			{
				iscut[u] = 1;
				++bcccnt;
				while (1)
				{
					if (bccno[s.top().first] ^ bcccnt)	bccno[s.top().first] = bcccnt, bcctt[s.top().first]++;
					if (bccno[s.top().second] ^ bcccnt)	bccno[s.top().second] = bcccnt, bcctt[s.top().second]++;
					if (s.top().first == u && s.top().second == to[i])
					{
						s.pop();
						break;
					}
					s.pop();
				}
			}
		}
		else if (to[i] ^ fa && pre[to[i]] < pre[u])
		{
			s.push(make_pair(u, to[i]));
			chkmin(low[u], pre[to[i]]);
		}
	if (child == 1 && !fa) iscut[u] = 0;
}

void get()
{
	REP(i, 1, n) iscut[i] = pre[i] = low[i] = bccno[i] = bcctt[i] = 0;
	dfs_clock = bcccnt = 0;
	dfs(1, 0);
}

priority_queue <pair<int, int> > Q;

int main()
{
#ifdef CraZYali
	freopen("10765.in", "r", stdin);
	freopen("10765.out", "w", stdout);
#endif
	register bool first = 1;
	while (scanf("%d%d", &n, &k) * (n + k))
	{
		e = 1;
		REP(i, 1, n) bg[i] = 0;
		while (1)
		{
			register int x, y;
			scanf("%d%d", &x, &y);
			x++;y++;
			if (!(x * y)) break;
			else add(x, y), add(y, x);
		}
		get();
		while (!Q.empty()) Q.pop();
		REP(i, 1, n)
			if (iscut[i]) Q.push(make_pair(bcctt[i], -(i - 1)));
			else Q.push(make_pair(1, -(i - 1)));
		while (k --> 0)
		{
			printf("%d %d\n", -Q.top().second, Q.top().first);
			Q.pop();
		}
		putchar(10);
	}
	
	return 0;
}
