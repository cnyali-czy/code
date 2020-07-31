/*
	Problem:	perm.cpp
	Time:		2020-07-31 08:46
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include "perm.h"
#include <cmath>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 400 + 5 << 1, maxm = (maxn / 2) * (maxn / 2);

int bg[maxn], cur[maxn], ne[maxm << 1], to[maxm << 1], w[maxm << 1], e;
inline void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
}
inline void Add(int x, int y, int z)
{
	add(x, y, z);
	add(y, x, 0);
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

int dis[maxn], q[maxn], head, tail, N, S, T;
bool bfs()
{
	REP(i, 1, N) dis[i] = -1;
	q[head = tail = 0] = T;
	dis[T] = 0;
	while (head <= tail)
	{
		int x = q[head++];
		for (int i = bg[x]; i; i = ne[i])
			if (dis[to[i]] == -1 && w[i ^ 1] > 0)
			{
				dis[to[i]] = dis[x] + 1;
				q[++tail] = to[i];
			}
	}
	return dis[S] > 0;
}
int dfs(int x = S, int y = 1e9)
{
	if (x == T || !y) return y;
	int res = 0;
	for (int &i = cur[x]; i; i = ne[i])
		if (w[i] > 0 && dis[to[i]] == dis[x] - 1)
		{
			int tmp = dfs(to[i], min(y, w[i]));
			if (tmp > 0)
			{
				res += tmp;
				w[i] -= tmp;
				w[i ^ 1] += tmp;
				y -= tmp;
				if (!y) break;
			}
		}
	return res;
}
int good[maxn][maxn];

int id[maxn], top, block;
int blg[maxn], L[maxn], R[maxn];

vector <int> guess(int n)
{
	S = n + n + 1;
	T = n + n + 2;
	N = n + n + 2;
	REP(i, 1, N) bg[i] = 0;e = 1;
	REP(i, 1, n) REP(j, 1, n) good[i][j] = 0;
	int Times = 100000;
	vector <int> res(n), pick(n);
	REP(i, 0, n - 1) res[i] = i + 1;
	REP(i, 0, n - 1) pick[i] = i;
	random_shuffle(res.begin(), res.end());
	vector <int> lst = query(res);
	block = max(1., n * .6);
	REP(i, 1, n) blg[i] = (i - 1) / block + 1;
	REP(i, 1, n) R[blg[i]] = i;
	DEP(i, n, 1) L[blg[i]] = i;

	vector <int> cnt(n + 1, 0);

	while (Times--)
	{
		auto old = res;
		random_shuffle(pick.begin(), pick.end());
		REP(i, 0, block - 1) id[i] = pick[i];
		random_shuffle(id, id + block);
		REP(i, 0, block - 1) res[pick[i]] = old[id[i]];
		auto cur = query(res);
		REP(i, 0, n) cnt[i] = 0;
		REP(i, 0, n - 1) cnt[lst[i]]++;
		REP(i, 0, n - 1) cnt[cur[i]]--;
		REP(i, 0, block - 1) REP(j, 0, n - 1)
		{
			int t_lst = abs(j - pick[i]), t_cur = abs(j - id[i]);
			if (cnt[t_lst] < 0 && cnt[t_cur] > 0)
				good[j + 1][res[pick[i]]]++;
		}
		lst = cur;
	}
	vector <bool> sure(n + 1, 0);
	pick = res;
	random_shuffle(pick.begin(), pick.end());
	REP(I, 0, n - 1)
	{
		int i = pick[I];
		int ccc = 0, Max = 0;
		REP(j, 1, n) if (!sure[j] && Max < good[i][j])
		{
			Max = good[i][j];
			ccc = j;
		}
		sure[ccc] = 1;
		res[i - 1] = ccc;
	}
//	REP(i, 1, n) REP(j, 1, n) printf("%d%c", good[i][j], j == end_j ? '\n' : ' ');
	/*
	REP(i, 1, n) Add(S, i, 1);
	REP(i, 1, n) REP(j, 1, n) if (!good[i][j]) Add(i, j + n, 1);
	REP(i, 1, n) Add(i + n, T, 1);
	while (bfs())
	{
		copy(bg, bg + 1 + N, cur);
		while (dfs());
	}
	res = vector<int>(n, -1);
	REP(x, 1, n)
		for (int i = bg[x]; i; i = ne[i]) if (n < to[i] && to[i] <= n + n && !w[i])
		{
			res[x - 1] = to[i] - n;
			break;
		}
#ifdef CraZYali
	puts("FUCK");
	REP(i, 0, n - 1) printf("%d%c", res[i], i == end_i ? '\n' : ' ' );
#endif
*/
	return res;
}

#ifdef CraZYali
#include <bits/stdc++.h>
#include "perm.h"
#define pb push_back
using namespace std;
namespace workspace {
	const string verdict[]={"Wrong Answer","OK"};
	vector<int> p; int n,qcnt;
	int abs_int(int x){ return x<0?-x:x;}
	void ensure(bool f){ if(!f) printf("Invalid Query"),exit(0); }
	vector<int> query(vector<int> q){
		++qcnt; vector<int> P(n+1),Q(n+1),R; int u=0; ensure(q.size()==n);
		for(int i=0;i<n;++i) ensure(1<=q[i]&&q[i]<=n),P[p[i]]=i+1,Q[q[i]]=i+1;
		for(int i=1;i<=n;++i) ensure(Q[i]!=0),R.pb(abs_int(P[i]-Q[i]));
		sort(R.begin(),R.end());
		return R;
	}
	void main(){
		freopen("perm.in", "r", stdin);
		freopen("perm.out", "w", stdout);
		cin>>n;
		for(int i=1,x;i<=n;++i) cin>>x,p.pb(x);
		vector<int> q=guess(n);
		printf("%s\n%d\n",verdict[q==p].c_str(),qcnt);
		if(qcnt<=90)puts("100");
		else if(qcnt<=150)printf("%.2lf\n",100-.1*qcnt);
		else if(qcnt<=200)printf("%.2lf\n",100-.2*qcnt);
		else if(qcnt<=500)printf("%.2lf\n",80-.1*qcnt);
		else printf("%.2lf\n",30/sqrt(qcnt/500.));
	}
}
vector<int> query(vector<int> q){ return workspace::query(q); }
int main(){ workspace::main(); }
#endif
