/*
	Problem:	A.cpp
	Time:		2020-02-20 16:21
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <unordered_map>
#include <bitset>
#include <map>
#include <unordered_set>
#include <cmath>
#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e4 + 10, maxm = maxn * 3;
const double eps = 1e-8, pi = acos(-1);

int bg[maxn], ne[maxm << 1], to[maxm << 1], e, deg[maxn];
double w[maxm << 1];
inline void add(int x, int y, double z)
{
	deg[x]++;deg[y]++;
	e++;
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

int n, m;
vector <pair <int, double> > G[maxn];

const unsigned long long base = 1e9 + 7;
struct cmp
{
	inline unsigned long long operator () (const pair <int, int> &A) const {return A.first * base + A.second;}
};
unordered_set <pair <int, int>, cmp > S;

bool vis[maxn];
struct Complex
{
	double x, y;
	inline Complex(double x = 0, double y = 0) : x(x), y(y) {}
	inline Complex operator - (const Complex &B) {return Complex(x - B.x, y - B.y);}
	inline Complex operator + (const Complex &B) {return Complex(x + B.x, y + B.y);}
	inline Complex operator * (const Complex &B) {return Complex(x * B.x - y * B.y, x * B.y + y * B.x);}
	inline Complex operator *=(const Complex &B) {return *this = *this * B;}
}p[maxn];
#define Point Complex

inline double sqr(double x) {return x * x;}
inline double dis(double x1, double y1, double x2, double y2) {return sqrt(sqr(x1 - x2) + sqr(y1 - y2));}
inline double dis2(double x1, double y1, double x2, double y2) {return sqr(x1 - x2) + sqr(y1 - y2);}
inline double dis(Point A, Point B) {return dis(A.x, A.y, B.x, B.y);}
void work(int p1, int p2)
{
	const double l0 = dis(p[p1], p[p2]);
	for (auto to : G[p1])
	{
		int p3 = to.first;double l1 = to.second;
		if (vis[p3]) continue;
		if (S.find(make_pair(p2, p3)) == S.end()) continue;
		vis[p3] = 1;
		double l2 = dis(p[p3], p[p2]);
		double theta = acos((sqr(l0) + sqr(l1) - sqr(l2)) / 2 / l0 / l1);
		Complex qaq = Complex(l1 / l0 * cos(theta), l1 / l0 * sin(theta));
		p[p3] = qaq * (p[p2] - p[p1]) + p[p1];
		if (p[p3].y < eps)
		{
			theta = pi + pi - theta;
			qaq = Complex(l1 / l0 * cos(theta), l1 / l0 * sin(theta));
			p[p3] = qaq * (p[p2] - p[p1]) + p[p1];
		}
		printf("%d %d to solve %d:\n", p1, p2, p3);
		printf("(%.0lf, %.0lf) (%.0lf, %.0lf) %.2lf %.2lf %.2lf, theta = %.2lf --> (%.0lf, %.0lf)\n", p[p1].x, p[p1].y, p[p2].x, p[p2].y, l0, l1, l2, theta, p[p3].x, p[p3].y);
		work(p1, p3);work(p2, p3);
	}
}

namespace run
{
	const int N = 1e4 + 10;
	int t, n, m, deg[N];
	vector <int> q[N];
	bitset <N> g[N], vis2[N];
	bool vis1[N];
	unordered_map<int, double> l[N];
	struct pnt
	{
		double x,y;
		pnt(double x=0,double y=0):x(x),y(y){}
		pnt operator + (const pnt &w) const{
			return pnt(x+w.x,y+w.y);
		}
		pnt operator - (const pnt &w) const{
			return pnt(x-w.x,y-w.y);
		}
		pnt operator / (const double &w) const{
			return pnt(x/w,y/w);
		}
		double operator * (const pnt &w) const{
			return x*w.y-y*w.x;
		}
		double operator ^ (const pnt &w) const{
			return x*w.x+y*w.y;
		}
		pnt getint() const{
			return pnt(floor(x+eps),floor(y+eps));
		}
	}a[N];

	double sqr(double x){return x*x;}

	double calc(int x,int y,int z){
		return (a[y]-a[x])*(a[z]-a[x]);
	}

	pnt cpt(int x,int y,int z){
		pnt u=a[x],v=a[y],t=v-u;
		double d1=l[x][y],d2=l[x][z],d3=l[y][z];
		double Cos=(sqr(d1)+sqr(d2)-sqr(d3))/(2*d1*d2),Sin=sqrt(1-sqr(Cos));
		t=pnt(t*pnt(Sin,Cos),t^pnt(Sin,Cos));
		t=t/(d1/d2);
		return (u+t).getint();
	}

	void solve(int x,int y){
		if (vis2[x][y]) return; vis2[x][y]=1;
		int xx=x,yy=y;
		if (deg[xx]>deg[yy]) swap(xx,yy);
		double s=1e20; int k=0;
		for (int z:q[xx]){
			if (g[yy][z]){
				if (!vis1[z]){vis1[z]=1; a[z]=cpt(x,y,z);}
				double t=calc(x,y,z);
				if (t<0) continue;
				if (t<s){s=t; k=z;}
			}
		}
		if (!k) return;
		solve(x,k); solve(k,y);
	}

	void ins(int x,int y,double d){
		g[x][y]=g[y][x]=1;
		l[x][y]=l[y][x]=d;
		q[x].push_back(y); q[y].push_back(x);
		++deg[x]; ++deg[y];
	}

	int main(){
		scanf("%d",&t);
		while (t--){
			scanf("%d%d",&n,&m);
			for (int i=1;i<=m;++i){
				int x,y; double d;
				scanf("%d%d%lf",&x,&y,&d);
				ins(x,y,d);
				if (i==1){a[1]=pnt(0,0); a[2]=pnt(d,0);}
			}
			vis1[1]=vis1[2]=1; solve(1,2);
			for (int i=1;i<=n;++i) printf("%.0lf %.0lf\n",a[i].x,a[i].y);
			puts("");
			for (int i=1;i<=n;++i){
				vis1[i]=0; vis2[i].reset(); g[i].reset(); l[i].clear(); q[i].clear(); deg[i]=0;
			}
		}
		return 0;
	}

}

int main()
{
#ifdef CraZYali
	file("A");
#endif
	return run::main();
	register int T = read<int>();
	while (T--)
	{
		n = read<int>();m = read<int>();
		REP(i, 1, n) G[i].clear(), vis[i] = bg[i] = deg[i] = 0;e = 0;
		S.clear();
		while (m--)
		{
			int x(read<int>()), y(read<int>());double z;scanf("%lf", &z);
			add(x, y, z);add(y, x, z);
			S.emplace(x, y);S.emplace(y, x);
			if (x + y == 3) p[2] = Complex(z, 0);
		}
		REP(x, 1, n) for (int i = bg[x]; i; i = ne[i]) if (deg[x] >= deg[to[i]]) G[x].emplace_back(to[i], w[i]);
		vis[1] = vis[2] = 1;
		work(1, 2);
		REP(i, 1, n) printf("%d %d\n", (int)(eps + p[i].x), (int)(eps + p[i].y));
		puts("");
	}
	return 0;
}
