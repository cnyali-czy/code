#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 1000000 + 10, maxk = 2000000;

template <typename T> inline T read()
{
	T ans(0), p(1);
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}

int n, k;
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
	//	REP(i, c, cmax)s[i].insert(lower_bound(s[i].begin(), s[i].end(), m), m);
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
#ifdef CraZYali
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
	freopen("B.err", "w", stderr);
#endif
	cin >> n >> k;
	REP(i, 1, n)
	{
		int s(read<int>()), c(read<int>()), m(read<int>());
		f[i] = flower(s, c, m, i);
	}
	sort(f + 1, f + 1 + n, cmp);
	//	REP(i, 1, n) printf("%d %d %d %d\n", f[i].s, f[i].c, f[i].m, f[i].id);

	int last = 1;
	REP(i, 1, n)
	{
		if (i > 1 && f[i].s ^ f[i-1].s)
		{
			REP(j, last, i-1)
				cnt[ans[f[j].id] = query(f[j].c, f[j].m)]++;//, puts("----"), cerr << f[i].id << ' ' << ans[f[i].id] << endl;
			last = i;
		}
		update(f[i].c, f[i].m);
	}
	REP(i, last, n) cnt[ans[f[i].id] = query(f[i].c, f[i].m)]++;//, puts("----"), cerr << f[i].id << ' ' << ans[f[i].id] << endl;
	REP(i, 0, n-1) printf("%d\n", cnt[i]);
	//	REP(i, 1, n) fprintf(stderr, "%d\n", ans[i]);
	return 0;
}
