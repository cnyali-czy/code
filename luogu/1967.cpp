#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 100000 + 10, maxm = 50000 + 10;

int bg[maxn], ne[maxm << 1], to[maxm << 1], w[maxm << 1], e = 1;
void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
}

#define edge pair<pair<int, int>, int>
edge E[maxm];
bool cmp(edge A, edge b) {return A.second > B.second;}

int fa[maxn];
int find(int x) {return f[x] == x ? f[x] : f[x] = find(f[x]);}

bool mark[maxn];

int m, n, q, x, y;

int main()
{
#ifdef CraZYali
	freopen("1967.in", "r", stdin);
	freopen("1967.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, m)
		scanf("%d%d%d", &E[i].first.first, &E[i].first.second, &E[i].second);
	
	REP(i, 1, n) fa[i] = i;
	sort(E + 1, E + 1 + m, cmp);
	int al(0);
	REP(i, 1, m)
	{
		x = find(E[i].first.first);
		y = find(E[i].first.second);
		if (fx ^ fy)
		{
			mark[E[i].first.first] = 1;
			mark[E[i].first.second] = 1;
			f[x] = y;
			al++;
			if (al == n - 1) break;
		}
	}

	REP(i, 1, m)
		if (mark[E[i].first.first] && mark[E[i].first.second]) 
		{
			add(E[i].first.first, E[i].first.second, E[i].second);
			add(E[i].first.second, E[i].first.first, E[i].second);
		}

	cin >> q;
	
	return 0;
}
