#define REP(i, s, e) for (int i = s; i <= e ; i++)

#include <bits/stdc++.h>
#define int unsigned long long
using namespace std;
const int maxn = 100 + 5, maxlen = 1e6 + 10, P = 1e9 + 7;

unordered_map <int, bool> cnt;
int n, Hash[maxlen];
char s[maxlen];

int power_pow(int a, int b)
{
	int ans = 1, base = a;
	while (b)
	{
		if (b & 1) ans *= base;
		base *= base;
		b >>= 1;
	}
	return ans;
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif
	scanf("%s", s + 1);
	int len = strlen(s + 1);
	REP(i, len + 1, len + len) s[i] = s[i-len];
	REP(i, 1, len + len) Hash[i] = Hash[i-1] * P + s[i];
	int PP = power_pow(P, len);
	REP(i, 1, len) cnt[Hash[i + len - 1] - Hash[i-1] * PP] = 1;
	cin >> n;
	while (n--)
	{
		scanf("%s", s + 1);
		int Len = strlen(s + 1), ans(0);
		REP(i, 1, Len) Hash[i] = Hash[i-1] * P + s[i];
		if (Len >= len) REP(i, 1, Len - len + 1) ans += cnt[Hash[i + len - 1] - Hash[i-1] * PP];
		printf("%llu\n", ans);
	}
	return 0;
}
