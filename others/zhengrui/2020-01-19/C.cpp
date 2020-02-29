//test
/*
	Problem:	C.cpp
	Time:		2020-02-27 20:49
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <ctime>
#include <cmath>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;

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

inline int min(int x, int y) {if (x < y) return x;return y;}
inline int max(int x, int y) {if (x > y) return x;return y;}

namespace run
{
	using namespace std;
	const int N = 2000 + 10;
	int d[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
	int n, m, q, W, ans[N], Up[N][N], Dn[N][N], mark[N];
	char s[N][N];
	struct Query
	{
		int xl, yl, xr, yr, i;
		inline Query(int xl = 0, int yl = 0, int xr = 0, int yr = 0, int i = 0) : xl(xl), yl(yl), xr(xr), yr(yr), i(i) {}
		inline bool operator < (const Query &B) const {return yr - yl > B.yr - B.yl;}
	};
	vector <Query> g[N];
	namespace Dsu
	{
		int f[N * N], siz[N * N];
		inline void init()
		{
			REP(i, 1, n * m) siz[f[i] = i] = 1;
		}
		int find(int x) {return x == f[x] ? f[x] : f[x] = find(f[x]);}
		inline void uni(int x, int y)
		{
			x = find(x);y = find(y);
			if (x == y) return;
			if (siz[x] < siz[y]) swap(x, y);
			f[y] = x;siz[x] += siz[y];
		}
		inline int Querysiz(int x) {return siz[find(x)];}
	}
	namespace my_sol1
	{
		int v[N][N], pre[N], pos[N*N];
		vector <int> V[N];
		inline int getid(int x, int y) {return (x - 1) * m + y;}
		inline int getx(int id) {return (id - 1) / m + 1;}
		inline int gety(int id) {return (id - 1) % m + 1;}
		inline void updv(int &l)
		{
			l++;
			REP(i, 1, n - l + 2)
				REP(j, 1, m) chkmin(v[i][j], v[i+1][j]);
		}
		inline void work()
		{
			REP(i, 1, n) DEP(j, m, 1) v[i][j] = s[i][j] ? 0 : v[i][j+1] + 1;
			for (int l = 1; l <= W; updv(l)) if (mark[l])
			{
				Dsu::init();
				REP(i, 0, m + 1) pre[i] = 0;
				REP(i, 1, n - l + 1) REP(j, 1, m) if (v[i][j]) pre[v[i][j]]++;
				DEP(i, m, 0) pre[i] += pre[i + 1];
				REP(i, 1, n - l + 1) REP(j, 1, m) if (v[i][j]) pos[--pre[v[i][j]]] = getid(i, j);
				sort(g[l].begin(), g[l].end());
				int lim = m + 1;
				for (auto t : g[l])
				{
					int l = t.yr - t.yl + 1;
					while (lim > l)
					{
						lim--;
						REP(p, pre[lim], pre[lim - 1] - 1)
						{
							int x = getx(pos[p]), y = gety(pos[p]);
							REP(i, 0, 3)
							{
								int tx = x + d[i][0], ty = y + d[i][1];
								if (v[tx][ty] >= lim) Dsu::uni(pos[p], getid(tx, ty));
							}
						}
					}
					ans[t.i] = Dsu::Querysiz(getid(t.xl, t.yl));
				}
			}
		}
	}
	namespace sol2
	{
		int L, ans, T, head, tail, vis[N][N], q[N * N], up[N][N], dn[N][N], mn[N];
		inline void push(int x, int y)
		{
			q[++tail] = x << 15 | y;
			vis[x][y] = T;
		}
		inline void bfs(int x,int y)
		{
			head = 0;tail = -1;
			push(x, y);
			while (head <= tail)
			{
				int x = q[head++], y = x & 32767;
				x >>= 15;
				int res = up[x][y] + dn[x][y] - L + 1;
				if (res <= 0) continue;
				else ans += res;
				if(vis[x][y-1]!=T&&min(up[x][y],up[x][y-1])+min(dn[x][y],dn[x][y-1])-L+1>0)push(x,y-1);
				if(vis[x][y+1]!=T&&min(up[x][y],up[x][y+1])+min(dn[x][y],dn[x][y+1])-L+1>0)push(x,y+1);
				if(vis[x-1][y]!=T&&up[x-1][y]&&up[x][y]>=L)push(x-1,y);
				if(vis[x+1][y]!=T&&up[x+1][y]&&dn[x][y]>=L-1)push(x+1,y);
			}
		}
		inline void gt(int n,int*a,int*b,int m,int lim)
		{
			for(int i=n;i;i--)mn[i]=i%m?min(a[i],mn[i+1]):a[i];
			for(int i=1,t=lim;i<=n-m+1;i++){b[i]=min(t,mn[i]);t=i%m?min(t,a[i+m]):lim;}
			for(int i=n-m+2;i<=n;i++)b[i]=0;
		}
		inline int work(Query t)
		{
			int lx=t.xr-t.xl+1,ly=t.yr-t.yl+1,sz=n/lx;
			memset(up[sz+1],0,sizeof(up[sz+1]));memset(dn[sz+1],0,sizeof(dn[sz+1]));
			for(int i=1;i<=sz;i++)gt(m,Up[i*lx],up[i],ly,lx),gt(m,Dn[i*lx+1],dn[i],ly,lx-1);
			L=lx;ans=0;T++;bfs((t.xl-1)/lx+1,t.yl);return ans;
		}
	} 
	int main()
	{
		n = read<int>();m = read<int>();q = read<int>();
		W = sqrt(n) + 23;
		REP(i, 1, n)
		{
			scanf("%s", s[i] + 1);
			REP(j, 1, m) s[i][j] -= 48;
		}
		REP(i, 1, n) REP(j, 1, m) Up[i][j] = s[i][j] ? 0 : Up[i-1][j] + 1;
		DEP(i, n, 1) REP(j, 1, m) Dn[i][j] = s[i][j] ? 0 : Dn[i+1][j] + 1;
		REP(i, 1, q)
		{
			int xl(read<int>()), yl(read<int>()), xr(read<int>()), yr(read<int>());
			g[xr - xl + 1].emplace_back(xl, yl, xr, yr, i);
		}
		REP(i, 1, W) mark[i] = g[i].size() >= i;
		my_sol1::work();
		REP(i, 1, n) if (!mark[i])
			for (auto t : g[i]) ans[t.i] = sol2::work(t);
		REP(i, 1, q) cout << ans[i] << '\n';
		return 0;
	} 
}

int main()
{
#ifdef CraZYali
	file("C");
#endif
	return run::main();
}
