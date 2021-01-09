#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)

#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1 << 18 | 10;

int h, n, cnt[maxn];
int read() {int x;scanf("%d", &x);return x;}
int main()
{
	cin >> h;
	n = (1 << h) - 1;
	REP(i, 1, 420)
	{
		int u = rand() % n + 1, v = rand() % n + 1, w = rand() % n + 1;
		if (u == v || u == w || v == w)
		{
			i--;
			continue;
		}
		printf("? %d %d %d\n", u, v, w);fflush(stdout);
		cnt[read()]++;
	}
	static int id[maxn];
	REP(i, 1, n) id[i] = i;
	sort(id + 1, id + 1 + n, [&](int x, int y) {return cnt[x] > cnt[y];});
	int s1 = id[1], s2 = id[2];
	REP(i, 1, n) if (i ^ s1 && i ^ s2)
	{
		printf("? %d %d %d\n", s1, s2, i);fflush(stdout);
		if (read() == i)
		{
			cout << "! " << i << endl;
			return 0;
		}
	}
	return 0;
}
