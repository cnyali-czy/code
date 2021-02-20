/*
	Problem:	couple.cpp
	Time:		2021-02-18 13:59
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <bits/stdc++.h>

using namespace std;


template <typename T>
inline T read()
{
	T ans = 0, flag = 1;
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

struct cmp
{
	inline bool operator () (const string &a, const string &b)
	{
		if (a.size() != b.size()) return a.size() < b.size();
		REP(i, 0, (int)a.size() - 1)
		{
			if (a[i] < b[i]) return 1;
			if (a[i] > b[i]) return 0;
		}
		return 0;
	}
};

void work_bf()
{
	read<int>();int T = read<int>();
	while (T--)
	{
		string s1, s2;
		cin >> s1 >> s2;
		s1 = "rm OUTPUT && factor " + s1 + " >> OUTPUT";
		system(s1.c_str());
		ifstream ANS("OUTPUT");
		map <string, int, cmp> cnt;
		ANS >> s2;
		while (ANS >> s2) cnt[s2]++;
		for (auto i : cnt) printf("%s %d ", i.first.c_str(), i.second);
		puts("");
	}
}

int main()
{
	file("couple");
//	work_bf();
	return 0;
}
