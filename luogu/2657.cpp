#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)

#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;
const int maxn = 15;

template <typename T> T read()
{
	T ans = 0, flag = 1;
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

int dp[maxn][maxn], a[maxn];
int work(int x)
{
	int len = 0, ans = 0;
	while(x)
	{
		a[++len] = x % 10;
		x /= 10;
	}
	REP(i, 1, len - 1)
		REP(j, 1, 9)
		ans += dp[i][j];
	REP(i, 1, a[len]-1) ans += dp[len][i];
	DREP(i, len - 1, 1)
	{
		REP(j, 0, a[i] - 1)
			if (abs(j-a[i+1])>=2)  ans+=dp[i][j]; 
		if(abs(a[i+1]  -a[i]) < 2) break;
	}
	return ans;
}
int main()
{
#ifdef CraZYali
	freopen("2657.in", "r", stdin);
	freopen("2657.out", "w", stdout);
#endif
	REP(i, 0, 9) dp[1][i] = 1;
	REP(i, 2, 10)
		REP(j, 0, 9)
		REP(k, 0, 9)
		if (abs(j-k) >= 2) dp[i][j] += dp[i-1][k];
	int x = read<int>(), y = read<int>();
	cout << work(y+1) - work(x) << endl;
	return 0;
}
