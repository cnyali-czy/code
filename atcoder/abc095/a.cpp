#include <bits/stdc++.h>

using namespace std;

int main()
{
#ifdef CraZYali
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
#endif
	long long ans = 700;
	register char c;
	while ((c = getchar()) != EOF && c ^ '\n')
		if (c == 'o') ans += 100;
	cout << ans;
	return 0;
}
