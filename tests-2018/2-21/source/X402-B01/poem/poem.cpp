#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 1e5 + 10;

int m, n, k;
string s[maxn];

int acc[maxn], len[maxn], res;

inline void gen(int x, int i, string now = "")
{
	if (x >= len[i]) return;
	x++;
	REP(j, 1, 26)
	{
		register string temp = now + (char)(j + 'a' - 1);
		register int lene = temp.size(), pos = 0;
		while ((pos = s[i].find(temp, pos)) != string::npos)
		{
			res++;
			pos += lene;
		}
		gen(x, i, temp);
	}
}

int main()
{
	freopen("poem.in", "r", stdin);
	freopen("poem.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin >> n;
	REP(i, 1, n)
	{
		cin >> s[i];
		len[i] = s[i].size();
	}
	int ans = 0;
	REP(i, 1, n)
	{
		int Tres = 0;
		REP(j, 1, i)
		{
			res = 0;
			gen(0, j);
			Tres += res;
		}
		cout << (ans += Tres) << endl;
	}
	return 0;
}
