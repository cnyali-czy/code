#define DREP(i, s, e) for(register long long i = s; i >= e ;i--)
#define  REP(i, s, e) for(register long long i = s; i <= e ;i++)

#include <iostream>
#include <cstdio>
#include <set>

using namespace std;

long long n;
long long ans;

int main() {
#ifdef CraZYali
	freopen("11136.in", "r", stdin);
	freopen("11136.out", "w", stdout);
#endif
	ios::sync_with_stdio(false);
	while (cin >> n && n) {
		multiset <long long> S;
		multiset <long long> :: iterator s, e;
		ans = 0ll;
		REP(i, 1, n) {
			long long tn, k;
			cin >> tn;
			while (tn--) {
				cin >> k;
				S.insert(k);
			}
			s = S.begin();
			e = S.end();e--;
			ans -= *s - *e;
			S.erase(s);
			e = S.end();e--;
			S.erase(e);
		}
		cout << ans << '\n';
	}

	return 0;
}

