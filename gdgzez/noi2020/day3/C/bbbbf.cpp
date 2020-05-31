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
#include <queue>
#include <vector>
#include <map>
#include <cmath>

using namespace std;
const int maxn = 1000, MOD = 1e9 + 7;

inline void inc(int &x, int y) {x += y;if (x >= MOD) x -= MOD;}

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

int calc(string x)
{
	if (x.size() == 1) return x[0];
	if (x.size() % 2 == 0) return 0;
	if (Map.count(x)) return Map[x];
	string pre = "";
	REP(i, 0, x.size() - 3)
	{
		int qaq = 0;
		qaq += x[i] + 2 * x[i + 1] + 4 * x[i + 2];
//		cerr << "qaq = " << qaq << endl;
		assert(qaq<8);
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

string str[maxn];
int cur;

vector <string> totst;

struct __init__
{
	__init__()
	{
		totst.emplace_back("");
		for (int len = 1; len <= 10; len++)
		{
			REP(i, 0, (1 << len) - 1)
			{
				string cur = "";
				REP(j, 0, len - 1) cur += (char)(i >> j & 1);
				totst.emplace_back(cur);
			}
		}
		for (auto i : totst) output(i);
	}
}__INIT__;
map <pair <string, string>, bool> Mem2;
bool same(string a, string b)
{
	if ((a.size() & 1) ^ (b.size() & 1)) return 0;
	if (a > b) swap(a, b);
	if (Mem2.count(make_pair(a, b))) return Mem2[make_pair(a, b)];
	for (auto i : totst) if ((i.size() + a.size()) % 2 == 1 && calc(a + i) != calc(b + i)) return Mem2[make_pair(a, b)] = 0;
	return Mem2[make_pair(a, b)] = 1;
}
int trans[maxn][2], dp[maxn][maxn];
string turn(string x) {REP(i,0,x.size()-1)x[i]-='0';return x;}
string back(string x) {REP(i,0,x.size()-1)x[i]+='0';return x;}
int main()
{
#ifdef CraZYali
	file("C");
	freopen("C.err", "w", stderr);
#endif
	register int T = read<int>();
	while (T--)
	{
		cin >> P >> S;
		n = S.size() - 1;
		REP(i, 0, 7) P[i] -= '0';
		REP(i, 0, n) if (S[i] != '?') S[i] -= '0';
		Map.clear();Mem2.clear();
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
		REP(i, 0, cur) trans[i][0] = trans[i][1] = 0;
		cur = 0;
//		str[++cur] = "1";str[cur][0] -= '0';
//		str[++cur] = "0";str[cur][0] -= '0';
		queue <int> q;q.push(0);
//		q.push(1);q.push(2);
		while (!q.empty())
		{
			int j = q.front();q.pop();
			REP(c, 0, 1)
			{
				string New = str[j] + (char)c;
				REP(k, 0, cur) if (same(New, str[k]))
				{
					trans[j][c] = k;
					break;
				}
				if (!trans[j][c])
				{
					trans[j][c] = ++cur;
					str[cur] = New;
					q.push(cur);
				}
			}
		}
		output(P," ");cerr<<cur<<endl;
		string _100 = "100";REP(i,0,2)_100[i] -= '0';
		string _1="1";_1[0] -= '0';
		cerr<<"test: " << same(turn("110"),turn("111")) << endl;
		REP(i, 1, cur)
		{
			fprintf(stderr,"%d: ",i);output(str[i]);
		}
		REP(i, 0, cur)
			REP(j, 0, 1) if (trans[i][j]) fprintf(stderr,"trans[%s][%d] = %s\n", back(str[i]).c_str(),j, back(str[trans[i][j]]).c_str());
		dp[0][0] = 1;
		REP(i, 0, n)
		{
			REP(j, 0, cur) dp[i + 1][j] = 0;
			REP(j, 0, cur)
				REP(k, 0, 1) if (S[i] != k)
				inc(dp[i + 1][trans[j][!k]], dp[i][j]);
		}
		REP(i, 0, n + 1) REP(j, 0, cur) fprintf(stderr,"%d%c", dp[i][j], j == end_j ? '\n' : ' ');
		REP(i, 1, cur)
			if (calc(str[i]))
			{
				inc(ans, dp[n + 1][i]);
			}
		cout << ans << '\n';
		fputs("\n",stderr);
	}
	return 0;
}
