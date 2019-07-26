#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)

#include <bits/extc++.h>
#include <iostream>
#include <cstdio>
using namespace std;
const int maxn = 5000 + 5, maxm = maxn;

int n, m;
char s[100000 + 10];

const unsigned long long P = 19260817;
unsigned long long *Hash[maxn][2];
#define mid (l + r >> 1)

#define t(j) s[i+ j -1]

namespace very_sMall
{
	const int maxm = 100 + 5;
	unsigned long long Hash[maxm];
	__gnu_pbds::gp_hash_table <unsigned long long, int> last, cnt;
	__gnu_pbds::gp_hash_table <unsigned long long, bool> need;
	unsigned long long bin[maxm];
	int siz[4];
	char c[] = {'A','T','G','C'};
	void work()
	{
		REP(i, 1, n - m + 1)
		{
			unsigned long long H = 0;
			REP(j, 1, m) H = H * P + t(j);
			need[H] = 1;
		}
		bin[0] = 1;
		REP(i, 1, m) bin[i] = bin[i-1] * P;
		REP(i, 1, n - m + 1)
		{
			DREP(j, m, 1) Hash[j] = Hash[j+1] + t(j) * bin[m-j];
			unsigned long long HH(0);
			REP(j, 1, m)
			{
				if (j > 1) HH = HH * P + t(j-1);
				REP(k, 0, 3)
				{
					unsigned long long H = (HH * P + c[k]) * bin[m-j] + Hash[j+1];
					/*
					printf("%llu:\t", H);
					REP(P,1,j-1)putchar(t(P));
					putchar(c[k]);
					REP(P,j+1,m)putchar(t(P));putchar(10);
					*/
					if (need.find(H)!=need.end() && last[H]^i)last[H]=i,cnt[H]++;
				}
			}
		}
		REP(i, 1, n - m + 1)
		{
			unsigned long long H = 0;
			REP(j, 1, m) H = H * P + t(j);
			printf("%d%c", (int)cnt[H] - 1, i == n - m + 1 ? '\n' : ' ');
		}
	}
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif
	cin >> n >> m;
	scanf("%s", s + 1);
	if (m <= 100) very_sMall::work();
	else
	{
		REP(i, 1, n-m+1) Hash[i][0] = new unsigned long long[m+5], Hash[i][1] = new unsigned long long[m+5];
		REP(i, 1, n - m + 1)
		{
			REP(j, 1, m)	Hash[i][0][j] = Hash[i][0][j-1] * P + t(j);
			DREP(j, m, 1)	Hash[i][1][j] = Hash[i][1][j+1] * P + t(j);
		}
		REP(i, 1, n - m + 1)
		{
			int ans(0);
			REP(j, 1, n - m + 1)
				if (i ^ j)
				{
					int l, r, pos;
					l = 0, r = m, pos;
					while (l <= r)
						if (Hash[i][0][mid] == Hash[j][0][mid])
						{
							pos = mid;
							l = mid + 1;
						}
						else r = mid - 1;
					ans += Hash[i][1][mid+2] == Hash[j][1][mid+2];
				}
			printf("%d%c", ans, i == n - m + 1 ? '\n' : ' ');
		}
	}
	return 0;
}
