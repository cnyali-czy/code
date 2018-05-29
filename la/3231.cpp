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
#include <map>
#include <set>

using namespace std;

inline void SLEEP(double tim)
{
	double start = clock();
	while (clock() - start < tim * CLOCKS_PER_SEC);
}


const int maxn = 1000 + 10, maxm = 10000 + 10, inf = (((1 << 30) - 1) << 1) + 1;
pair <int, int> a[maxm];

const int maxN = maxn + maxm, maxM = maxm * 3 + maxn;

int m, n;
int N, S, T;

int bg[maxN], ne[maxM << 1], to[maxM << 1], w[maxM << 1], e = 1;

inline bool Is_Mission(int x) {return 1 <= x && x <= m;}
inline bool Is_Cpu(int x) {return m + 1 <= x && x <= m + n;}

int mid;

inline int cap(int A, int B)
{
	if (A == S && Is_Mission(B)) return 1;
	if (Is_Mission(A) && Is_Cpu(B)) return 1;
	if (Is_Cpu(A) && B == T) return mid;
	return 0;
}

inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

queue <int> q;
int dis[maxN];
inline bool BFS()
{
	while (!q.empty()) q.pop();
	REP(i, 1, N) dis[i] = -1;
	dis[S] = 0;
	q.push(S);
	while (!q.empty())
	{
		register int x = q.front();
		q.pop();
		for (register int i = bg[x]; i ; i = ne[i])
			if (dis[to[i]] == -1 && cap(x, to[i]) - w[i] > 0)
			{
				dis[to[i]] = dis[x] + 1;
				q.push(to[i]);
			}
	}
	return dis[T] != -1;
}

int cur[maxN];

int dfs(int x, int y)
{
	if (x == T || !y) return y;
//	fprintf(stderr, "%d %d\n", x, y);
//	SLEEP(1.5);
	register int res = 0;
	for (register int &i = cur[x]; i ; i = ne[i])
	{
//		fprintf(stderr, "%d %d %d %d %d\n", bg[x], i, ne[i], x, to[i]);
//		SLEEP(1.5);
		if (dis[to[i]] == dis[x] + 1 && cap(x, to[i]) - w[i] > 0)
		{
//			DEBUG;
			register int temp = dfs(to[i], min(y, cap(x, to[i]) - w[i]));
			if (temp > 0)
			{
				w[i] += temp;
				w[i ^ 1] -= temp;
				res += temp;
				y -= temp;
				if (!y) return res;
			}
		}
	}
	return res;
}

inline int maxflow()
{
	register int ans(0);
	while (BFS())
	{
		for (register int i = 1; i <= N; i += 4) {cur[i] = bg[i]; cur[i + 1] = bg[i + 1]; cur[i + 2] = bg[i + 2]; cur[i + 3] = bg[i + 3];}
		ans += dfs(S, inf);
		if (ans > m) return -1;
	}
	return ans;
}

template <typename T> T read()
{
	T ans(0), p(1);
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}
/*
inline void output()
{
	REP(x, 1, N)
		for (register int i = bg[x]; i ; i = ne[i])
			if (cap[i]) printf("%d %d %d\n", x, to[i], cap[i]);puts("");
}
*/

int main()
{
#ifdef CraZYali
	freopen("3231.in", "r", stdin);
	freopen("3231.out", "w", stdout);
#endif
	register int TTT = read<int>();
	while (TTT --> 0)
	{
		n = read<int>();//处理器
		m = read<int>();//任务
		REP(i, 1, m) a[i] = make_pair(read<int>(), read<int>());
		S = n + m + 1;
		T = N = n + m + 2;
		
		for (register int i = 1; i <= N; i += 4) bg[i] = bg[i + 1] = bg[i + 2] = bg[i + 3] = 0;
		e = 1;
		REP(i, 1, n) {add(i + m, T);add(T, i + m);}
		REP(i, 1, m) {add(S, i);add(i, S);}
		REP(i, 1, m) {add(i, a[i].first + m);add(a[i].first + m, i);add(i, a[i].second + m);add(a[i].second + m, i);}
		
		int l(1), r(m), ans;
		while (l <= r)
		{
			mid = (l + r) >> 1;
			for (register int i = 1; i <= e; i += 4) w[i] = w[i + 1] = w[i + 2] = w[i + 3] = 0;
			register int temp = maxflow();
//			output();

			if (temp == m) {ans = mid; r = mid - 1;}
			else l = mid + 1;
		}
		printf("%d\n", ans);
	}
	return 0;
}
