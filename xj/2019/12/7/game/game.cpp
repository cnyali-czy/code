#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <bits/stdc++.h>
#include "game.h"
using namespace std;
const int maxn = 5000 + 10, maxm = 2e7;

int bg[maxn << 1], ne[maxm], to[maxm], w[maxm], e = 1;
inline void add(int x, int y, int z)
{
	e++;
	w[e] = z;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}
int S, T, N;
bool ban[maxn][maxn];
int q[maxn << 1], head, tail, dis[maxn << 1];
bool bfs()
{
	REP(i, 1, N) dis[i] = -1;
	dis[q[head = tail = 0] = T] = 0;
	while (head <= tail)
	{
		int x = q[head++];
		for (int i = bg[x]; i; i = ne[i])
			if (w[i ^ 1] > 0 && dis[to[i]] == -1)
				dis[q[++tail] = to[i]] = dis[x] + 1;
	}
	return dis[S] != -1;
}
int dfs(int x = S, int y = 1e9)
{
	if (x == T || !y) return y;
	int res(0);
	for (int i = bg[x]; i; i = ne[i])
		if (w[i] > 0 && dis[to[i]] == dis[x] - 1)
		{
			int tmp = dfs(to[i], min(y, w[i]));
			if (tmp > 0)
			{
				res += tmp;
				y -= tmp;
				w[i] -= tmp;
				w[i ^ 1] += tmp;
				if (!y) break;
			}
		}
	return res;
}
vector <int> guess(int n, int limit)
{
	srand(time(0));
	vector <int> ans(n);
	REP(i, 0, n - 1) ans[i] = i + 1;
	int times(0),qaq(0);
	while (limit)
	{
		times++;
		random_shuffle(ans.begin(), ans.end());
		limit--;
		if(!count(ans))
		{
			qaq++;
			REP(i, 1, n)
				ban[i][ans[i-1]] = 1;
		}
	}
	REP(i, 1, n)
		REP(j, 1, n) if (!ban[i][j])
		{
			add(i, j + n, 1);
			add(j + n, i, 0);
		}
	S = n + n + 1, N = T = n + n + 2;
	REP(i, 1, n) add(S, i, 1e9), add(i, S, 0);
	REP(i, 1, n) add(i + n, T, 1e9), add(T, i + n, 0);
	while (bfs())
	{
		int tmp = dfs();
		while (tmp) tmp = dfs();
	}
	REP(x, 1, n)
		for (int i = bg[x]; i; i = ne[i])
			if (!w[i] && n < to[i] && to[i] <= n + n)
			{
				ans[x-1] = to[i] - n;
				break;
			}
	return ans;
}
#ifdef CraZYali
#include "game.h"
#include<bits/stdc++.h>

namespace gg {

	static const int N = 10005;

	static int n, limit, a[N], b[N], times;

	void work() {
		scanf("%d %d", &n, &limit);
		for(int i = 0; i < n; i ++) {
			scanf("%d", &a[i]);
			if(!(a[i] >= 1 && a[i] <= n)) {
				printf("The input is invalid.\n");
				assert(a[i] >= 1 && a[i] <= n);
			}
			b[a[i]] = i + 1;
		}
		for(int i = 1; i <= n; i ++) {
			if(!(b[i] != 0)) {
				printf("The input is invalid.\n");
				assert(b[i] != 0);
			}
		}
		std :: vector<int> ans = guess(n, limit);
		if(!(ans.size() == n)) {
			printf("Wrong answer.\n");
			//assert(ans.size() == n);
			exit(0);
		}
		for(int i = 0; i < n; i ++)
			if(!(ans[i] == a[i])) {
				printf("Wrong answer.\n");
				//assert(ans[i] == a[i]);
				exit(0);
			}
		printf("Accepted.\nYou use %d queries\n", times);
	}
}

int count(std :: vector<int> c) {
	using namespace gg;
	times ++;
	if(!(times <= limit)) {
		printf("Too many queries.\n");
		//assert(times <= limit);
		exit(0);
	}
	int sum = 0;
	assert(c.size() == n);
	for(int i = 1; i <= n; i ++) b[i] = 0;
	for(int i = 0; i < n; i ++) {
		if(!(c[i] >= 1 && c[i] <= n)) {
			printf("The query is invalid.\n");
			assert(c[i] >= 1 && c[i] <= n);
		}
		sum += c[i] == a[i];
		b[c[i]] = i + 1;
	}
	for(int i = 1; i <= n; i ++) {
		if(!(b[i] != 0)) {
			printf("The query is invalid.\n");
			assert(b[i] != 0);
		}
	}
	return sum;
}

int main()
{
	freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);
	gg :: work();
	return 0;
}
#endif
