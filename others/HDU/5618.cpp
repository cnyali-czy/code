#define  REP(i, s, e) for(int i = s; i <= e ;i++)
#define chkmin(a, b) a = min(a, b)
#include <bits/stdc++.h>
using namespace std;
const int maxn = 100000 + 10, maxk = 2000000;

int n, k = 100000;
struct flower
{
	int s, c, m, id;
	flower(){}
	flower(int _s, int _c, int _m, int _id) : s(_s), c(_c), m(_m), id(_id){}
}f[maxn];
bool cmp(flower A, flower B) {return A.s < B.s;}

vector <int> s[maxn];
void update(int c, int m)
{
	while (c <= k)
	{
		s[c].insert(lower_bound(s[c].begin(), s[c].end(), m), m);
		c += c & -c;
	}
}
int ans[maxn];
int query(int c, int m)
{
	int res = 0;
	while (c > 0)
	{
		res += lower_bound(s[c].begin(), s[c].end(), m+1) - s[c].begin();
		c -= c & -c;
	}
	return res-1;
}
int cnt[maxn];
int main()
{
#ifndef ONLINE_JUDGE
	freopen("5618.in", "r", stdin);
	freopen("5618.out", "w", stdout);
#endif
	int Case;
	cin >> Case;
	while (Case--)
	{
		scanf("%d", &n);
		REP(i, 1, n)
		{
			int s, c, m;
			scanf("%d%d%d", &s, &c, &m);
			f[i] = flower(s, c, m, i);
		}
		sort(f + 1, f + 1 + n, cmp);
		int last = 1;
		REP(i, 1, n)
		{
			if (i > 1 && f[i].s ^ f[i-1].s)
			{
				REP(j, last, i-1) ans[f[j].id] = query(f[j].c, f[j].m);
				last = i;
			}
			update(f[i].c, f[i].m);
		}
		REP(i, last, n) ans[f[i].id] = query(f[i].c, f[i].m);
		REP(i, 1, k) s[i].clear();
		REP(i, 1, n) printf("%d\n", ans[i]);
	}
	return 0;
}
