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
const int maxn = 1000;

int root, n, m;

int f[maxn + 10];
int find(int x) {return f[x] == x ? f[x] : f[x] = find(f[x]);}

set <int> S;
set <int> :: iterator it;

bool vis[maxn];

int main()
{
#ifdef CraZYali
	freopen("IsItATree.in", "r", stdin);
	freopen("IsItATree.out", "w", stdout);
#endif
	int x, y, Case(0);
	while (scanf("%d%d", &x, &y) && x != -1 && y != -1)
	{
		memset(vis, 0, sizeof(vis));
		S.clear();
		m = 0;
		bool flag = 1;
		REP(i, 1, maxn) f[i] = i;
		do
		{
			if (find(x) == find(y)) flag = 0;
			else f[find(x)] = find(y);
			if (vis[y]) flag = 0;
			S.insert(x);S.insert(y);
			vis[y] = 1;
			m++;
			scanf("%d%d", &x, &y);
		}while (x * y);
		n = S.size();
		if (m ^ (n - 1)) flag = 0;
		for (it = S.begin(); it != S.end() ; it++)
			if (find(*it) == *it) {root = *it;break;}
		for (it = S.begin(); it != S.end() ; it++)
			if (find(*it) ^ root) {flag = 0;break;}
		
		printf("Case %d is ", ++Case);
		if (!flag) printf("not ");
		printf("a tree.\n");
	}
	return 0;
}
