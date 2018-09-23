#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;

const long long MOD = 1e9 + 9;

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

int m, n, k, h;

namespace bf
{
	const int maxn = 11;
	int choose[maxn];

	vector <int> v[5];

	int ans;

	int TOT;
	void dfs(int x)
	{
		if (x == n)
		{
			REP(i, 1, 4) vector <int> ().swap(v[i]);

			REP(i, 1, n)
				v[choose[i]].push_back(i);

			REP(i, 1, 4)
			{
				register int last = 0;
				register int siz = v[i].size() - 1;
				
				REP(j, 0, siz)
					if (v[i][j] - last > h) goto ne;
					else last = v[i][j];
				if (last + h >= n + 1)
				{
					ans++;
					return;
				}
ne:;
			}
			ans %= MOD;
			return;
		}
		x++;
		REP(i, 1, 4)
		{
			choose[x] = i;
			dfs(x);
		}
	}
	void work()
	{
		dfs(0);
		cout << ans;
	}
}
int main()
{
#ifdef CraZYali
	freopen("ladder.in", "r", stdin);
	freopen("ladder.out", "w", stdout);
#endif
	cin >> n >> h;
	if (n <= 10) bf::work();
	return 0;
}
