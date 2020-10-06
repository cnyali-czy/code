#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define mp make_pair
#define x first
#define y second
const int MN = 19683,mn=1515;
int at[MN][15],ppcnt[MN],pw[MN];
int f[MN][mn],pos[MN][mn];
pii pre[MN][mn];
int x[mn],y[mn],n,m,k,l,N;
queue<pii >Q;
//0：无 1：按了没动 2：按了动了
void init(int n){
	pw[0]=1;for(int i=1;i<=n;++i)pw[i]=pw[i-1]*3;
	int sz=pw[n];
	for(int i=0;i<sz;++i){
		int x=i,cnt=0;
		for(int j=0;j<n;++j){
			at[i][j]=x%3;
			if(at[i][j]==1) cnt++;
			x/=3;
		}
		ppcnt[i]=cnt;
	}
}
int dist(int i,int j){
	return max(abs(x[i]-x[j]),abs(y[i]-y[j]));
}
int qwq[15];
void out(int x,int y){
	if(pre[x][y].y)out(pre[x][y].x,pre[x][y].y);
	if(pos[x][y]==114514){
		if(pre[x][y].y)
			for(int i=1;i<=k;++i)
				if(qwq[i]!=N)qwq[i]++;
		return;
	}
	for(int i=1;i<=k;++i)
		if(qwq[i]==pos[x][y]){
			for(int j=1;j<=k;++j)
				if(qwq[j]!=N)qwq[j]++;
			qwq[i]=0;
			printf("%d %d\n",i,f[x][y]);
			break;
		}
	return;
}
int main(){
	scanf("%d%d%d%d",&n,&m,&k,&l);
	N=max(n-1,m-1);
	init(N);
	for(int i=1;i<=k;++i)qwq[i]=i-1;
	for(int i=N+1;i<=k;++i)qwq[i]=N;
	int st=0;
	for(int i=1;i<=k;++i){
		st+=pw[i-1];
		x[k-i+1]=-i+2;y[k-i+1]=-i+2;
	}
	l+=k;
	st%=pw[N];
	for(int i=k+1;i<=l;++i)
		scanf("%d%d",&x[i],&y[i]);
	Q.push(mp(st,k));
	pos[st][k]=114514;
	memset(f,0x3f,sizeof(f));
	f[st][k]=0;
	while(!Q.empty()){
		pii w=Q.front();Q.pop();
		if(w.y==l){
			printf("%d\n",f[w.x][w.y]);
			out(w.x,w.y);
			break;
		}
		int now=w.y+1;
		int del=0;
		for(int i=0;i<N;++i){
			if(at[w.x][i]!=0)del++;
			if(at[w.x][i]!=1)continue;
			if(dist(now-del,now)<=i){
				int to=w.x+pw[i];
				to*=3;
				to%=pw[N];
				to++;
				if(f[to][now]<=1e9)continue;
				pos[to][now]=i;
				pre[to][now]=mp(w.x,w.y);
				f[to][now]=f[w.x][w.y]+1;
				Q.push(mp(to,now));
			}
		}
		if(k>ppcnt[w.x]&&f[w.x][w.y]>=N){
			int to=w.x*3%pw[N];
			to++;
			if(f[to][w.y+1]>1e9){
				f[to][w.y+1]=f[w.x][w.y]+1;
				pos[to][w.y+1]=N;
				pre[to][w.y+1]=mp(w.x,w.y);
				Q.push(mp(to,w.y+1));
			}
		}
		{
			int to=w.x*3%pw[N];
			if(f[to][w.y]<=1e9)continue;
			pos[to][w.y]=114514;
			f[to][w.y]=f[w.x][w.y]+1;
			pre[to][w.y]=mp(w.x,w.y);
			Q.push(mp(to,w.y));
		}
	}
	return 0;
}
