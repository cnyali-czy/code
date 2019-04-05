#define  REP(i, s, e) for(int i = s; i <= e; i++)
#define DREP(i, s, e) for(int i = s; i >= e; i--)

#include <iostream>
#include <cstdio>
#define int long long

using namespace std;
const int maxn = 50 + 5;

int read()
{
	int ans(0), flag(1);
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

int n, p[70], ans;

void insert(int x)
{
	DREP(i, 62, 0)
	{
		if (!(x & (1ll << i))) continue;
		if (!p[i])
		{
			p[i] = x;
			break;
		}
		x ^= p[i];
	}
}

signed main()
{
#ifdef CraZYali
	freopen("3812.in", "r", stdin);
	freopen("3812.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n) insert(read());
	DREP(i, 62, 0)
		if (ans < (ans ^ p[i])) ans ^= p[i];
	cout << ans << endl;
	return 0;
}
