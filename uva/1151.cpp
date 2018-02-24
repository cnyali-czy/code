#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define dist(x1, y1, x2, y2) ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2))
#define chkmin(a, b) a = min(a, b)
#define DEBUG fprintf(stderr, "Passing [%s] in line %d\n", __FUNCTION__, __LINE__);

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <vector>
#include <set>

using namespace std;
const int maxn = 1010, maxm = 10;

template <typename T> T read() {
	T ans(0), p(1);
	char c = getchar();
	while (!isdigit(c)) {
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c)) {
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}
struct pack {
	int siz, cost;
	set <int> c;
}a[maxm];

int m, n, k;
int _x[maxn], _y[maxn];

struct edeg {
	int x, y;
	int z, xz;
	bool chosen, cc;
}think[maxn], e[maxn * maxn / 2];
inline bool cmp(edeg A, edeg B) {return A.z < B.z;}

inline void Read() {
	n = read<int>();
	m = read<int>();
	REP(i, 1, m) {
		a[i].siz = read<int>();
		a[i].cost = read<int>();
		a[i].c.clear();
		REP(j, 1, a[i].siz) a[i].c.insert(read<int>());
	}
	REP(i, 1, n)
		_x[i] = read<int>(),
		_y[i] = read<int>();
	k = 0;
	REP(i, 1, n)
		REP(j, i + 1, n) {
			k++;
			e[k].x = i;
			e[k].y = j;
			e[k].z = dist(_x[i], _y[i], _x[j], _y[j]);
			e[k].chosen = e[k].cc = 0;
		}	
}
struct Set {
	int f[maxn];
	inline void init() {REP(i, 1, n) f[i] = i;}
	inline int find(int x) {return f[x] == x ? f[x] : f[x] = find(f[x]);}
}s;

inline int Kruskal() {
	sort(e + 1, e + 1 + k, cmp);
	s.init();
	register int res = 0;
	register int already = 0;
	REP(i, 1, k) {
		register int fx = s.find(e[i].x);
		register int fy = s.find(e[i].y);
		if (fx != fy) {
			s.f[fx] = fy;
			res += e[i].z;
			e[i].chosen = 1;
			already++;
			if (already == n - 1) return res;
		}
	}
	return -1.0;
}

bool vis[maxm];

inline bool judge() {
	register int judge(0);
	REP(i, 1, m)
		judge += vis[i];
	return judge;
}

int ans;
inline void dfs(int x) {
	if (x == m) {
		if (!judge()) return;
		register int res = 0, now = 0;
		s.init();
		REP(i, 1, m) if (vis[i]) {
			res += a[i].cost;
			REP(j, 1, k) if (a[i].c.count(e[j].x) && a[i].c.count(e[j].y)) {
				register int fx = s.find(e[j].x);
				register int fy = s.find(e[j].y);
				if (fx ^ fy) {
					s.f[fx] = fy;
					now++;
					if (now == n - 1) {chkmin(ans, res);break;}
				}
			}
		}
		if (now < n - 1)
			REP(i, 1, n - 1) {
				register int fx = s.find(think[i].x);
				register int fy = s.find(think[i].y);
				if (fx ^ fy) {
					s.f[fx] = fy;
					res += think[i].z;
					now++;
					if (now == n - 1) {chkmin(ans, res);break;}
				}
			}
		return;
	}
	x++;
	vis[x] = 1;
	dfs(x);
	vis[x] = 0;
	dfs(x);
}

inline void work() {
	Read();
	ans = Kruskal();register int temp = 0;
	REP(i, 1, k)
		if (e[i].chosen) think[++temp] = e[i];
	dfs(0);
	printf("%d\n", ans);
}

int main() {
#ifdef CraZYali
	freopen("submit.in", "r", stdin);
	freopen("submit.out", "w", stdout);
#endif
	register int T = read<int>();
	while (--T) work(), putchar('\n');
	work();
	return 0;
}
