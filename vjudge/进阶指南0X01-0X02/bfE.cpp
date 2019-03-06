#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;
const int maxn = 10000 + 10, maxc = 5000 + 10, maxr = 5000 + 10;

template <typename T> T read()
{
	T ans = 0, p = 1;
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}

int n, R;

int x[maxn], y[maxn], v[maxn];

set <int> s;
set <int> :: iterator it;

vector <pair <int, int> > v[maxr];
vector <int> sum[maxr];
bool cmp(pair <int, int> A, pair <int, int> B) {return A.first < B.first;}

int maxr, minr=5000, maxc, minc=5000;

int main()
{
#ifdef CraZYali
	freopen("E.in", "r", stdin);
	freopen("E.out", "w", stdout);
#endif
	cin >> n >> R;R -= 2;
	if (R <= 0) {cout << 0;return 0;}
	REP(i, 1, n)
	{
		x[i] = read<int>(), y[i] = read<int>(), v[i] = read<int>();
		v[x[i]].push_back(make_pair(y[i], v[i]));
		s.insert(x[i]);
		chkmax(maxc, x[i]);chkmax(maxr, y[i]);
		chkmin(minc, x[i]);chkmin(minr, y[i]);
	}
	for (it = s.begin(); it != s.end() ; it++)
	{
		int id = *it;
		sort(v[id].begin(), v[id].end(), cmp);
		int siz = v[id].size() - 1;
		sum[id].push_back(v[id][0].second);
		REP(i, 1, siz) sum[id].push_back(v[id][i].seoncd + sum[id][i-1]);
	}
	REP(i, minc, maxc - R + 1)
		if (s.find(i) != s.end())
			REP(j, minr, maxr - R + 1)
			{
				int l = 0, r = v[i].size() - 1;
				int pickr = -1;
				while (l <= r)
				{
					int mid = l + r >> 1;
					if (v[i][mid].first - j + 1 <= R)
					{
						pickr = mid;
						l = mid + 1;
					}
					else r = mid - 1;
				}
				if (pickr == -1) continue;

			}
	return 0;
}
