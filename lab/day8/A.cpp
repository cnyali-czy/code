#define REP(i, s, e) for (int i = s; i <= e ; i++)

#include <bits/stdc++.h>
using namespace std;
const int maxn = 100000 + 10;

int a[maxn], b[maxn], c[maxn], n, m, Case, C;

unordered_map <int, int> d;

void turn(int x[], int n)
{
	d.clear();int cnt = 0;
	REP(i, 1, n) x[i] = d[x[i]] ? d[x[i]] : d[x[i]] = ++cnt;
}
int pos[maxn], ans;

namespace cheat
{
	const int maxN = maxn + maxn + maxn, inf = 1e9;
	int bg[maxn], e = 1;
	vector <int> to, ne, w;
	void add(int x, int y, int z)
	{
		if (e == 1) {to.push_back(0);ne.push_back(0);w.push_back(0);}
		if (e == 1) {to.push_back(0);ne.push_back(0);w.push_back(0);}
		e++;
		to.push_back(y);
		ne.push_back(bg[x]);
		bg[x] = e;
		w.push_back(z);
	}
	void ADD(int x, int y, int z) {add(x, y, z);add(y, x, 0);}
	int S, T, N;
	int dis[maxN], q[maxN], head, tail;
	bool bfs()
	{
		q[head = tail = 1] = S;
		REP(i, 1, N) dis[i] = -1;
		dis[S] = 0;
		while (head <= tail)
		{
			int x = q[head++];
			for (int i = bg[x]; i ; i = ne[i])
				if (w[i] > 0 && dis[to[i]] == -1) dis[q[++tail] = to[i]] = dis[x] + 1;
		}
		return dis[T] != -1;
	}

	int dfs(int x = S, int y = inf)
	{
		if (x == T || !y) return y;
		int res = 0;
		for (int i = bg[x], temp; i ; i = ne[i])
			if (w[i] > 0 && dis[to[i]] == dis[x] + 1 && (temp = dfs(to[i], min(y, w[i]))) > 0)
			{
				w[i] -= temp;
				w[i ^ 1] += temp;
				res += temp;
				y -= temp;
				if (!y) break;
			}
		return res;
	}
	int ipt[maxN];
	void clear(){REP(i,1,N)bg[i]=0;e=1;to.clear();ne.clear();w.clear();}
	void work()
	{
		N = C + C + C + 2;
		S = C + C + C + 1;
		T = C + C + C + 2;
		clear();
		REP(i, 1, m) ADD(S, b[i], 1);
		REP(i, 1, m)
			REP(j, 1, C) ADD(b[i], C + j, 1);
		REP(i, 1, n) 
			REP(j, 1, C) ADD(C + j, C + C + a[i], 1);
		REP(i, 1, n) ADD(C + C + a[i], T, 1);
#ifndef ONLINE_JUDGE
		REP(x,1,N)
			for (int i = bg[x]; i ; i = ne[i])printf("%d %d %d\n", x, to[i], w[i]);
		puts("========");
#endif
		int flw(0);
		while (bfs()) flw+=dfs();
//		cout<<"flow = " <<flw<<endl;
		REP(A, 1, n)
		{
			int x = C + C + a[A];
			for (int i = bg[x]; i ;i = ne[i])
				if (to[i] == T) {ipt[C + C + A] = i;break;}
		}
		int cnt(0);
		REP(i, 1, m) cnt += !w[ipt[C + C + i]];
		REP(i, m + 1, n + 1)
		{
			if (cnt == m) pos[++ans] = i-m;
			cnt -= !w[ipt[C + C + i-m]];
			cnt += !w[ipt[C + C + i]];
		}
	}
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	cin >> Case >> C;
	while (Case--)
	{
		scanf("%d%d", &n, &m);
		REP(i, 1, n) scanf("%d", a + i);
		REP(i, 1, m) scanf("%d", b + i);
		ans = 0;
		if (0 && n <= 1000 && m <= 1000)
		{
			turn(b, m);
			REP(i, 1, n-m+1)
			{
				REP(j, 1, m) c[j] = a[i+j-1];
				turn(c, m);
				bool flag = 1;
				REP(j, 1, m) if (c[j] != b[j]) {flag = 0;break;}
				if (flag) pos[++ans] = i;
			}
		}
		else cheat::work();
		printf("%d\n", ans);
		REP(i, 1, ans) printf("%d%c", pos[i], i == ans ? '\n' : ' ');
	}
	return 0;
}
