#include<bits/stdc++.h>
using namespace std;
struct node
{
	int val;
	int index;
	bool operator <(const node &B)const
	{
		return (val==B.val)?(index<B.index):(val<B.val);
	}
};
multiset<node>st;
int now[100005];
int cf[100005];
int main(){
	freopen("invest.in","r",stdin);
	freopen("invest.out","w",stdout);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>now[i];
		cf[i]=0;
		st.insert(node{0,i});
	}
	while(1){
		char a[10];
		cin>>a;
		if( a[0]=='R' )
		{
			multiset<node>::iterator i=st.begin();
			cout<<(*i).index<<" ";
			i++;
			cout<<(*i).index<<"\n";
		}else if(a[0]=='E')break;
		else{
			int k,b;
			sscanf(a,"%d",&k);
			cin>>b;
			st.erase(node{cf[k],k});
			st.insert(node{now[k]-b,k});
			cf[k]=now[k]-b;
			now[k]=b;
		}
	}
	return 0;
}

