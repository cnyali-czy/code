#include<bits/stdc++.h>
using namespace std;
int p[100010],zp[100010],y[100010];
int main() {
	freopen("invest.in","r",stdin);
	freopen("invest.out","w",stdout);
	int i,j,k,l,m,n,a,x,top,maxn=-100000,minn=100000,f;
	scanf("%d",&n);
	for(i=1; i<=n; i++)scanf("%d",&p[i]);
	while(1) {
		string s;
		cin>>s;
		if(s[0]=='E')break;
		if(s[0]>='0' && s[0]<='9') {
			a=s[0]-'0';
			top=1;
			while(s[top]>='0' && s[top]<='9') {
				top++;
				a=a*10+s[top]-'0';
			}
			scanf("%d",&x);
			if(zp[a]==0){zp[a]=x;y[a]=zp[a]-p[a];}
			else {p[a]=zp[a];zp[a]=x;y[a]=zp[a]-p[a];}
		}
			if(s[0]=='R'){
			for(i=1;i<=n;i++)if(zp[i]==0)y[i]=0;
			minn=100000;maxn=-10000;
			for(i=1;i<=n;i++)maxn=max(maxn,y[i]);
			if(maxn==0){cout<<1<<" "<<2<<endl;continue;}
			for(i=1;i<=n;i++)if(maxn==y[i]){cout<<i<<" ";f=i;break;}
			for(i=1;i<=n;i++)if(i!=f)minn=min(maxn-y[i],minn);
			for(i=1;i<=n;i++)if(minn==maxn-y[i]){cout<<i<<" "<<endl;break;}
			//cout<<minn<<endl;
			}
		}
		//for(i=1;i<=n;i++)cout<<p[i]<<" "<<zp[i]<<endl;
	return 0;
}

