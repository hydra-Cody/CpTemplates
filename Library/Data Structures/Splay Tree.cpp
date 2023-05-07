#include <cstdio>
#include <cstring>
const int N=101234;
struct jilu{int key,cnt,size,ls,rs,fa;}tree[N*20];
struct jilu2{int tail,ls,next;}tr[N];
int n,m,k,size[N],que[10000000],ans,e[N*2],next[N*2],lis[N],cost[N],dist[N],tot;
int root[N],l,fa[N];
bool mark[N];
inline void Renew(int x)
{
	tree[x].size=tree[tree[x].ls].size+tree[tree[x].rs].size+tree[x].cnt;
}
inline void Zig(int x)
{
	int y=tree[x].fa,z=tree[y].fa;
	tree[y].ls=tree[x].rs,tree[tree[x].rs].fa=y;
	tree[x].fa=z;
	if (tree[z].ls==y) tree[z].ls=x;
	else tree[z].rs=x;
	tree[y].fa=x,tree[x].rs=y;
	Renew(y);
}
inline void Zag(int x)
{
	int y=tree[x].fa,z=tree[y].fa;
	tree[y].rs=tree[x].ls,tree[tree[x].ls].fa=y;
	tree[x].fa=z;
	if (tree[z].ls==y) tree[z].ls=x;
	else tree[z].rs=x;
	tree[y].fa=x,tree[x].ls=y;
	Renew(y);
}
inline void Splay(int x,int &root)
{
	for (;tree[x].fa!=0;){
		int y=tree[x].fa,z=tree[y].fa;
    	if (z==0){
			if (tree[y].ls==x) Zig(x);
    		else Zag(x);
   		 	}
    	else{
    		if (tree[z].ls==y)
    			if (tree[y].ls==x) Zig(y),Zig(x);
    			else Zag(x),Zig(x);    		
    		else
    			if (tree[y].rs==x) Zag(y),Zag(x);
    			else Zig(x),Zag(x);
    		}
		}
	root=x; Renew(x);
}
inline void Find(int &root,int x)
{
	int p=root;
	for (;;){
		if (x==tree[p].key) break;
		if (x>tree[p].key)
			if (tree[p].rs!=0) p=tree[p].rs;
			else break;
    	else
    		if (tree[p].ls!=0) p=tree[p].ls;
    		else break;
		}
	Splay(p,root);
	if (tree[p].key==x) ans+=tree[p].cnt;
}
inline void Insert(int x,int &root)
{
	int p=root;
	for (;;){
		if (x==tree[p].key) break;
		if (x>tree[p].key)
			if (tree[p].rs!=0) p=tree[p].rs;
    		else {tree[p].rs=tot+1;break;}
    	else
    		if (tree[p].ls!=0) p=tree[p].ls;
    		else {tree[p].ls=tot+1;break;}
    	}
	if (tree[p].key==x) tree[p].cnt++,Splay(p,root);
    else{
    	tot++;
    	tree[tot].cnt=1;
    	tree[tot].key=x;
    	tree[tot].fa=p;
    	Splay(tot,root);
    	}
}
void Dfs(int u)
{
	mark[u]=true;
    for (int v=tr[u].ls;v!=0;v=tr[v].next) Dfs(v);
	int max=0,maxv=-1;
	for (int v=tr[u].ls;v!=0;v=tr[v].next)
	if (size[v]>max) max=size[v],maxv=v;
	if (maxv!=-1){
		for (int v=tr[u].ls;v!=0;v=tr[v].next)
		if (v!=maxv){
			int head=0,tail=1;que[1]=v;
			while (head<tail){
    			head++;
    			for (int i=tr[que[head]].ls;i!=0;i=tr[i].next)
    				que[++tail]=i;
    			}
    		for (int i=1;i<=tail;i++)
    			Find(root[maxv],k+2*dist[u]-dist[que[i]]);
    		for (int i=1;i<=tail;i++)
    			Insert(dist[que[i]],root[maxv]);
    		}
    	Find(root[maxv],k+2*dist[u]-dist[u]);
    	Insert(dist[u],root[maxv]);
    	root[u]=root[maxv];
    	}
    else{
    	root[u]=++tot;
    	tree[tot].key=dist[u];
    	tree[tot].cnt=1;
    	tree[tot].size=1;
    	}	
}

int main()
{
    scanf("%d%d",&n,&k);
    int x,y,z;char c;
    for (int i=1;i<n;i++){
    	scanf("%d%d",&x,&y);
    	e[++l]=y,next[l]=lis[x],lis[x]=l;cost[l]=1;
    	e[++l]=x;next[l]=lis[y],lis[y]=l;cost[l]=1;
    	}
    int u,v,head=0,tail=1;que[1]=1;mark[1]=true;dist[1]=0;
    while (head<tail){
    	u=que[++head];
    	for (int i=lis[u];i!=0;i=next[i]){
    		v=e[i];
    		if (!mark[v]){
    			if (!tr[u].ls) tr[u].ls=v;
    			else tr[tr[u].tail].next=v;
    			dist[v]=dist[u]+cost[i];
    			tr[u].tail=v; que[++tail]=v; fa[v]=u;
    			mark[v]=true;
				}
			}
    	}
    for (int i=tail;i>0;i--)
		size[que[i]]++,size[fa[que[i]]]+=size[que[i]];
	ans=0; tot=0; Dfs(1);
	printf("%d\n",ans); return 0;
}