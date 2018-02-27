#include<bits/stdc++.h>
using namespace std;
const int maxn=100000+10;
int n;
int f[maxn],m[maxn];
int main(){
	freopen("invest.in","r",stdin);
	freopen("invest.out","w",stdout);
	int i,a,top,x,fmax,smax;
	char s[20];
	m[0]=-2147483647;
	scanf("%d",&n);
	for(i=1;i<=n;i++)
		scanf("%d",&f[i]);
	while(1){
		cin>>s;
		if(s[0]>='0'&&s[0]<='9'){
			a=s[0]-'0';
			top=1;
			while(s[top]>='0'&&s[top]<='9'){
				a=a*10+s[top]-'0';
				top++;
			}
			scanf("%d",&x);
			m[a]=x-f[a];
			f[a]=x;
		}
		if(s[0]=='E')
			return 0;
		if(s[0]=='R'){
			fmax=smax=0;
			for(i=1;i<=n;i++)
				if(m[i]>m[fmax]){
					smax=fmax;
					fmax=i;
				}
				else
					if(m[i]>m[smax])
						smax=i;
			printf("%d %d\n",fmax,smax);
		}
	}
	return 0;
}
