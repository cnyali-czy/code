#define REP(i, s, e) for(register int i = s; i <= e ;i++)

#include <bits/stdc++.h>

using namespace std;

int m, n, k, T;

vector <string> v;

int main()
{
	freopen("match.in", "r", stdin);
	freopen("match.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin >> T;
	while (T --)
	{
		string s, t;
		cin >> s >> t;
		int lens = s.size();
		int lent = t.size();
		if (s.size() < t.size())
		{
			cout << "Impossible\n";
			continue;
		}
		v.clear();
		int te = 0;
		while (t.find("*", te) != string::npos)
		{
			int ttt = t.find("*", te);
			v.push_back(t.substr(te, ttt - te));
			te = ttt + 1;
		}
		
		if (t[t.size() - 1] != '*') v.push_back(t.substr(te));
		/*
		REP(i, 0, v.size() - 1) cout << v[i] << ' ';
		cout << endl;
		*/
		int pos = 0, si = v.size() - 1;
		REP(i, 0, si)
			if (s.find(v[i], pos) == string::npos)
			{
				cout << "Impossible\n";
				goto no;
			}
			else pos = s.find(v[i], pos);
		if (pos == lens && t[lent] == '*') cout << "Impossible\n";
		else cout << "Maybe\n";
		no:;
	}
	return 0;
}
