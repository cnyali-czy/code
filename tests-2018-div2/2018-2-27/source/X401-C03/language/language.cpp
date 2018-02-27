#include<bits/stdc++.h>
using namespace std;

map<string,int>mp;
string nmpa[105];
int mpa[105][105];
int  mid[105][105];

void Debug(){
	for(int i = 1;i <= 6;i ++){
		for(int j = 1;j <= 6;j ++){
			cout << mpa[i][j] << " ";
		}cout << "\n";
	}
}

int main(){
	freopen("language.in","r",stdin);
	freopen("language.out","w",stdout);
	int m,n;cin >> m >> n;
	for(int i = 1;i <= m;i ++){
		for(int j = 1;j <= m;j ++){
			mpa[i][j] = -10000000;
		}
	}
	for(int i = 1;i <= m;i ++){
		string coin;cin >> coin;
		//cout << coin << "\n";
		nmpa[i] = coin;
		mp[coin] = i;
	}
	for(int i = 1;i <= n;i ++){
		string A,B;
		cin >> A >> B;
		mpa[mp[A]][mp[B]] = -1;
		mid[mp[A]][mp[B]] = mp[A];
	}
	//Debug();
	for(int k = 1;k <= m;k ++){
		for(int i = 1;i <= m;i ++){
			for(int j = 1;j <= m;j ++){
				if( mpa[i][j] < mpa[i][k] + mpa[k][j] ){
					mpa[i][j] = mpa[i][k] + mpa[k][j];
					mid[i][j] = k;
				}
			}
		}
	}
	//Debug();
	int mi = 0;int X = 0,Y = 0;
	for(int i = 1;i <= m;i ++){
		for(int j = 1;j <= m;j ++){
			if( mpa[i][j] < mi and mpa[i][j] != -10000000 ){
				mi = mpa[i][j];
				X = i;
				Y = j;
			}
		}
	}
	int now = X;
	stack<int>stk;
	stk.push(Y);
	cout << (-mi + 1) << "\n";
	cout << nmpa[X] << " ";
	while(!stk.empty()){
		int last = stk.top();
		if(mid[now][last] == now){
			now = last;
			cout << nmpa[now] << " ";
			stk.pop();
		}else{
			stk.push(mid[now][last]);
		}
	}
	return 0;
}
/*
6 6
I
You
Love
Miss
Very
Much
I Love
Love You
I Miss
Miss You
You Very
Very Much
*/
