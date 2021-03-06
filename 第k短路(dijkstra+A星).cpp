#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while (ch<'0' || ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0' && ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int Point=1005, Edges=100005;
int n,m,start,end,kth;
int dist[Point],times[Point];
bool vis[Point];
struct Edge{
	int to,next,val;
}E[Edges],Eopp[Edges];      //Eopp means Eopposite
int head[Point],head_opp[Point];
struct A_Star_node{
	int p,g,h;
	bool operator < (A_Star_node x)const{
		return x.g+x.h<g+h;
	}
};         //means point  and a_Star:f(x)=g(x)+h(x);
priority_queue<A_Star_node>Q;
inline void add(int Ecnt,int u,int v,int w){
	E[Ecnt].next=head[u];
	E[Ecnt].to=v;
	E[Ecnt].val=w;
	head[u]=Ecnt;
}
inline void add_opposite(int EoppCnt,int u,int v,int w){
	Eopp[EoppCnt].next=head_opp[u];
	Eopp[EoppCnt].to=v;
	Eopp[EoppCnt].val=w;
	head_opp[u]=EoppCnt;
}
void dijkstra(int s,int e){
	memset(vis,0,sizeof(vis));
	memset(dist,127,sizeof(dist));
	int mini;	dist[e]=0;
	for (int i=1;i<=n;i++){
		mini=0;
		for (int j=1;j<=n;j++)
			if (!vis[j] && dist[mini]>dist[j])	mini=j;
		vis[mini]=1;
		for (int x=head_opp[mini];x;x=Eopp[x].next)
			dist[Eopp[x].to]=min(dist[Eopp[x].to],dist[mini]+Eopp[x].val);
	}
}
int A_Star(int s,int e){
	A_Star_node t1,tmp;
	memset(times,0,sizeof(times));
	t1.g=t1.h=0; t1.p=s;
	Q.push(t1);
	while (!Q.empty()){
		t1=Q.top();	Q.pop();
		times[t1.p]++;
		if (times[t1.p]==kth && t1.p==e) return t1.h+t1.g;
		if (times[t1.p]>kth) continue;
		for (int i=head[t1.p];i;i=E[i].next){
			tmp.p=E[i].to;
			tmp.g=dist[E[i].to];
			tmp.h=E[i].val+t1.h;
			Q.push(tmp);
		}
	}
	return -1;
}
int main(){
	n=read(),m=read(),kth=read(),start=read(),end=read();
	int x,y,z;
	memset(head,0,sizeof(head));
	memset(head_opp,0,sizeof(head_opp));
	for (int i=1;i<=m;i++){
		x=read(),y=read(),z=read();
		add(i,x,y,z);
		add_opposite(i,y,x,z);
	}
	dijkstra(start,end);
	if (start==end) kth++;
	int ans=A_Star(start,end);
	if (ans==-1) puts("No");
		else	printf("%d\n",ans);
	return 0;
}
