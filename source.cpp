#include <bits/stdc++.h>
#define rep(i,n)for(int i=0;i<(n);i++)
using namespace std;

struct st{
	double tim;
	int ty;//ty=0→辺がタイトになる、ty=1→施設を開設できる
	int a,b;
};
bool operator<(const st&a,const st&b){
	return a.tim>b.tim;
}

double x[2000],y[2000];
double c[2000][2000];
double f[2000];

double alpha[2000]; //最終的なα
double cont[2000];  //貢献している都市の数
double last[2000];  //最後にcontが変わった時間
double sum[2000];   //last時点でのsum
double est[2000];   //予定開設時間
int p[2000];        //接続立証人
int ans[2000];      //実際につなぐ先
int d[2000];

vector<int>special[2000];
vector<int>v[2000];

priority_queue<st>que;

void update(int b,double tim){
	sum[b]+=(tim-last[b])*cont[b];
	last[b]=tim;
}

void push(int b){
	if(cont[b]==0){
		est[b]=INFINITY;
		return;
	}
	double t=(f[b]-sum[b])/cont[b]+last[b];
	est[b]=t;
	que.push({est[b],1,b});
}

void end(int a,double tim){
	alpha[a]=tim;
	for(int u:special[a]){
		if(cont[u]==-1)continue;
		update(u,tim);
		cont[u]--;
		push(u);
	}
}

int main(){
	int n,m;cin>>n>>m;//n←都市の数、m←施設の数
	
	rep(i,n+m)scanf("%lf%lf",&x[i],&y[i]);
	rep(i,m)scanf("%lf",&f[i]);

	rep(i,n)rep(j,m){
		double dist=(x[j+n]-x[i])*(x[j+n]-x[i])+(y[j+n]-y[i])*(y[j+n]-y[i]);
		dist=sqrt(dist);
		c[i][j]=dist;
		que.push({dist,0,i,j});
	}
	ofstream ofs("./out.txt");
	rep(i,n)alpha[i]=INFINITY;
	memset(p,-1,sizeof(p));
	vector<int>F;//仮想開設された集合
	while(!que.empty()){
		st e=que.top();que.pop();
		if(e.ty==0){//辺がタイト
			if(e.tim>=alpha[e.a])continue;
			
			if(cont[e.b]>=0){//開設に貢献する
				update(e.b,e.tim);
				cont[e.b]++;
				push(e.b);
				special[e.a].push_back(e.b);
				v[e.b].push_back(e.a);
			}
			else{//既に開設している
				end(e.a,e.tim);
				ofs<<-1<<' '<<e.a<<endl;
				if(p[e.a]==-1)p[e.a]=e.b;
			}
			ofs<<e.a<<' '<<e.b<<endl;
		}
		else{//施設を開設
			if(e.tim!=est[e.a])continue;
			update(e.a,e.tim);
			cont[e.a]=-1;
			F.push_back(e.a);
			for(int u:v[e.a]){
				if(p[u]!=-1)continue;
				p[u]=e.a;
				ofs<<-1<<' '<<u<<endl;
				end(u,e.tim);
			}
			ofs<<e.a<<endl;
		}
	}
	double alphasum=0;
	rep(i,n){
		printf("%d %.5lf\n",p[i],alpha[i]);
		alphasum+=alpha[i];
	}
	set<int>H;//実際に開設する施設
	for(int i:F){
		bool ok=true;
		for(int a:v[i]){
			if(d[a]){ok=false;break;}
		}
		if(ok){
			H.insert(i);
			for(int a:v[i])d[a]=true;
		}
	}
	rep(i,n){
		int id=-1;
		double Min=INFINITY;
		for(int j:H){
			if(Min>c[i][j]){
				Min=c[i][j];
				id=j;
			}
		}
		ans[i]=id;
	}
	double total=0;
	for(int i:H){
		total+=f[i];
	}
	rep(i,n){
		total+=c[i][ans[i]];
	}
	cout<<"H: ";
	for(int i:H){
		cout<<i<<' ';
	}
	cout<<endl;
	rep(i,n){
		cout<<i<<": "<<ans[i]<<endl;
	}
	cout<<"alphasum: "<<alphasum<<endl;
	cout<<"total cost: "<<total<<endl;
	ofs<<"end"<<endl;
	rep(i,m){
		ofs<<H.count(i)<<endl;
	}
	cout<<F.size()<<' '<<H.size()<<endl;
	rep(i,n){
		ofs<<ans[i]<<endl;
	}
}