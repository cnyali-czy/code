#define REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <map>
#include <cmath>

using namespace std;

template <typename T> T read()
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

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

int n;
string P, S;
void output(string S, string End = "\n", FILE *F = stderr)
{
	REP(i, 0, S.size() - 1) fprintf(F, "%c", S[i] + '0');
	fprintf(F, "%s", End.c_str());
}
#include <unordered_map>
unordered_map <string, bool> Map;
int blg[8];
int ans;
bool vis[1 << 15];

int calc(string x)
{
	if (x.size() == 1) return x[0];
	if (Map.count(x)) return Map[x];
	string pre = "";
	REP(i, 0, x.size() - 3)
	{
		int qaq = 0;
		qaq += x[i] + 2 * x[i + 1] + 4 * x[i + 2];
		string New = pre + (char)blg[qaq] + x.substr(i + 3);
		if (calc(New)) return Map[x] = 1;
		pre += x[i];
	}
	return Map[x] = 0;
}

void dfs(int x, string cur)
{
	if (x == n) ans += calc(cur);
	else
	{
		x++;
		cur += 'a';
		if (S[x] == '?')
			REP(i, 0, 1)
			{
				cur[x] = i;
				dfs(x, cur);
			}
		else
		{
			cur[x] = S[x];
			dfs(x, cur);
		}
	}
}

namespace Sub2
{
	void work()
	{
		bool flag = 1;
		ans = 1;
		REP(i, 0, n) if (S[i] == '?') ans <<= 1;
		else if (S[i] == '1') flag = 0;
		cout << ans - flag << '\n';
	}
}

int main()
{
#ifdef CraZYali
	file("C");
//	freopen("C.err", "w", stderr);
#endif
	register int T = read<int>();
	while (T--)
	{
		cin >> P >> S;
		n = S.size() - 1;
		if (P == "01111111") {Sub2 :: work();continue;}
		REP(i, 0, 7) P[i] -= '0';
		REP(i, 0, n) if (S[i] != '?') S[i] -= '0';
		Map.clear();
		REP(x0, 0, 1)
			REP(x1, 0, 1)
			REP(x2, 0, 1)
			{
				string tmp = "";
				tmp += (char)x0;// + '0';
				tmp += (char)x1;// + '0';
				tmp += (char)x2;// + '0';
				int qaq = x0 + 2 * x1 + 4 * x2;
				bool flag = P[x0 + 2 * x1 + 4 * x2];
				blg[qaq] = flag;
			}
			ans = 0;
			dfs(-1, "");
			cout << ans << '\n';
	}
	return 0;
}
