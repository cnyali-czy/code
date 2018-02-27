#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
using namespace std;
struct NODE{int JG,BH,SY;}A[100005];
bool CMP(NODE X,NODE Y){
	if(X.SY==Y.SY)
		 return X.BH<=Y.BH;
	else return X.SY>=Y.SY;
}
int CHAN(string X){
	int ANS=0;
	for(int I=0;I<X.size();I++)
		ANS=ANS*10+X[I]-'0';
	return ANS;
}
int main( ){
	freopen("invest.in","r",stdin);
	freopen("invest.out","w",stdout);
	int I,J,K,M,N,S;
	string C;cin>>M;
	for(I=1;I<=M;I++){
		cin>>A[I].JG;
		A[I].BH=I;
		A[I].SY=0;
	}
	sort(A+1,A+M+1,CMP);
	while(cin>>C && C!="EndOfCurrentCase"){ 
		if(C[0]=='R'){
			sort(A+1,A+M+1,CMP);
			cout<<A[1].BH<<" ";
			cout<<A[2].BH<<endl;
		}else{
			int X=CHAN(C),Y;
			cin>>Y;
			for(I=1;I<=M;I++){
				if(A[I].BH==X){
					A[X].SY=Y-A[X].JG;
					A[X].JG=Y; break;
				}
			}
		}
	}
	return 0;
}
