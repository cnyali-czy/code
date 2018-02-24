#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 120010;

template <typename T> T read() {
	T ans(0), p(1);
	char c = getchar();
	while (!isdigit(c)) {
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c)) {
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}

int m, n, k;
string s[maxn];
set <string> S;

int main() {
#ifdef CraZYali
	freopen("10391.in", "r", stdin);
	freopen("10391.out", "w", stdout);
#endif
	ios::sync_with_stdio(false);
	while (cin >> s[++n]) S.insert(s[n]);n--;
	REP(i, 1, n) {
		register int len = s[i].size() - 1;
		REP(j, 1, len)
			if (S.count(s[i].substr(0, j)) && S.count(s[i].substr(j, len + 1 - j))) {cout << s[i] << endl;break;}
	}
	return 0;
}
