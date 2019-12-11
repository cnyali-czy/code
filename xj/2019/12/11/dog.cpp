#include <bits/stdc++.h>
using namespace std;
#define MN 2005
bitset<MN>tmp,bit[MN];
int n,m,k,L,c[MN],v[MN],cnt[MN],rk[MN];
vector<int>num[MN];
bool ok[MN];
bool cmp(int a,int b){
	if(v[a]==v[b])return c[a]>c[b];
	return v[a]<v[b];
}
int main() {
	scanf("%d%d",&n,&L);
	for(int i=1;i<=n;++i){
		scanf("%d%d",&c[i],&v[i]);
		rk[i]=i;
		//      cnt[v[i]]+=c[i];
		//      vis[v[i]]++;
	}
	sort(rk+1,rk+1+n,cmp);
	int Cnt=0,lie=0;
	for(int I=1;I<=n;++I){
		int i=rk[I];
		int bin=1,ned=L/v[i];
		while(c[i]>=bin&&bin*v[i]<=L){
			num[i].push_back(bin*v[i]);
			lie++;
			ned-=bin;
			c[i]-=bin;
			bin<<=1;
		}
		if(c[i]&&ned>0)num[i].push_back(min(c[i],ned)*v[i]);
	}
	scanf("%d",&m);
	for(int i=1;i<=m;++i){
		scanf("%d",&k);
		ok[k]=1;
	}
	bit[0].set(0);
	int sum=0;
	for(int I=1;I<=n;++I){
		int i=rk[I];
		if(v[i]==v[rk[I-1]]){  
			Cnt++;
			if(sum>L/v[i]){
				for(int j=I-1;j>=Cnt-1;--j){
					bit[j+1]|=(bit[j]<<v[i]);
				}
				continue;
			}
			sum+=c[i];
		}
		else {
			Cnt=1,sum=c[i];
		}
		for(int j=I-1;j>=0;--j){
			tmp.reset();
			for(int k=0;k<num[i].size();++k){
				tmp|=((tmp|bit[j])<<num[i][k]);
			}
			bit[j+1]|=tmp;
		}
	}
	tmp.reset();
	for(int i=1;i<=n;++i)
		if(ok[i])tmp|=bit[i];
	while(tmp.count()){
		int p=tmp._Find_first();
		if(p>L)break;
		printf("%d ",p);
		tmp.reset(p);
	}
	return 0;
}
