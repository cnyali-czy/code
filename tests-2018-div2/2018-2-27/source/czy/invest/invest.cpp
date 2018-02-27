#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 100000 + 10;

template <typename T> T read()
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

int m, n, k, a[maxn];

inline int turn(string s)
{
	int len = s.size() - 1, res = 0;
	REP(i, 0, len) res = res * 10 + s[i] - 48;
	return res;
}
int b[maxn];

int main()
{
	freopen("invest.in", "r", stdin);
	freopen("invest.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin >> n;
	REP(i, 1, n) cin >> a[i];
	while (1)
	{
		string t;
		cin >> t;
		if (t[0] == 'E') return 0;
		else if (t[0] == 'R')
		{
			int Max = b[1], cho = 1;
			REP(i, 2, n)
				if (b[i] > Max)
				{
					Max = b[i];
					cho = i;
				}
			cout << cho << ' ' ;
			int Maxx = 0, cho2 = 2;
			REP(i, 1, n)
				if (i ^ cho && b[i] > Maxx)
				{
					Maxx = b[i];
					cho2 = i;
				}
			cout << cho2 << endl;
		}
		else
		{
			int x(turn(t)), y;
			cin >> y;
			b[x] = y - a[x];
			a[x] = y;
		}
	}

	return 0;
}

