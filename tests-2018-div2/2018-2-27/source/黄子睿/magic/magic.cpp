#include<bits/stdc++.h>
using namespace std;
long long a,s;
int main()
{
	freopen("magic.in","r",stdin);
	freopen("magic.out","w",stdout);
	cin>>a;
	if(a==1)
		cout<<1<<endl;
	else
		cout<<a*(a-1)/2-1<<endl;
	return 0;
}
