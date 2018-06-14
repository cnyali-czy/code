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

using namespace std;
const int maxn = 10000 + 10;

int m, n, k;

char c;

int score[maxn];

const unsigned long long X = 1e9 + 7;
unsigned long long Hash, spe;

string str;
map <string, int> id;
int main()
{
#ifdef CraZYali
	freopen("RankList.in", "r", stdin);
	freopen("RankList.out", "w", stdout);
#endif
	scanf("%d\n", &n);
	REP(i, 1, n)
	{
		getline(cin, str);
		id[str] = i;
	}
	int Li = id["Li Ming"];
	scanf("%d\n", &m);
	REP(i, 1, m)
	{
		REP(j, 1, n)
		{
			int temp;
			scanf("%d ", &temp);
			getline(cin, str);
			score[id[str]] += temp;
		}
		int ans = 1;
		REP(j, 1, n) if (score[j] > score[Li]) ans++;
		printf("%d\n", ans);		
	}
	return 0;
}
