#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <map>
#include <vector>
#include <cassert>
using namespace std;
const int N=5010;
const int N2=5e6;
struct bian{
	int next,point;
}b[N<<1];
int p[N],len,n,num,A[50],u[N2],v[N2],K,now,m,se,father[N];
const int mo=998244353,inv2=(mo+1)/2;
struct tree{
	int w,n,se,p;
	vector<int>go[12];
	vector<int>sub;
}t[N];
map<int,int>M;
vector<int>go[50],B[100000];
vector<string>sub;
int quick(int k1,int k2){
	int k3=1;
	while (k2){
		if (k2&1) k3=1ll*k3*k1%mo;
		k2>>=1; k1=1ll*k1*k1%mo;
	}
	return k3;
}
int gettree(){
	int k1=++len; now++;
	while (A[now]) go[k1].push_back(gettree());
	now++; return k1;
}
string gethash(int k1){
	vector<string>A;
	for (int i=0;i<go[k1].size();i++)
		A.push_back(gethash(go[k1][i]));
	sort(A.begin(),A.end());
	int pre=0;
	for (int i=1;i<=A.size();i++)
		if (i==A.size()||A[i]!=A[i-1]){
			int k1=i-pre;
			for (int j=1;j<=k1;j++) se=1ll*se*j%mo;
			pre=i;
		}
	if (k1==1) sub=A;
	string ans="1";
	for (int i=0;i<A.size();i++) ans+=A[i];
	return ans+"0";
}
int getw(string K){
	long long ans=0;
	for (int i=0;i<K.length();i++) ans=ans*2+K[i]-'0';
	return ans;
}
string getsub(int k1,int k2,int key){
	vector<string>A;
	for (int i=0;i<go[k1].size();i++){
		int j=go[k1][i];
		if ((key&(1<<j-1))&&j!=k2) A.push_back(getsub(j,k1,key));
	}
	sort(A.begin(),A.end());
	string ans="1";
	for (int i=0;i<A.size();i++) ans+=A[i];
	return ans+"0";
}
int d[N2],D[N2],size[50],root,cur;
void dfs1(int k1,int k2){
	size[k1]=1;
	for (int i=0;i<go[k1].size();i++){
		int j=go[k1][i];
		if (j!=k2){
			dfs1(j,k1); size[k1]+=size[j];
		}
	}
}
void dfs2(int k1,int k2,int n){
	int now=n-size[k1];
	for (int i=0;i<go[k1].size();i++){
		int j=go[k1][i];
		if (j!=k2){
			dfs2(j,k1,n); now=max(now,size[j]);
		}
	}
	if (now<cur){
		cur=now; root=k1;
	}
}
map<int,int>M2;
void getans(int n){
	for (int i=1;i<=n;i++) go[i].clear(); len=0,now=1; se=1;
	gettree(); sub.clear();
	string s=gethash(1);
	int key=getw(s);
	if (M[key]) return; num++; M[key]=num; 
	t[num].n=n; t[num].se=se;
	for (int i=1;i<=n;i++) t[num].go[i]=go[i];
	for (int i=0;i<sub.size();i++) 
		if (M[getw(sub[i])]!=1) t[num].sub.push_back(M[getw(sub[i])]);
		else t[num].p++;
	len=n; m=0;
	for (int i=1;i<=n;i++)
		for (int j=0;j<go[i].size();j++){
			m++; u[m]=i; v[m]=go[i][j];
		}
	for (int i=1;i<=n;i++)
		for (int j=0;j<go[i].size();j++)
			if (go[i][j]>i) go[go[i][j]].push_back(i);
	root=0; cur=n+1; dfs1(1,0); dfs2(1,0,n);
	string now=getsub(root,0,(1<<n)-1);
	int curhash=getw(getsub(root,0,(1<<n)-1)),where=M2[curhash];
	if (where){
		t[num].w=t[where].w; return;
	}
	M2[curhash]=num;		
	int lim=K-1;
	if (lim>=4) lim-=3;
	for (int t=1;t<=lim;t++){
		for (int i=1;i<=len;i++) B[i].clear();
		int prelen=len;
		len=m;
		for (int i=1;i<=m;i++) B[u[i]].push_back(i),B[v[i]].push_back(i);
		m=0;
		for (int i=1;i<=prelen;i++)
			for (int j=0;j<B[i].size();j++)
				for (int k=0;k<j;k++){
					m++; u[m]=B[i][j]; v[m]=B[i][k];
				}
	}
	if (lim==K-1) t[num].w=m;
	else {
	//	cout<<"fa "<<len<<" "<<m<<endl;
	//	for (int i=1;i<=m;i++) cout<<u[i]<<" "<<v[i]<<endl;
		for (int i=1;i<=len;i++) d[i]=0;
		for (int i=1;i<=m;i++) d[u[i]]++,d[v[i]]++;
		for (int i=1;i<=m;i++) D[i]=d[u[i]]+d[v[i]]-2;
		int ans=0;
		for (int i=1;i<=m;i++){
			ans=(ans+1ll*D[i]*(D[i]-1)%mo*(D[i]-2))%mo;
		}
		for (int i=1;i<=len;i++) d[i]=0;
		for (int i=1;i<=m;i++){
			d[u[i]]=(d[u[i]]+D[i]-1)%mo,d[v[i]]=(d[v[i]]+D[i]-1)%mo;
			ans=(ans-2ll*(D[i]-1)*(D[i]-1))%mo;
		}
		for (int i=1;i<=len;i++) ans=(ans+1ll*d[i]*d[i])%mo;
		ans=(ans+mo)%mo;
		t[num].w=1ll*ans*inv2%mo;
	}
	//cout<<"asd "<<num<<" "<<s<<" "<<t[num].w<<" "<<t[num].se<<endl;
	for (int i=1;i<(1<<n)-1;i++){
		int root=0;
		for (int j=1;j<=n;j++) if (i&(1<<j-1)) root=j;
		string sub=getsub(root,0,i);
		if (sub.length()!=__builtin_popcount(i)*2) continue;
		t[num].w=(t[num].w-t[M[getw(sub)]].w+mo)%mo;
	} 
	//cout<<"asd "<<num<<" "<<s<<" "<<t[num].w<<" "<<t[num].se<<endl;
}
void dfs(int k1,int k2,int k3,int n){
	if (k1==n*2){
		getans(n); return;
	}
	if (k2){
		A[k1]=0; dfs(k1+1,k2-1,k3,n);
	}
	if (k3<n){
		A[k1]=1; dfs(k1+1,k2+1,k3+1,n);
	}
}
void getall(int n){
	A[1]=1; A[2*n]=0; dfs(2,0,1,n);
}
void ade(int k1,int k2){
	b[++len]=(bian){p[k1],k2}; p[k1]=len;
}
void add(int k1,int k2){
	ade(k1,k2); ade(k2,k1);
}
int f[N][2000],dp[1024];
vector<int>Ch;
int C[N][22];
int getans(const vector<int>& A,const vector<int>& B,int p){
	int n=A.size(),m=B.size(); 
	if (n<m+p) return 0;
	for (int i=0;i<(1<<m);i++) dp[i]=0; dp[0]=1;
	for (int i=0;i<A.size();i++)
		for (int j=(1<<m)-1;j>=0;j--)
			for (int k=0;k<m;k++)
				if ((j&(1<<k))==0)
					dp[j|(1<<k)]=(dp[j|(1<<k)]+1ll*dp[j]*f[A[i]][B[k]])%mo;
	int ans=1ll*dp[(1<<m)-1]*C[n-m][p]%mo;
	return ans;
}
void treedp(int k1,int k2){
	for (int i=p[k1];i;i=b[i].next){
		int j=b[i].point;
		if (j!=k2) treedp(j,k1);
	}
	Ch.clear();
	for (int i=p[k1];i;i=b[i].next){
		int j=b[i].point;
		if (j!=k2) Ch.push_back(j);
	}
	for (int i=1;i<=num;i++) f[k1][i]=getans(Ch,t[i].sub,t[i].p);
}
int findfather(int k1){
	if (father[k1]==k1) return k1; return father[k1]=findfather(father[k1]);
}
int main(){
	scanf("%d%d",&n,&K);
	for (int i=1;i<=n;i++) father[i]=i; int rem=n;
	for (int i=0;i<=n;i++){
		C[i][0]=1;
		for (int j=1;j<=min(i,20);j++)
			C[i][j]=(1ll*C[i-1][j-1]*j+C[i-1][j])%mo;
	}
	for (int i=1;i<=K+1;i++) getall(i);
	for (int i=1;i<=num;i++) t[i].w=1ll*t[i].w*quick(t[i].se,mo-2)%mo;
	for (int i=1;i<n;i++){
		int k1,k2; scanf("%d%d",&k1,&k2);
		if (findfather(k1)!=findfather(k2)){
			father[findfather(k1)]=findfather(k2);
			rem--;
		}
		add(k1,k2);
	}
	assert(rem==1);
	treedp(1,0);
	int ans=0;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=num;j++){
			ans=(ans+1ll*f[i][j]*t[j].w)%mo;
		}
	printf("%d\n",ans);
	return 0;
}
