#include<bits/stdc++.h>
using namespace std;
const int maxn=100000+5;
int a[maxn],s[maxn];
struct node{
	int s,num;
}a1[maxn];
int doit(string a)
{
	int b=0;
	for(int i=0;i<a.size();i++)
		b=b*10+a[i]-'0';
	return b;
}
int cmp(node a,node b)
{
	return a.s>b.s;
}
int main()
{
	freopen("invest.in","r",stdin);
	freopen("invest.out","w",stdout);
	int n,i,x;string b;
	scanf("%d",&n);
	for(i=1;i<=n;i++)
		scanf("%d",&a[i]);
	while(1)
	{
		cin>>b;
		if(b[0]>='0'&&b[0]<='9')
		{
			scanf("%d",&x);
			int sum=doit(b);
			s[sum]=x-a[sum];
			a[sum]=x;
		}
		if(b[0]=='R')
		{
			for(i=1;i<=n;i++)
				a1[i].s=s[i],a1[i].num=i;
			sort(a1+1,a1+1+n,cmp);
			cout<<a1[1].num<<" "<<a1[2].num<<endl;
		}
		if(b[0]=='E')
			return 0;
	}
	return 0;
}
