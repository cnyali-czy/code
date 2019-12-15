//test
#include<bits/stdc++.h>
using namespace std;
template<typename T>inline T read(){
	T x=0,f=0;char c=getchar();
	while(!isdigit(c)) f=c=='-',c=getchar();
	while(isdigit(c)) x=x*10+c-48,c=getchar();
	return f?-x:x;
}
#include <bitset>
#define int long long
namespace run
{
	inline char getc()
	{
		char c=getchar();
		while(c!='0' && c!='1') c=getchar();
		return c;
	}
	typedef pair<int,int> P;
	const int N=2e5+1;
#define node bitset <75>
	node mt[N];
	int n,m,a[71],b[71],pos[71];
	P c[71];

	inline void Turn(int tmp){
		node _new;
		for(int i=1;i<=m;i++)
			_new[pos[i]]=mt[tmp][i];
		mt[tmp]=_new;
	}
	inline void prin(node tmp){
		for(int i=1;i<=m;i++) printf("%d",tmp[i]);
		puts("");
	}

	node lb[71];int pw[36];
	inline void insert(node tmp){
		for(int i=m;i>=1;i--)
			if(tmp[i]){
				if(!lb[i][i]){lb[i]=tmp;return;}
				else tmp ^= lb[i];
			}
	}
	inline int get(){
		node tmp;int ans=0;
		for(int i=m,las,now;i>=1;i--){
			//  cout<<i<<":-------"<<endl;
			//  prin(tmp);
			//  cout<<ans<<endl;
			if(a[i]==1){
				if(tmp[i]){las=1;ans+=pw[b[i]];continue;}
				else{
					if(lb[i][i]){
						tmp ^= lb[i];
						ans+=pw[b[i]],now=1;
					}else now=0;
				}
			}else{
				ans-=pw[b[i]];
				if(!tmp[i]){las=0;ans+=pw[b[i]];continue;}
				else{
					if(lb[i][i]){
						tmp ^= lb[i];
						ans+=pw[b[i]],now=0;
					}else now=1;
				}
			}

			//  if(i==3) cout<<now<<" "<<las<<endl;
			if(i<m && b[i+1]==b[i] && las==now && (lb[i+1][i+1] && lb[i+1][i])){
				node _new=lb[i+1];
				_new[i+1]=_new[i]=0;
				//      cout<<i<<" "<<endl;
				//      prin(_new);
				insert(_new);
			}
			las=now;
		}
		return ans;
	}
	int main(){
		pw[0]=1;
		for(int i=1;i<=35;i++) pw[i]=pw[i-1]*3LL;
		n=read<int>(),m=read<int>();
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				mt[i][j]=getc()-'0';

		for(int i=1;i<=m;i++){
			a[i]=read<int>(),b[i]=read<int>();
			c[i]=P(abs(b[i]),i);
		}
		sort(c+1,c+m+1);
		for(int i=1;i<=m;i++) pos[c[i].second]=i;
		static int d[71],e[71];
		for(int i=1;i<=m;i++) d[pos[i]]=a[i],e[pos[i]]=b[i];
		for(int i=1;i<=m;i++) a[i]=d[i],b[i]=e[i];

		for(int i=1;i<=n;i++) Turn(i),insert(mt[i]);
		//      for(int i=1;i<=m;i++) cout<<a[i]<<" "<<b[i]<<endl;
		//      for(int i=m;i>=1;i--) if(lb[i][i]) cout<<i<<endl,prin(lb[i]);
		printf("%lld\n",get());
		return 0;
	}
}
#undef int
int main(){
#ifdef CraZYali
	freopen("matrix.in", "r", stdin);
	freopen("matrix.out", "w", stdout);
#endif
	return run::main();
}
