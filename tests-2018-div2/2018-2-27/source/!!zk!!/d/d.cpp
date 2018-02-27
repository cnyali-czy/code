#include<bits/stdc++.h>
using namespace std;
const int maxn=777+5;
int a[maxn][maxn],b[maxn],c[maxn];
int main()
{
	freopen("d.in","r",stdin);
	freopen("d.out","w",stdout);
	int n,m,i,j,x,y,z,s=0,ans=0;
	scanf("%d",&n);
	for(i=0;i<n;i++)
		scanf("%d%d",&b[i],&c[i]);
	scanf("%d",&m);
	for(i=1;i<=m;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		if(x==0&&y==n)
			ans=z;
		a[x][y]=z;
		int sum;
		if(y==n)
		{
			s+=a[x][y];
			continue;
		}
		sum=z%(b[y]+c[y]);
		if(sum<c[y]) sum=c[y]+b[y];
		s=s+a[x][y]+c[y]+b[y]-sum;
	}
	if(!ans)
		cout<<s;
	else
		cout<<ans;
	return 0;
}
