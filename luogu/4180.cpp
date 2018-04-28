//50pts version
#define REP(i, s, e) for(register int i = s; i <= e ;i++)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 2000 + 10, maxm = 3000 + 10;

int m, n, k;

struct edeg
{
	int x, y, z;
}e[maxm];
inline bool cmp(edeg A, edeg B) {return A.z < B.z;}

int f[maxn];
int find(int x) {return x == f[x] ? f[x] : f[x] = find(f[x]);}

bool mark[maxm];

int main()
{
	freopen("4180.in", "r", stdin);
	freopen("4180.out", "w", stdout);
	cin >> n >> m;
	REP(i, 1, m)
	{
		register int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		e[i] = (edeg){x, y, z};
	}
	sort(e + 1, e + 1 + m ,cmp);
	REP(i, 1, n) f[i] = i;
	
	int al = 0, tot = 0;
	REP(i, 1, m)
		if (find(e[i].x) != find(e[i].y))
		{
			f[find(e[i].x)] = find(e[i].y);
			al++;
			mark[i] = 1;
			tot += e[i].z;
			if (al == n - 1) break;
		}
	int ans = (((1 << 30) - 1) << 1) + 1;
	REP(i, 1, m)
		if (mark[i])
		{
			REP(j, 1, n) f[j] = j;
			REP(j, 1, m)
				if (mark[j] && i ^ j) f[find(e[j].x)] = find(e[j].y);

			REP(j, 1, m)
				if (!mark[j] && find(e[j].x) ^ find(e[j].y) && e[i].z < e[j].z)
					chkmin(ans, tot - e[i].z + e[j].z);
		}
	cout << ans;
	return 0;
}
