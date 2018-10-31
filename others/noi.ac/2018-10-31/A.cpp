#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 1500 + 10, maxm = 1500 + 10;

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

template <typename T> void write(T x)
{
	if (x < 0) putchar('-'), write(-x);
	else if (x / 10) write(x / 10);
	putchar(x % 10 + '0');
}

int m, n, k, temp;
bool vis[maxn][maxm];char s[maxm];

set <pair <int, int> > S;
set <pair <int, int> > :: iterator it;

struct node {int opt, pos, b, c;node (int _opt, int _pos, int _b, int _c) : opt(_opt), pos(_pos), b(_b), c(_c){};};
vector <node> v;

int main()
{
#ifdef CraZYali
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, n)
	{
		scanf("%s", s + 1);
		REP(j, 1, m)
		{
			vis[i][j] = (s[j] == '#');
			if (!vis[i][j]) S.insert(make_pair(i, j)), ++k;
		}
	}
	bool flag = 1;
	while (k > 0 && flag)
	{
		flag = 0;
		for (it = S.begin(); it != S.end() ; it++)
		{
			register int x = it -> first, y = it -> second;
			register int l, r;
			l = r = y;
			while (l > 1 && r < m)
			{
				l--;r++;
				if (vis[x][l] && vis[x][r])
				{
					vis[x][y] = 1;
					flag = 1;
					v.push_back(node(1, x, l, r));
					S.erase(it);
					k--;
					goto ne;
				}
			}
			l = r = x;
			while (l > 1 && r < n)
			{
				l--;r++;
				if (vis[l][y] && vis[r][y])
				{
					vis[x][y] = 1;
					flag = 1;
					v.push_back(node(2, y, l, r));
					S.erase(it);
					k--;
					goto ne;
				}
			}
ne:;
		}
//		REP(i, 1, n)REP(j,1,m)printf("%d%c",vis[i][j],j==m?'\n':' ');
	}
	int siz = v.size() - 1;
	cout << siz + 1 << endl;
	REP(i, 0, siz) printf("%d %d %d %d\n", v[i].opt, v[i].pos, v[i].b, v[i].c);
	return 0;
}
