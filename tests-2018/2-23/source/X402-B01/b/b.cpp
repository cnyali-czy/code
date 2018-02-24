#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 30, MOD = 1e9 + 7;

int n, k, ans, p;

int a[maxn];
bool vis[maxn];

vector <set <int> > v;
set <int> s;

inline void calc()
{
	v.clear();
	REP(i, 1, n)
	{
		int r = i + k - 1;
		if (r > n) break;
		REP(j, r, n)
		{
			s.clear();
			REP(q, i, j) s.insert(a[q]);
			if (s.size() < k) continue;
			else
			{
				register set <int> :: iterator it;
				it = s.begin();
				REP(hjfasdkljfhl, 1, k)
					it++;
				s.erase(it , s.end());
			}
			bool flag = 1;int si = v.size() - 1;
			REP(q, 0, si)
			{
				bool flag = 0;
				register set <int> :: iterator it;
				for (it = v[q].begin(); it != v[q].end(); it++)
					if (!s.count(*it))
					{
						flag = 1;
						goto thisok;
					}
				for (it = s.begin(); it != s.end(); it++)
					if (!v[q].count(*it))
					{
						flag = 1;
						goto thisok;
					}
			
thisok:			if (!flag) goto noway;
			}
			v.push_back(s);
		}
noway:;
	}
	if (v.size() == p)
	{
		ans++;
		ans %= MOD;
	}

}

inline void dfs(int x = 0)
{
	if (x == n)
	{
		calc();
		return;
	}
	x++;
	REP(i, 1, n)
		if (!vis[i])
		{
			vis[a[x] = i] = 1;
			dfs(x);
			vis[i] = 0;
		}
}

int main()
{
	freopen("b.in", "r", stdin);
	freopen("b.out", "w", stdout);
	cin >> n >> k >> p;
	if (n <= 8)
	{
		dfs();
		cout << ans % MOD;
	}
	else if (k == 1 && p == n)
	{
		int res = 1;
		REP(i, 1, n) res = (res * i) % MOD;
		cout << res;
	}
	else if (k == n && p == 1)
		cout << n;
	return 0;
}
