#define REP(i, s, e) for (int i = s; i <= e ; i++)

#include<bits/stdc++.h>

using namespace std;
const int maxn = 300 + 5;

int n, ans, h[maxn], a[maxn], b[maxn];
bool judge()
{
	REP(i, 1, n)
	{
		int l(i), r(i);
		while (l > 1 && h[l-1] <= h[i])
			l--;
		while (r < n && h[r+1] < h[i])
			r++;
		if(abs(i - l - (r - i)) > 2) return 0;
	}
	return 1;
}
void dfs(int x)
{
	if (x == n) ans += judge();
	else
	{
		x++;
		REP(i, a[x], b[x])
		{
			h[x] = i;
			dfs(x);
		}
	}
}
int main()
{
	freopen("robot.in","r",stdin);
	freopen("robot.out","w",stdout);
	cin >> n;
	REP(i, 1, n) scanf("%d%d", a + i, b + i);
	dfs(0);
	cout << ans << endl;
	return 0;
}
