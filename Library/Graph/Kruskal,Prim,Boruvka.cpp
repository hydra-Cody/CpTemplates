#include<bits/stdc++.h>
using namespace std;
#define ll long long 


//--------------------------------------------------------------------------------------
/*kruskal 
 ->minimum spanning tree of an undirected,weighted graph
 ->better for relatively few edges-sparse graphs
 ->O(ELogE + ELogV) 
 ->Edge-based
*/
const ll MAX_N=10e5+10;
ll n,m;
vector<ll> adj[MAX_N];
const ll MAX=100005;
ll par[MAX];
ll rnk[MAX];
void make_set(ll n){
    for(ll i=1; i<=n; i++){
        par[i] = i;
        rnk[i] = 1;
    }
}
ll find(ll x){
    if(par[x]==x)
    return x;
    else
    return par[x]=find(par[x]);
}

void merge(ll x,ll y){
    ll px=find(x);
    ll py=find(y);
    if(rnk[px]>rnk[py]){
        par[py]=px;
        rnk[px]+=rnk[py];
    }else{
        par[px]=py;
        rnk[py]+=rnk[px];
    }
}
vector<pair<ll,pair<ll,ll>>> edges;
void kruskal() {
    sort(edges.begin(), edges.end());
    make_set(n);
    ll cnt = 0, cost = 0;
    for (auto x : edges) {
        ll w=x.first;
        ll u=x.second.first;
        ll v=x.second.second;
        u = find(u), v = find(v);
        if (u != v) {
            merge(u,v);
            cost += w;
            cnt++;
        }
    }
    if (cnt == n - 1) cout << cost << "\n";
    else cout << "IMPOSSIBLE\n";
}



//--------------------------------------------------------------------------------------- 
/*Prim
 ->minimum spanning tree for a weighted undirected graph 
 ->better for many edges compared to the number of vertices-dense graphs
 ->O(V2)
 ->Vertex-based
*/

// const ll MAX_N = 1e5 + 1;
// ll n, m;
ll visited[MAX_N];
vector<pair<ll,ll>> g[MAX_N];
void prim(ll s = 1) {
    ll cost = 0;
    priority_queue<pair<ll,ll>, vector<pair<ll,ll>>, greater<pair<ll,ll>>> pq;
    visited[s] = 1; 
    for (auto ch: g[s]){ 
        ll u=ch.first,d=ch.second;
        if (!visited[u]) 
            pq.push({d, u});
    }
    while (pq.size()) {
        auto ch2= pq.top();
        ll d=ch2.first, u=ch2.second;  
        pq.pop();
        if (!visited[u]) {
            cost += d;
            visited[u] = 1;
            for (auto ch3 : g[u]){ 
                ll v=ch3.first, w=ch3.second;
                if (!visited[v]) 
                    pq.push({w, v});
            }
        }
    } 
    for (ll i = 1; i <= n; i++) {
        if (!visited[i]) {
            cout << "IMPOSSIBLE\n";
            exit(0);
        }
    }
    cout << cost << "\n";
}


//---------------------------------------------------------------------------------------



/*
    Boruvka's Algorithm
    -> Find MST in O(Elog(V)) 
    ->well-suited for parallel computing environments.
    -> Component-based
*/
const ll N=1e5+7;
struct edges{
    ll v,u,cost;
};

ll n,m;
ll p[N],min_edge[N];
edges g[N];

void init_dsu(){
  for(ll i=1;i<=n;i++){
    p[i]=i;
  }
}
ll root(ll v){
    if(p[v]==v)return v;
    return p[v]=root(p[v]);
}
bool merge(ll v,ll u){
  v=root(v);u=root(u);
  if(v==u)return 0;
  p[v]=u;
  return 1;
}

ll mst(){
  init_dsu();
  ll cnt_cmp=n;
  ll ans=0;
  while(cnt_cmp>1){
    for(ll i=1;i<=n;i++){
      min_edge[i]=-1;
    }
    for(int i=1;i<=m;i++){
      if(root(g[i].v)==root(g[i].u))continue;
      ll r_v=root(g[i].v);
      if(min_edge[r_v]==-1 || g[i].cost<g[min_edge[r_v]].cost){
        min_edge[r_v]=i;
      }
      ll r_u=root(g[i].u);
      if(min_edge[r_u]==-1 || g[i].cost<g[min_edge[r_u]].cost){
        min_edge[r_u]=i;
      }
    }
    for(ll i=1;i<=n;i++){
      if(min_edge[i]!=-1){
        if(merge(g[min_edge[i]].v,g[min_edge[i]].u)){
          ans+=g[min_edge[i]].cost;
          cnt_cmp--;
        }
      }
    }
  }
  return ans;

}

void input(){
  cin>>n>>m;
  for(ll i=1;i<=m;i++){
    cin>>g[i].v>>g[i].u>>g[i].cost;
  }
  cout<<mst()<<nline;
}
