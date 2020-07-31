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

#include <set>
#include <ctime>
#include "perm.h"
#include <random>
#include <cmath>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 400 + 5;

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

int good[maxn][maxn];
int id[maxn], top, block;
int cnt[maxn], sure[maxn];
mt19937 hh;
int randint(int l, int r) {return hh() % (r - l + 1) + l;}
int count(const vector <int> &a)
{
	int res = 0;
	for (auto i : a) res += !i;
	return res;
}
vector <int> guess(int n)
{
	if (n == 1) return vector <int> (1, 1);
	REP(i, 1, n) REP(j, 1, n) good[i][j] = 0;
	hh = mt19937(time(0));
	int Times = 120, pre = 10;
	Times -= pre;
	vector <int> res(n), pick(n);
	REP(i, 0, n - 1) res[i] = i + 1;
	REP(i, 0, n - 1) pick[i] = i;
	shuffle(res.begin(), res.end(), hh);
	vector <int> lst = query(res);

	int block = max(2., n * .6);
	while (--Times)
	{
		auto old = res;
		shuffle(pick.begin(), pick.end(), hh);
		REP(i, 0, block - 1) id[i] = pick[i];
		shuffle(id, id + block, hh);
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

	set <vector <int> > Vis;
	REP(Case, 1, pre)
	{
		REP(i, 1, n) sure[i] = 0;
		pick = res;
		shuffle(pick.begin(), pick.end(), hh);
		auto qaq = pick;
		for (auto i : pick)
		{
			shuffle(qaq.begin(), qaq.end(), hh);
			int ccc = 0, Max = -1;
			for (auto j : qaq)
				if (!sure[j] && Max < good[i][j])
				{
					Max = good[i][j];
					ccc = j;
				}
			sure[ccc] = 1;
			res[i - 1] = ccc;
		}
		if (Vis.count(res)) {Case--;continue;}
		Vis.insert(res);
		if (count(query(res)) == n) return res;
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
