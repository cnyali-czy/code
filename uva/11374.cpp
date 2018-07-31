#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>
#include <stack>
#include <queue>

using namespace std;
const int maxn = 500 + 5, maxm = 1000 + 10, inf = 1e9;

int bg[maxn], ne[maxm << 1], to[maxm << 1], w[maxm << 1], e = 1;

inline void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
}

int n, m, k, S, E;

priority_queue <pair <int, int> > q;


inline void calc(int root, int dis[], int fa[])
{
	REP(i, 1, n) dis[i] = inf;
	dis[root] = 0;
	while (!q.empty()) q.pop();
	q.push(make_pair(0, root));
	while (!q.empty())
	{
		int dist = -q.top().first;
		int x = q.top().second;
		q.pop();
		if (dist > dis[x]) continue;
		for (register int i = bg[x]; i ; i = ne[i])
			if (dis[to[i]] > dist + w[i]) q.push(make_pair(-(dis[to[i]] = dist + w[i]), to[i])), fa[to[i]] = x;
	}
}

int disS[maxn], disT[maxn], disA[maxn];
int faS[maxn], faT[maxn], faA[maxn];

stack <int> s;

int main()
{
#ifdef CraZYali
	freopen("11374.in", "r", stdin);
	freopen("11374.out", "w", stdout);
#endif
	bool first = 1;
	int S, T;
	while (scanf("%d%d%d", &n, &S, &T) != EOF)
	{
		if (first) first = 0;
		else printf("\n");
		e = 1;
		REP(i, 1, n) bg[i] = 0;
		scanf("%d", &m);
		register int x, y, z;
		while (m --> 0)
		{
			scanf("%d%d%d", &x, &y, &z);
			add(x, y, z);
			add(y, x, z);
		}
		calc(S, disS, faS);
		calc(T, disT, faT);
		bool flag = 0;
		int Min = disS[T];
		int A, B;
//S -> A -> B -> T
		scanf("%d", &m);
		while (m--)
		{
			scanf("%d%d%d", &x, &y, &z);
			if (Min > disS[x] + z + disT[y])
			{
				flag = 1;
				Min = disS[x] + z + disT[y];
				A = x;B = y;
			}
			if (Min > disS[y] + z + disT[x])
			{
				flag = 1;
				Min = disS[y] + z + disT[x];
				A = y;B = x;
			}
		}
		if (!flag)
		{
			register int now = S;
			while (now ^ T)
			{
				printf("%d ", now);
				now = faT[now];
			}
			printf("%d\nTicket Not Used\n", T);
		}
		else
		{
			register int now = S;
			calc(A, disA, faA);
			while (now ^ A)
			{
				printf("%d ", now);
				now = faA[now];
			}
			printf("%d ", A);
			now = B;
			while (now ^ T)
			{
				printf("%d ", now);
				now = faT[now];
			}
			printf("%d\n%d\n", T, A);
		}
		printf("%d\n", Min);
	}
	
	return 0;
}
