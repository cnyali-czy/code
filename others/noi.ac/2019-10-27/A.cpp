#define  REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
#include <vector>

using namespace std;

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

int T, opt, qaq;
string x, y;
pair <string, string> lst[3];
map <string, int> ade02;


int main()
{
#ifdef CraZYali
	file("A");
#endif
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> T;
	REP(Case, 1, T)
	{
		cin >> opt;
		switch (opt)
		{
			case 1:
				cin >> x >> y;
				if (Case >= 3 && lst[1] == lst[2] && lst[1] == make_pair(x, y)) ade02[x]++;
				if (y == "thanks" && ade02.find(lst[1].first) != ade02.end() && ade02[lst[1].first]) ade02[lst[1].first]--;
				lst[2] = lst[1];
				lst[1] = make_pair(x, y);
				break;
			case 2:
				cin >> opt;
				while (opt--)
				{
					cin >> x;
					if (ade02.find(x) != ade02.end() && ade02[x]) ade02[x]--;
				}
				break;
		}
	}
	bool flag(0);
	for (auto i : ade02) if (i.second)
	{
		flag = 1;
		cout << i.first << ' ' << i.second << endl;
	}
	if (!flag) puts("None");
	return 0;
}
