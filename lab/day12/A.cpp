#define REP(i, s, e) for (int i = s; i <= e; i++)

#include <bits/extc++.h>
#include <bits/stdc++.h>

using namespace std;
const int maxn = 50000 + 10, maxm = 10 + 5;
const unsigned long long P = 19260817;

int n, m;
char s[maxn], t[maxn];
__gnu_pbds::gp_hash_table <unsigned long long, bool> cnt;
char v[300];

int main()
{
#ifndef ONLINE_JUDGE
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	cin >> n >> m;
	scanf("%s", s + 1);
	REP(i, 1, n)
		REP(j, i, n)
		{
			int len = j - i + 1;
			copy(s + i, s + 1 + j, t + 1);
			REP(k, 1, len) v[t[k]] = 0;
			unsigned long long H(0);char cur = 'a';
			REP(k, 1, len)
			{
				if (!v[t[k]]) v[t[k]] = cur++;
				t[k] = v[t[k]];
			}
			REP(k, 1, len) H = H * P + t[k];
			cnt[H] = 1;
		}
	cout << cnt.size() << endl;
	return 0;
}
