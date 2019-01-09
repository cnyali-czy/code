#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <queue>
#include <map>
#include <set>

using namespace std;
const int maxn = 500 + 5, maxm = 500 + 5, maxk = 500 + 5;

int m, n, k, s, t, t1, t2;

set <int> S[maxn];
set <int> :: iterator it;

inline int calc()
{
	int ans = 0;
	REP(i, 1, n)
		if (S[i].size())
		{
			it = S[i].begin();
			s = *it;
			it = S[i].end();it--;
			t = *it;
			ans += t - s + 1;
		}
	return ans;
}

int main()
{
#ifdef CraZYali
	freopen("d.in", "r", stdin);
	freopen("d.out", "w", stdout);
#endif
	scanf("%d %d %d\n", &n, &m, &k);
	REP(i, 1, n)
		REP(j, 1, m)
		{
			int opt;
			scanf("%1d", &opt);
			if (opt) S[i].insert(j);
		}
	while (k--)
	{
		int _max = -1, cho = -1;
		REP(i, 1, n) if (S[i].size())
		{
			int get;
			if (S[i].size() == 1) get = 1;
			else if (S[i].size() == 2)
			{
				it = S[i].begin();
				s = *it;
				it = S[i].end();
				it--;
				t = *it;
				get = t - s;
			}
			else
			{
				it = S[i].begin();
				s = *it;
				it++;
				t = *it;
				t1 = t - s;
	
				it = S[i].end();it--;
				t = *it;
				it--;
				s = *it;
				t2 = t - s;

				get = max(t1, t2);
			}
			if (_max < get)
			{
				_max = get;
				cho = i;
			}
		}
		if (cho == -1) break;
		int i = cho;
		if (S[i].size() <= 2) S[i].erase(S[i].begin());
		else
		{
			it = S[i].begin();
			s = *it;
			it++;
			t = *it;
			t1 = t - s + 1;

			it = S[i].end();it--;
			t = *it;
			it--;
			s = *it;
			t2 = t - s + 1;
			
			if (t1 > t2) S[i].erase(S[i].begin());
			else
			{
				it = S[i].end();
				it--;
				S[i].erase(it);
			}
		}
	}
	cout << calc() << endl;
	return 0;
}
