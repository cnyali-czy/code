#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
const int maxn = 50 + 5, maxm = 50 + 5;

template <typename T> inline T read()
{
	T ans(0), flag(1);
	char c(getchar());
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}


int n;

string ssr[maxn], x[maxn], z[maxn];
int id[maxn];

int main()
{
#ifdef CraZYali
	freopen("dna.in", "r", stdin);
	freopen("dna.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n)
	{
		string &s = ssr[i];
		cin >> s;
		x[i] = s;
		REP(j, 1, s.size())
		{
			string cur = s.substr(0, j);
			string ccc = s.substr(j);
			bool flag(0);
			while (1)
				if (cur > ccc)
				{
					flag = 1;
					break;
				}
				else if (ccc.substr(0, cur.size()) == cur) ccc = ccc.substr(cur.size());
				else break;
			if (!flag)
			{
				x[i] = cur;
				z[i] = ccc;
				break;
			}
		}
		string qaq = x[i];
		while (qaq.size() < 50) qaq += x[i];
		x[i] = qaq.substr(0, 50);
	}
	REP(i, 1, n) id[i] = i;
	sort(id + 1, id + 1 + n, [&](int A, int B) {return x[A] > x[B] || x[A] == x[B] && (z[A] + 'Z') < (z[B] + 'Z');});
	string ans = "";
	REP(i, 1, n)
	{
		string last = ans;
		ans = "Z";
		REP(j, 1, ssr[id[i]].size()) chkmin(ans, ssr[id[i]].substr(0, j) + last);
	}
	cout << ans << endl;
	return 0;
}
