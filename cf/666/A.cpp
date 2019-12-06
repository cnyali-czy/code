#define  REP(i, s, e) for (register int i(s); i <= e; i++)
#define DREP(i, s, e) for (register int i(s); i >= e; i--)

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <set>

using namespace std;
const int maxn = 1e4 + 10;

int n;
string str;
set <string> ans;

bool dp[maxn][4];

int main()
{
#ifdef CraZYali
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	cin >> str;
	n = str.size();
	reverse(str.begin(), str.end());
	if (n >= 7) dp[2][2] = 1;
	if (n >= 8) dp[3][3] = 1;
	REP(i, 3, n - 5)
	{
		dp[i][2] |= dp[i-2][3];
		if (i >= 4) dp[i][2] |= (dp[i-2][2] && str.substr(i-2, 2) != str.substr(i-4, 2));
		dp[i][3] |= dp[i-3][2];
		if (i >= 6) dp[i][3] |= (dp[i-3][3] && str.substr(i-3, 2) != str.substr(i-6, 2));
	}
	REP(i, 1, n)
	{
		if (dp[i][2])
		{
			string tmp = str.substr(i-2, 2);
			reverse(tmp.begin(), tmp.end());
			ans.insert(tmp);
		}
		if (dp[i][3])
		{
			string tmp = str.substr(i-3, 3);
			reverse(tmp.begin(), tmp.end());
			ans.insert(tmp);
		}
	}
	cout << ans.size() << endl;
	for (auto i : ans) cout << i << endl;
	return 0;
}
