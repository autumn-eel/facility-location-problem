#include <bits/stdc++.h>
#define rep(i,n)for(int i=0;i<(n);i++)
using namespace std;

int main(){
	random_device rnd;
	int n=600;
	int m=100;
	cout<<n<<' '<<m<<endl;
	rep(i,n+m)printf("%d %d\n",rnd()%1800+1,rnd()%800+1);
	rep(i,m)printf("%d\n",rnd()%500+1);
}