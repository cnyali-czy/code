#define REP(i, s, e) for(register int i = s; i <= e ;i++)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 100;

int m, n, k;

int s[maxn];
char s1[maxn], s2[maxn];

int main()
{
	
	freopen("task.in", "r", stdin);
	freopen("task.out", "w", stdout);
	
	cin >> n;
	REP(i, 1, n) scanf("%d", s + i);
	int ans = 0;
	scanf("%s\n%s", s1 + 1, s2 + 1);
	REP(i, 1, n) ans += s[i] * (s1[i] == s2[i]);
	cout << ans << endl;
	REP(i, 1, n)
		if (s1[i] == s2[i]) printf("Accepted\n");
		else printf("Wrong Answer\n");
	return 0;
}
