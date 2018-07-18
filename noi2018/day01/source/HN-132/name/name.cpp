#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxlen = 5e5 + 10;

int m, n, k, Q, l, r;

char S[maxlen], T[maxlen];
int lens, lent;

char temp[maxlen];

int nxt[maxlen];

inline bool chk(int L, int R)
{
	int len = R - L + 1;
	REP(i, 1, len) temp[i] = T[i - 1 + L];
	nxt[1] = 0;
	int k = 1;
	REP(i, 2, len)
	{
		while (k > 0 && temp[k + 1] != temp[i]) k = nxt[k];
		if (temp[k + 1] == temp[i]) k++;
		nxt[i] = k;
	}
	
	k = 1;
	REP(i, 1, lens)
	{
		while (k > 0 && temp[k + 1] != S[i]) k = nxt[k];
		if (temp[k + 1] == S[i]) k++;
		if (k == len) return 0;
	}
	return 1;
}

int main()
{
	freopen("name.in", "r", stdin);
	freopen("name.out", "w", stdout);
	scanf("%s", S + 1);
	lens = strlen(S + 1);
	cin >> Q;
	while (Q --> 0)
	{
		scanf("%s %d %d", T + 1, &l, &r);
		lent = strlen(T + 1);
		int ans = 0;
		REP(i, 1, lent)
		{
			int cnt = 0;
			int L = i, R = lent, KKK = -1;
			while (L <= R)
			{
				int mid = L + R >> 1;
				if (chk(i, mid))
				{
					KKK = mid;
					R = mid - 1;
				}
				else L = mid + 1;
			}
			if (KKK != -1) ans += lent - KKK + 1;
		}
		printf("%d\n", ans);
	}

	return 0;
}
