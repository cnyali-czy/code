#define REP(i, s, e) for (int i = s; i <= e; i++)

#include <bits/stdc++.h>

using namespace std;

string ssr, s[1000];

int main()
{
#ifndef ONLINE_JUDGE
	freopen("B.in", "r", stdin);
	freopen("bfB.out", "w", stdout);
#endif
	cin>>ssr>> s[0];
	int id(0);
	while(cin>>ssr)
	{
		id++;
		int x,y,z;
		if(ssr=="I")
		{
			cin>>x>>ssr;
			s[id]=s[id-1].substr(0,x)+ssr+s[id-1].substr(x);
		}
		else if(ssr=="D")
		{
			cin>>x>>y;
			s[id]=s[id-1].substr(0,x-1)+s[id-1].substr(y);
		}
		else if(ssr=="C")
		{
			cin>>x>>y>>z;
			ssr=s[id-1].substr(x-1,y-x+1);
			s[id]=s[id-1].substr(0,z)+ssr+s[id-1].substr(z);
		}
		else
		{
			id--;
			cin>>x>>y>>z;
			cout<<s[id-x].substr(y-1,z-y+1)<<endl;
		}
	}
	//	cout<<s[0]<<'\n'<<s[0].substr(3)<<'\n'<<s[0].substr(1,2)<<endl;
	return 0;
}
