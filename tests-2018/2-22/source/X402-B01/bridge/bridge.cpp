#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <iostream>
#include <cstdio>
#include <map>

using namespace std;
const int maxn = 3000 + 10, maxm = 3000 + 10;

int m, n, k;
int flag, x0, y0, x1, y1;

inline int id(int y, int x) {return (y - 1) * n + x;}

#define node pair<int, int> 
#define A first
#define B second
map <node, int> exi;
node G[maxm << 2];

inline void add(int x, int y)
{
	if (x == y || exi[make_pair(x, y)] == 1) return;
	if (exi[make_pair(x, y)] == 0)
		exi[G[++k] = make_pair(x, y)] = 1;
	else exi[make_pair(x, y)] = 1;
}
inline void erase(int x, int y)
{
	if (x == y || exi[make_pair(x, y)] != 1) return;
	exi[make_pair(x, y)] = -1;
}

int f[maxn << 1];
inline int find(int x) {return f[x] == x ? f[x] : f[x] = find(f[x]);}
inline void uni(int x, int y) {f[find(x)] = find(y);}
inline void initSet() {REP(i, 1, 2 * n) f[i] = i;}

inline int query()
{
	int ans = 0, tot = 0;
	initSet();
	REP(i, 1, k) if (exi[G[i]]) uni(G[i].A, G[i].B);
	REP(i, 1, n * 2) tot += (f[i] == i);
	REP(i, 1, k)
		if (exi[G[i]] == 1)
		{
			int res = 0;
			initSet();
			REP(j, 1, k)
				if (i != j && exi[G[j]] == 1) uni(G[j].A, G[j].B);
			REP(j, 1, n * 2)
				if (f[j] == j) res++;
			if (res > tot) ans++;
		}
	return ans;
}

int main()
{
	freopen("bridge.in", "r", stdin);
	freopen("bridge.out", "w", stdout);
	scanf("%d%d", &n, &m);
	REP(i, 1, n)
	{
		add(id(1, i), id(2, i));
		if (i < n) add(id(1, i), id(1, i + 1)), add(id(2, i), id(2, i + 1));
	}
	REP(I, 1, m)
	{
		scanf("%d%d%d%d%d", &flag, &x0, &y0, &x1, &y1);
		int x = id(x0, y0);	int y = id(x1, y1);
		if (x > y) swap(x, y);
		if (flag == 1)	add(x, y);
		else 			erase(x, y);
		printf("%d\n", query());
	}

	return 0;
}
