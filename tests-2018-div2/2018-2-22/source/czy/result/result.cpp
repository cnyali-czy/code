#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 130000 + 10;

int n;

struct student
{
	string name;
	int score;
}s[maxn];
inline bool cmp(student A, student B) {return A.name < B.name;}

vector <string> full;

int main()
{
	freopen("result.in", "r", stdin);
	freopen("result.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin >> n;
	REP(i, 1, n)
	{
		cin >> s[i].name >> s[i].score;
		if (s[i].score == 150)
			full.push_back(s[i].name);
	}
	cout << "1~9 10~19 20~29 30~39 40~49 50~59 60~69 70~79 80~89 90~99 100~109 110~119 120~129 130~139 140~149\n";
	int res = 0;
	REP(i, 1, n)
		if (1 <= s[i].score && s[i].score <= 9) res++;
	cout << res; 
	REP(cut, 1, 14)
	{
		res = 0;
		REP(i, 1, n)
			if (cut * 10 <= s[i].score && s[i].score <= cut * 10 + 9) res++;
		cout << ' ' << res;
	}
	cout << endl;
	sort(s + 1, s + 1 + n, cmp);
	REP(i, 1, n) cout << s[i].name << ' ' << s[i].score << endl;
	int siz = full.size();
	if (siz)
	{
		sort(full.begin(), full.end());
		cout << siz-- << endl;
		REP(i, 0, siz) cout << full[i] << endl;
	}
	else
		cout << "0\nNo";
	return 0;
}
